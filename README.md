# ESP32-S3 with W5500 Ethernet - Connection and Testing

## Hardware Requirements
- ESP32-S3 WROOM1 Module
- W5500 Ethernet Module
- Ethernet Cable
- Power Supply (USB-C for ESP32-S3)
- Jumper Wires

## Wiring Connections

### SPI Connection (W5500 to ESP32-S3)

| W5500 Pin | ESP32-S3 Pin | Description |
|-----------|--------------|-------------|
| VCC       | 3.3V         | Power       |
| GND       | GND          | Ground      |
| MOSI      | GPIO 11      | SPI MOSI    |
| MISO      | GPIO 13      | SPI MISO    |
| SCK       | GPIO 12      | SPI Clock   |
| CS        | GPIO 10      | Chip Select |
| RST       | GPIO 9       | Reset (optional) |

**Note:** These are the default SPI pins for ESP32-S3. You can modify them in the code if needed.

## Arduino IDE Setup

### 1. Install ESP32 Board Support
1. Open Arduino IDE
2. Go to **File → Preferences**
3. Add this URL to "Additional Board Manager URLs":
   ```
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```
4. Go to **Tools → Board → Boards Manager**
5. Search for "ESP32" and install "esp32 by Espressif Systems"
6. Select **Tools → Board → ESP32 Arduino → ESP32S3 Dev Module**

### 2. Install Required Libraries
Go to **Sketch → Include Library → Manage Libraries** and install:
- **Ethernet** (by Various - built-in Arduino library)

Alternative libraries you can try:
- **Ethernet2** or **Ethernet3** (if the standard Ethernet library doesn't work)

### 3. Board Configuration for ESP32-S3 WROOM-1 N16R8
Set these in Arduino IDE under **Tools** menu:
- Board: "ESP32S3 Dev Module"
- USB CDC On Boot: "Enabled"
- USB DFU On Boot: "Disabled"
- USB Mode: "Hardware CDC and JTAG"
- CPU Frequency: "240MHz (WiFi)"
- Flash Mode: "QIO 80MHz"
- Flash Size: "16MB (128Mb)"
- PSRAM: "OPI PSRAM"
- Partition Scheme: "16M Flash (3MB APP/9.9MB FATFS)"
- Upload Mode: "UART0 / Hardware CDC"
- Upload Speed: "921600"

## Testing Steps

1. Wire up the hardware according to the connection table above
2. Connect your ESP32-S3 to your computer via USB
3. Connect an Ethernet cable from the W5500 to your router/switch
4. Open one of the test sketches in Arduino IDE
5. Upload and open Serial Monitor (115200 baud)
6. Observe the output for successful connection

## Test Programs

### Basic Tests (in order of complexity):
1. **01_W5500_Basic_Test** - Tests SPI communication with W5500
2. **02_W5500_DHCP_Test** - Tests getting IP address via DHCP
3. **03_W5500_Static_IP_Test** - Tests with static IP configuration
4. **04_W5500_Web_Client** - Tests HTTP client functionality
5. **05_W5500_Web_Server** - Tests HTTP server functionality

## Troubleshooting

### No Link Light on W5500
- Check power connections (VCC and GND)
- Verify Ethernet cable is properly connected
- Try different Ethernet cable

### Cannot Get IP Address
- Check SPI connections (MOSI, MISO, SCK, CS)
- Verify CS pin matches code
- Try static IP instead of DHCP
- Check router DHCP settings

### SPI Communication Issues
- Verify 3.3V power (not 5V!)
- Check all ground connections
- Reduce SPI clock speed in code
- Add small delay after Ethernet.begin()

### Upload Issues
- Press and hold BOOT button during upload
- Check USB cable supports data transfer
- Try lower upload speed (460800 or 115200)

## Next Steps
After successful connection testing, you can implement:
- Modbus TCP/IP server
- Modbus RTU to Modbus TCP gateway
- Custom network protocols
