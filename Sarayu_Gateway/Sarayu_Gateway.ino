/*
 * Sarayu Gateway - Network Configuration Portal
 * ESP32-S3 with WiFi and W5500 Ethernet
 * 
 * Features:
 * - AP mode on every boot for network configuration
 * - Choose WiFi, Ethernet, or Both
 * - Priority selection (WiFi first or Ethernet first)
 * - 20-second timeout for fallback
 * - Configuration stored in NVS (Preferences)
 */

#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h>

// W5500 Pin definitions
#define W5500_CS    10
#define W5500_RST   9
#define SPI_MOSI    11
#define SPI_MISO    13
#define SPI_SCK     12

// AP Configuration
#define AP_SSID     "Sarayu-Gateway-Setup"
#define AP_PASSWORD "sarayu123"
#define AP_TIMEOUT  300000  // 5 minutes in AP mode before retry

// Network timeouts
#define NETWORK_TIMEOUT 20000  // 20 seconds

// Web server
WebServer server(80);
Preferences prefs;

// Configuration structure
struct NetworkConfig {
  String mode;           // "wifi", "ethernet", "both"
  String priority;       // "wifi_first", "ethernet_first"
  int timeout;           // 20 seconds
  
  // WiFi settings
  String wifi_ssid;
  String wifi_security;  // "open", "closed"
  String wifi_password;
  
  // Ethernet settings
  String eth_ip_mode;    // "dhcp", "static"
  String eth_ip;
  String eth_netmask;
  String eth_gateway;
  String eth_dns;
} currentConfig, previousConfig;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

bool wifiConnected = false;
bool ethernetConnected = false;

// Forward declarations
void startAPMode();
void loadConfiguration();
void saveConfiguration();
bool connectWiFi();
bool connectEthernet();
void applyNetworkConfiguration();
void handleRoot();
void handleSave();
void handleCancel();
void handleStatus();

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n╔════════════════════════════════════════╗");
  Serial.println("║    Sarayu Gateway - Network Setup     ║");
  Serial.println("╚════════════════════════════════════════╝\n");

  // Initialize preferences
  prefs.begin("network", false);
  
  // Load saved configuration
  loadConfiguration();
  
  // Always start AP mode first for configuration
  startAPMode();
  
  // Setup web server routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/save", HTTP_POST, handleSave);
  server.on("/cancel", HTTP_POST, handleCancel);
  server.on("/status", HTTP_GET, handleStatus);
  
  server.begin();
  Serial.println("✓ Web server started");
  Serial.println("═══════════════════════════════════════════");
}

void loop() {
  server.handleClient();
  
  // Monitor connection status
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 5000) {
    lastCheck = millis();
    
    if (wifiConnected && WiFi.status() != WL_CONNECTED) {
      Serial.println("⚠ WiFi disconnected!");
      wifiConnected = false;
    }
    
    if (ethernetConnected && Ethernet.linkStatus() == LinkOFF) {
      Serial.println("⚠ Ethernet disconnected!");
      ethernetConnected = false;
    }
  }
}

void startAPMode() {
  Serial.println("\n📡 Starting Access Point mode...");
  Serial.println("─────────────────────────────────────────");
  
  WiFi.mode(WIFI_AP);
  
  // Configure static IP for AP
  IPAddress local_ip(192, 168, 4, 1);
  IPAddress gateway(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);
  
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(AP_SSID, AP_PASSWORD);
  
  IPAddress IP = WiFi.softAPIP();
  Serial.println("✓ AP Mode Active");
  Serial.print("  SSID    : ");
  Serial.println(AP_SSID);
  Serial.print("  Password: ");
  Serial.println(AP_PASSWORD);
  Serial.print("  IP      : ");
  Serial.println(IP);
  Serial.println("\n🌐 Open http://" + IP.toString() + " in your browser");
  Serial.println("═══════════════════════════════════════════\n");
}

void loadConfiguration() {
  Serial.println("📂 Loading configuration from NVS...");
  
  currentConfig.mode = prefs.getString("mode", "wifi");
  currentConfig.priority = prefs.getString("priority", "wifi_first");
  currentConfig.timeout = prefs.getInt("timeout", 20);
  
  currentConfig.wifi_ssid = prefs.getString("wifi_ssid", "");
  currentConfig.wifi_security = prefs.getString("wifi_sec", "closed");
  currentConfig.wifi_password = prefs.getString("wifi_pass", "");
  
  currentConfig.eth_ip_mode = prefs.getString("eth_mode", "dhcp");
  currentConfig.eth_ip = prefs.getString("eth_ip", "");
  currentConfig.eth_netmask = prefs.getString("eth_mask", "");
  currentConfig.eth_gateway = prefs.getString("eth_gw", "");
  currentConfig.eth_dns = prefs.getString("eth_dns", "");
  
  // Load previous config
  previousConfig.mode = prefs.getString("prev_mode", "");
  previousConfig.wifi_ssid = prefs.getString("prev_ssid", "");
  previousConfig.eth_ip_mode = prefs.getString("prev_ethmode", "");
  
  if (currentConfig.mode.length() > 0) {
    Serial.println("✓ Configuration loaded");
    Serial.println("  Mode: " + currentConfig.mode);
    if (currentConfig.mode == "wifi" || currentConfig.mode == "both") {
      Serial.println("  WiFi SSID: " + currentConfig.wifi_ssid);
    }
    if (currentConfig.mode == "ethernet" || currentConfig.mode == "both") {
      Serial.println("  Ethernet: " + currentConfig.eth_ip_mode);
    }
  } else {
    Serial.println("ℹ No saved configuration found");
  }
}

