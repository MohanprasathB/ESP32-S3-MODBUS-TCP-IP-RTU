/*
 * ESP32-S3 with W5500 - Basic Connection Test
 * 
 * This sketch tests basic SPI communication with the W5500 module.
 * It reads the chip version and verifies the hardware connection.
 * 
 * Wiring:
 * W5500 VCC  -> ESP32-S3 3.3V
 * W5500 GND  -> ESP32-S3 GND
 * W5500 MOSI -> ESP32-S3 GPIO11
 * W5500 MISO -> ESP32-S3 GPIO13
 * W5500 SCK  -> ESP32-S3 GPIO12
 * W5500 CS   -> ESP32-S3 GPIO10
 * W5500 RST  -> ESP32-S3 GPIO9 (optional)
 */

#include <SPI.h>
#include <Ethernet.h>

// Pin definitions for ESP32-S3
#define W5500_CS    10
#define W5500_RST   9
#define SPI_MOSI    11
#define SPI_MISO    13
#define SPI_SCK     12

// MAC address - modify if you have multiple devices
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n=================================");
  Serial.println("ESP32-S3 W5500 Basic Test");
  Serial.println("=================================\n");

  // Initialize reset pin if used
  pinMode(W5500_RST, OUTPUT);
  digitalWrite(W5500_RST, LOW);
  delay(50);
  digitalWrite(W5500_RST, HIGH);
  delay(200);

  // Initialize SPI with custom pins for ESP32-S3
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, W5500_CS);
  
  Serial.println("Initializing W5500...");
  Serial.print("CS Pin: GPIO");
  Serial.println(W5500_CS);
  Serial.print("MOSI Pin: GPIO");
  Serial.println(SPI_MOSI);
  Serial.print("MISO Pin: GPIO");
  Serial.println(SPI_MISO);
  Serial.print("SCK Pin: GPIO");
  Serial.println(SPI_SCK);
  Serial.println();

  // Configure Ethernet chip select pin
  Ethernet.init(W5500_CS);
  
  delay(500);

  // Test reading W5500 chip version
  Serial.println("Testing SPI communication...");
  
  // Try to initialize Ethernet
  if (Ethernet.begin(mac, 5000, 5000) == 0) {
    Serial.println("❌ Failed to configure Ethernet using DHCP");
    
    // Try to get hardware status
    auto link = Ethernet.linkStatus();
    Serial.print("Link Status: ");
    switch(link) {
      case Unknown:
        Serial.println("Unknown - Check SPI connections!");
        break;
      case LinkON:
        Serial.println("Link ON - Cable connected");
        break;
      case LinkOFF:
        Serial.println("Link OFF - Check Ethernet cable");
        break;
    }
    
    auto hardware = Ethernet.hardwareStatus();
    Serial.print("Hardware Status: ");
    switch(hardware) {
      case EthernetNoHardware:
        Serial.println("No Hardware - Check wiring and SPI pins!");
        break;
      case EthernetW5100:
        Serial.println("W5100 detected");
        break;
      case EthernetW5200:
        Serial.println("W5200 detected");
        break;
      case EthernetW5500:
        Serial.println("✓ W5500 detected - Hardware communication OK!");
        break;
      default:
        Serial.println("Unknown hardware");
        break;
    }
  } else {
    Serial.println("✓ W5500 initialized successfully!");
    Serial.print("✓ IP Address: ");
    Serial.println(Ethernet.localIP());
    Serial.print("✓ Subnet Mask: ");
    Serial.println(Ethernet.subnetMask());
    Serial.print("✓ Gateway: ");
    Serial.println(Ethernet.gatewayIP());
    Serial.print("✓ DNS Server: ");
    Serial.println(Ethernet.dnsServerIP());
    
    auto link = Ethernet.linkStatus();
    Serial.print("Link Status: ");
    Serial.println(link == LinkON ? "Connected" : "Disconnected");
  }

  Serial.println("\n=================================");
  Serial.println("Test complete!");
  Serial.println("=================================");
}

void loop() {
  // Maintain DHCP lease
  Ethernet.maintain();
  
  // Print status every 10 seconds
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 10000) {
    lastCheck = millis();
    
    Serial.println("\n--- Status Update ---");
    Serial.print("Link: ");
    Serial.println(Ethernet.linkStatus() == LinkON ? "Connected" : "Disconnected");
    Serial.print("IP: ");
    Serial.println(Ethernet.localIP());
  }
  
  delay(100);
}
