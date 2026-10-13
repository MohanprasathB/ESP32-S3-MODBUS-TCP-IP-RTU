/*
 * ESP32-S3 with W5500 - DHCP Connection Test
 * 
 * This sketch tests DHCP connection and automatic IP assignment.
 * Monitor the Serial output to see the assigned IP address.
 * 
 * Expected Result: Device should get IP address from your router
 */

#include <SPI.h>
#include <Ethernet.h>

// Pin definitions for ESP32-S3
#define W5500_CS    10
#define W5500_RST   9
#define SPI_MOSI    11
#define SPI_MISO    13
#define SPI_SCK     12

// MAC address - make this unique for each device
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n=================================");
  Serial.println("ESP32-S3 W5500 DHCP Test");
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
  
  Serial.println("Requesting DHCP address...");
  Serial.println("(This may take up to 60 seconds)");
  
  // Start Ethernet with DHCP (timeout: 60 seconds, response timeout: 4 seconds)
  if (Ethernet.begin(mac, 60000, 4000) == 0) {
    Serial.println("\n❌ Failed to obtain IP address via DHCP");
    
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("❌ W5500 hardware not detected!");
      Serial.println("   Check SPI wiring and connections");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("⚠ W5500 detected but Ethernet cable not connected");
      Serial.println("   Check cable connection");
    } else {
      Serial.println("⚠ DHCP server not responding");
      Serial.println("   Check router/network settings");
    }
    
    while(true) {
      delay(1000);
    }
  }

  // Successfully got IP address
  Serial.println("\n✓✓✓ SUCCESS ✓✓✓\n");
  printNetworkInfo();
  
  Serial.println("\n=================================");
  Serial.println("Network is ready!");
  Serial.println("=================================\n");
}

void loop() {
  // Maintain DHCP lease
  switch (Ethernet.maintain()) {
    case 1:
      Serial.println("⚠ DHCP renewal failed");
      break;
    case 2:
      Serial.println("✓ DHCP renewal success");
      printNetworkInfo();
      break;
    case 3:
      Serial.println("⚠ DHCP rebind failed");
      break;
    case 4:
      Serial.println("✓ DHCP rebind success");
      printNetworkInfo();
      break;
    default:
      break;
  }
  
  // Check link status every 5 seconds
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 5000) {
    lastCheck = millis();
    
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("⚠ Network cable disconnected!");
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
