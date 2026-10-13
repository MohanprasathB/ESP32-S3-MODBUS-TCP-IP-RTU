/*
 * ESP32-S3 with W5500 - Web Client Test
 * 
 * This sketch tests HTTP client functionality by making a request
 * to a test server and displaying the response.
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

// Test server (httpbin.org for testing)
char server[] = "httpbin.org";

EthernetClient client;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n=================================");
  Serial.println("ESP32-S3 W5500 Web Client Test");
  Serial.println("=================================\n");

  // Hardware reset
  pinMode(W5500_RST, OUTPUT);
  digitalWrite(W5500_RST, LOW);
  delay(50);
  digitalWrite(W5500_RST, HIGH);
  delay(200);

  // Initialize Ethernet
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, W5500_CS);
  Ethernet.init(W5500_CS);
  
  Serial.println("Starting Ethernet with DHCP...");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("❌ Failed to configure Ethernet");
    while(true) delay(1000);
  }

  Serial.print("✓ IP Address: ");
  Serial.println(Ethernet.localIP());
  Serial.println();

  // Give network time to initialize
  delay(1000);
  
  // Make HTTP request
  testHttpRequest();
}

void loop() {
  // Print any incoming data
  if (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // If the server disconnected, stop the client
  if (!client.connected()) {
    if (client.available() == 0) {
      Serial.println();
      Serial.println("=================================");
      Serial.println("Request complete!");
      Serial.println("=================================");
      client.stop();
      
      // Wait and try again
      Serial.println("\nWaiting 10 seconds before next request...");
      delay(10000);
      testHttpRequest();
    }
  }
}

void testHttpRequest() {
  Serial.println("=================================");
  Serial.println("Making HTTP request...");
  Serial.println("=================================\n");
  Serial.print("Connecting to ");
  Serial.print(server);
  Serial.println("...");

  if (client.connect(server, 80)) {
    Serial.println("✓ Connected to server");
    Serial.println("Sending HTTP GET request...\n");
    
    // Send HTTP request
    client.println("GET /ip HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
    
    Serial.println("Response:");
    Serial.println("-----------------------------------");
  } else {
    Serial.println("❌ Connection failed");
    Serial.println("Check network connectivity");
  }
}
