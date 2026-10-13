/*
 * ESP32-S3 with W5500 - Static IP Test
 * 
 * This sketch configures a static IP address instead of using DHCP.
 * Useful for faster startup and when DHCP is not available.
 * 
 * IMPORTANT: Modify the IP settings below to match your network!
 */

#include <SPI.h>
#include <Ethernet.h>

// Pin definitions for ESP32-S3
#define W5500_CS    10
#define W5500_RST   9
#define SPI_MOSI    11
#define SPI_MISO    13
#define SPI_SCK     12

// MAC address
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Network configuration - MODIFY THESE FOR YOUR NETWORK!
IPAddress ip(192, 168, 1, 177);        // Static IP for ESP32
IPAddress gateway(192, 168, 1, 1);      // Your router IP
IPAddress subnet(255, 255, 255, 0);     // Subnet mask
IPAddress dns(192, 168, 1, 1);          // DNS server (usually router IP)

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n=================================");
  Serial.println("ESP32-S3 W5500 Static IP Test");
  Serial.println("=================================\n");

  // Hardware reset of W5500
  pinMode(W5500_RST, OUTPUT);
  digitalWrite(W5500_RST, LOW);
  delay(50);
  digitalWrite(W5500_RST, HIGH);
  delay(200);

  // Initialize SPI
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, W5500_CS);
  Ethernet.init(W5500_CS);
  
  Serial.println("Configuring static IP...");
  Serial.print("Requested IP: ");
  Serial.println(ip);
  
  // Start Ethernet with static IP
  Ethernet.begin(mac, ip, dns, gateway, subnet);
  
  // Give W5500 time to initialize
  delay(1000);

  // Check hardware status
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("\n❌ W5500 hardware not detected!");
    Serial.println("   Check SPI wiring and connections");
    while(true) delay(1000);
  }

  // Check link status
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("\n⚠ W5500 detected but Ethernet cable not connected");
    Serial.println("   Please connect cable and reset");
  }

  // Verify configuration
  Serial.println("\n✓ Static IP configured\n");
  printNetworkInfo();
  
  Serial.println("\n=================================");
  Serial.println("Network is ready!");
  Serial.println("=================================\n");
  Serial.println("You can now:");
  Serial.println("  - Ping this device from another computer");
  Serial.println("  - Try telnet or other network tools");
}

void loop() {
  // Check link status every 5 seconds
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 5000) {
    lastCheck = millis();
    
    Serial.print("Link Status: ");
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("❌ Cable disconnected");
    } else {
      Serial.println("✓ Connected");
    }
  }
  
  delay(100);
}

void printNetworkInfo() {
  Serial.println("Network Configuration:");
  Serial.print("  IP Address : ");
  Serial.println(Ethernet.localIP());
  Serial.print("  Subnet Mask: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("  Gateway    : ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("  DNS Server : ");
  Serial.println(Ethernet.dnsServerIP());
  Serial.print("  MAC Address: ");
  for (byte i = 0; i < 6; i++) {
    if (mac[i] < 16) Serial.print("0");
    Serial.print(mac[i], HEX);
    if (i < 5) Serial.print(":");
  }
  Serial.println();
}
