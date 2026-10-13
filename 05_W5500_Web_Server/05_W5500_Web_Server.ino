/*
 * ESP32-S3 with W5500 - Web Server Test
 * 
 * This sketch creates a simple web server that responds to HTTP requests.
 * After uploading, open the displayed IP address in your web browser.
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

// Initialize the Ethernet server library on port 80
EthernetServer server(80);

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n=================================");
  Serial.println("ESP32-S3 W5500 Web Server Test");
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

  // Start the server
  server.begin();
  
  Serial.println("\n✓✓✓ Web Server Started ✓✓✓\n");
  Serial.print("Server IP address: ");
  Serial.println(Ethernet.localIP());
  Serial.println("\nOpen this address in your web browser!");
  Serial.println("=================================\n");
}

void loop() {
  // Listen for incoming clients
  EthernetClient client = server.available();
  
  if (client) {
    Serial.println("New client connected");
    
    boolean currentLineIsBlank = true;
    String request = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        
        // If you've gotten to the end of the line and the line is blank,
        // the HTTP request has ended, so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          
          // Send HTTP response
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          
          // Send HTML page
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head>");
          client.println("<title>ESP32-S3 W5500 Test</title>");
          client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
          client.println("<style>");
          client.println("body { font-family: Arial; margin: 20px; background: #f0f0f0; }");
          client.println(".container { background: white; padding: 20px; border-radius: 10px; max-width: 600px; margin: 0 auto; box-shadow: 0 2px 5px rgba(0,0,0,0.1); }");
          client.println("h1 { color: #2c3e50; border-bottom: 3px solid #3498db; padding-bottom: 10px; }");
          client.println(".success { color: #27ae60; font-size: 24px; }");
          client.println(".info { background: #ecf0f1; padding: 15px; border-radius: 5px; margin: 10px 0; }");
          client.println("</style>");
          client.println("</head>");
          client.println("<body>");
          client.println("<div class='container'>");
          client.println("<h1>ESP32-S3 with W5500 Ethernet</h1>");
          client.println("<p class='success'>✓ Web Server Test Successful!</p>");
          client.println("<div class='info'>");
          client.println("<h3>System Information:</h3>");
          client.print("<p><strong>IP Address:</strong> ");
          client.print(Ethernet.localIP());
          client.println("</p>");
          client.print("<p><strong>MAC Address:</strong> ");
          for (byte i = 0; i < 6; i++) {
            if (mac[i] < 16) client.print("0");
            client.print(mac[i], HEX);
            if (i < 5) client.print(":");
          }
          client.println("</p>");
          client.print("<p><strong>Uptime:</strong> ");
          client.print(millis() / 1000);
          client.println(" seconds</p>");
          client.print("<p><strong>Free Memory:</strong> ");
          client.print(ESP.getFreeHeap());
          client.println(" bytes</p>");
          client.println("</div>");
          client.println("<p>Your ESP32-S3 is successfully connected to the network via W5500 Ethernet!</p>");
          client.println("<p><a href='/'>Refresh Page</a></p>");
          client.println("</div>");
          client.println("</body>");
          client.println("</html>");
          
          break;
        }
        
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    
    // Give the browser time to receive the data
    delay(1);
    // Close the connection
    client.stop();
    Serial.println("Client disconnected\n");
  }
  
  // Maintain DHCP lease
  Ethernet.maintain();
}