void saveConfiguration() {
  Serial.println("\n💾 Saving configuration to NVS...");
  
  // Save previous config
  prefs.putString("prev_mode", currentConfig.mode);
  prefs.putString("prev_ssid", currentConfig.wifi_ssid);
  prefs.putString("prev_ethmode", currentConfig.eth_ip_mode);
  
  // Save current config
  prefs.putString("mode", currentConfig.mode);
  prefs.putString("priority", currentConfig.priority);
  prefs.putInt("timeout", currentConfig.timeout);
  
  prefs.putString("wifi_ssid", currentConfig.wifi_ssid);
  prefs.putString("wifi_sec", currentConfig.wifi_security);
  prefs.putString("wifi_pass", currentConfig.wifi_password);
  
  prefs.putString("eth_mode", currentConfig.eth_ip_mode);
  prefs.putString("eth_ip", currentConfig.eth_ip);
  prefs.putString("eth_mask", currentConfig.eth_netmask);
  prefs.putString("eth_gw", currentConfig.eth_gateway);
  prefs.putString("eth_dns", currentConfig.eth_dns);
  
  Serial.println("✓ Configuration saved");
}

bool connectWiFi() {
  if (currentConfig.wifi_ssid.length() == 0) return false;
  
  Serial.println("\n📶 Connecting to WiFi...");
  Serial.println("  SSID: " + currentConfig.wifi_ssid);
  
  WiFi.mode(WIFI_AP_STA);  // Keep AP active while connecting
  
  if (currentConfig.wifi_security == "open") {
    WiFi.begin(currentConfig.wifi_ssid.c_str());
  } else {
    WiFi.begin(currentConfig.wifi_ssid.c_str(), currentConfig.wifi_password.c_str());
  }
  
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < NETWORK_TIMEOUT) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("✓ WiFi connected!");
    Serial.println("  IP: " + WiFi.localIP().toString());
    wifiConnected = true;
    return true;
  } else {
    Serial.println("✗ WiFi connection failed");
    return false;
  }
}

bool connectEthernet() {
  Serial.println("\n🔌 Connecting to Ethernet...");
  
  // Initialize W5500
  pinMode(W5500_RST, OUTPUT);
  digitalWrite(W5500_RST, LOW);
  delay(50);
  digitalWrite(W5500_RST, HIGH);
  delay(200);
  
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, W5500_CS);
  Ethernet.init(W5500_CS);
  
  bool success = false;
  
  if (currentConfig.eth_ip_mode == "static") {
    Serial.println("  Mode: Static IP");
    IPAddress ip, gateway, subnet, dns;
    ip.fromString(currentConfig.eth_ip);
    gateway.fromString(currentConfig.eth_gateway);
    subnet.fromString(currentConfig.eth_netmask);
    dns.fromString(currentConfig.eth_dns);
    
    Ethernet.begin(mac, ip, dns, gateway, subnet);
    delay(1000);
    success = (Ethernet.linkStatus() == LinkON);
  } else {
    Serial.println("  Mode: DHCP");
    success = (Ethernet.begin(mac, NETWORK_TIMEOUT, 4000) != 0);
  }
  
  if (success && Ethernet.linkStatus() == LinkON) {
    Serial.println("✓ Ethernet connected!");
    Serial.println("  IP: " + Ethernet.localIP().toString());
    ethernetConnected = true;
    return true;
  } else {
    Serial.println("✗ Ethernet connection failed");
    return false;
  }
}

void applyNetworkConfiguration() {
  Serial.println("\n🔄 Applying network configuration...");
  Serial.println("═══════════════════════════════════════════");
  
  wifiConnected = false;
  ethernetConnected = false;
  
  if (currentConfig.mode == "wifi") {
    connectWiFi();
  }
  else if (currentConfig.mode == "ethernet") {
    connectEthernet();
  }
  else if (currentConfig.mode == "both") {
    if (currentConfig.priority == "wifi_first") {
      Serial.println("Priority: WiFi → Ethernet");
      if (!connectWiFi()) {
        Serial.println("⚠ WiFi failed, trying Ethernet...");
        connectEthernet();
      } else {
        // Also try ethernet
        connectEthernet();
      }
    } else {
      Serial.println("Priority: Ethernet → WiFi");
      if (!connectEthernet()) {
        Serial.println("⚠ Ethernet failed, trying WiFi...");
        connectWiFi();
      } else {
        // Also try WiFi
        connectWiFi();
      }
    }
  }
  
  Serial.println("═══════════════════════════════════════════");
  Serial.println("Status:");
  Serial.println("  WiFi    : " + String(wifiConnected ? "Connected" : "Disconnected"));
  Serial.println("  Ethernet: " + String(ethernetConnected ? "Connected" : "Disconnected"));
  Serial.println("═══════════════════════════════════════════\n");
}

// Include web handlers after all function definitions
#include "web_handlers.h"
