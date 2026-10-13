/*
 * ESP32-S3 with W5500 - Simple Web Server Test
 * 
 * This creates a simple web server you can access from your browser.
 * After upload, open the IP address shown in Serial Monitor in your web browser.
 * 
 * Your IP: 192.168.1.17 (based on your test)
 */

#include <SPI.h>
#include <Ethernet.h>

// Pin definitions for ESP32-S3
#define W5500_CS    10
#define W5500_RST   9
#define SPI_MOSI    11
#define SPI_MISO    13
#define SPI_SCK     12

// MAC address - must be unique on your network
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Web server on port 80
EthernetServer server(80);

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n╔════════════════════════════════════════╗");
  Serial.println("║  ESP32-S3 W5500 Web Server Test       ║");
  Serial.println("╚════════════════════════════════════════╝\n");

  // Hardware reset of W5500
  pinMode(W5500_RST, OUTPUT);
  digitalWrite(W5500_RST, LOW);
  delay(50);
  digitalWrite(W5500_RST, HIGH);
  delay(200);

  // Initialize SPI and Ethernet
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, W5500_CS);
  Ethernet.init(W5500_CS);
  
  Serial.println("Starting Ethernet...");
  
  // Start with longer timeout for DHCP
  if (Ethernet.begin(mac, 15000, 4000) == 0) {
    Serial.println("⚠ DHCP failed, but checking status...");
  }
  
  // Give it a moment
  delay(1000);
  
  // Check actual status
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("❌ No Ethernet cable connected!");
    while(true) delay(1000);
  }
  
  if (Ethernet.localIP() == IPAddress(0,0,0,0)) {
    Serial.println("❌ No IP address obtained!");
    while(true) delay(1000);
  }

  // Start the web server
  server.begin();
  
  Serial.println("\n╔════════════════════════════════════════╗");
  Serial.println("║  ✓✓✓ WEB SERVER IS READY! ✓✓✓         ║");
  Serial.println("╚════════════════════════════════════════╝\n");
  
  Serial.print("🌐 Open this URL in your browser:\n\n   http://");
  Serial.println(Ethernet.localIP());
  
  Serial.println("\n────────────────────────────────────────");
  Serial.println("Network Information:");
  Serial.print("  IP Address : ");
  Serial.println(Ethernet.localIP());
  Serial.print("  Gateway    : ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("  Subnet     : ");
  Serial.println(Ethernet.subnetMask());
  Serial.println("────────────────────────────────────────\n");
  Serial.println("Waiting for browser connections...\n");
}

void loop() {
  // Listen for incoming clients
  EthernetClient client = server.available();
  
  if (client) {
    Serial.println("🔗 New client connected!");
    
    boolean currentLineIsBlank = true;
    String requestLine = "";
    boolean isFirstLine = true;
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        // Capture first line (GET request)
        if (isFirstLine) {
          if (c == '\n') {
            isFirstLine = false;
            Serial.println("   Request: " + requestLine);
          } else if (c != '\r') {
            requestLine += c;
          }
        }
        
        // Check for end of HTTP request
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
          client.println("<title>ESP32-S3 W5500 Success!</title>");
          client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
          client.println("<style>");
          client.println("* { margin: 0; padding: 0; box-sizing: border-box; }");
          client.println("body { font-family: 'Segoe UI', Arial, sans-serif; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); min-height: 100vh; display: flex; align-items: center; justify-content: center; padding: 20px; }");
          client.println(".card { background: white; padding: 40px; border-radius: 20px; box-shadow: 0 20px 60px rgba(0,0,0,0.3); max-width: 600px; width: 100%; }");
          client.println("h1 { color: #2c3e50; margin-bottom: 10px; font-size: 32px; }");
          client.println(".success { color: #27ae60; font-size: 48px; margin: 20px 0; text-align: center; }");
          client.println(".info { background: #f8f9fa; padding: 20px; border-radius: 10px; margin: 20px 0; border-left: 4px solid #667eea; }");
          client.println(".info h3 { color: #495057; margin-bottom: 15px; }");
          client.println(".info p { color: #6c757d; margin: 8px 0; line-height: 1.6; }");
          client.println(".label { font-weight: bold; color: #495057; }");
          client.println(".value { color: #667eea; font-family: 'Courier New', monospace; }");
          client.println(".button { display: inline-block; padding: 12px 30px; background: #667eea; color: white; text-decoration: none; border-radius: 25px; margin-top: 20px; transition: all 0.3s; }");
          client.println(".button:hover { background: #764ba2; transform: translateY(-2px); box-shadow: 0 5px 15px rgba(0,0,0,0.2); }");
          client.println("</style>");
          client.println("</head>");
          client.println("<body>");
          client.println("<div class='card'>");
          client.println("<h1>🎉 Connection Successful!</h1>");
          client.println("<div class='success'>✓</div>");
          client.println("<p style='text-align: center; color: #6c757d; font-size: 18px;'>Your ESP32-S3 is now connected via W5500 Ethernet!</p>");
          
          client.println("<div class='info'>");
          client.println("<h3>📡 Network Information</h3>");
          client.print("<p><span class='label'>IP Address:</span> <span class='value'>");
          client.print(Ethernet.localIP());
          client.println("</span></p>");
          client.print("<p><span class='label'>MAC Address:</span> <span class='value'>");
          for (byte i = 0; i < 6; i++) {
            if (mac[i] < 16) client.print("0");
            client.print(mac[i], HEX);
            if (i < 5) client.print(":");
          }
          client.println("</span></p>");
          client.print("<p><span class='label'>Gateway:</span> <span class='value'>");
          client.print(Ethernet.gatewayIP());
          client.println("</span></p>");
          client.println("</div>");
          
          client.println("<div class='info'>");
          client.println("<h3>💻 System Status</h3>");
          client.print("<p><span class='label'>Chip Model:</span> <span class='value'>");
          client.print(ESP.getChipModel());
          client.println("</span></p>");
          client.print("<p><span class='label'>CPU Frequency:</span> <span class='value'>");
          client.print(ESP.getCpuFreqMHz());
          client.println(" MHz</span></p>");
          client.print("<p><span class='label'>Flash Size:</span> <span class='value'>");
          client.print(ESP.getFlashChipSize() / (1024 * 1024));
          client.println(" MB</span></p>");
          client.print("<p><span class='label'>PSRAM Size:</span> <span class='value'>");
          client.print(ESP.getPsramSize() / (1024 * 1024));
          client.println(" MB</span></p>");
          client.print("<p><span class='label'>Uptime:</span> <span class='value'>");
          unsigned long seconds = millis() / 1000;
          unsigned long minutes = seconds / 60;
          unsigned long hours = minutes / 60;
          client.print(hours);
          client.print("h ");
          client.print(minutes % 60);
          client.print("m ");
          client.print(seconds % 60);
          client.println("s</span></p>");
          client.println("</div>");
          
          client.println("<div style='text-align: center;'>");
          client.println("<a href='/' class='button'>🔄 Refresh Page</a>");
          client.println("</div>");
          
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
    
    // Close connection
    delay(1);
    client.stop();
    Serial.println("   ✓ Client disconnected\n");
  }
  
  // Maintain DHCP lease
  Ethernet.maintain();
}
