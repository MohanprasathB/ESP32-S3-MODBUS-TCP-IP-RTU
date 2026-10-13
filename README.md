# Sarayu Gateway - Network Configuration Portal

ESP32-S3 WROOM-1 N16R8 with WiFi and W5500 Ethernet module for flexible network connectivity.

## Features

- **AP Mode on Boot**: Always starts in AP mode for easy configuration
- **Flexible Connectivity**: Choose WiFi, Ethernet, or Both
- **Priority System**: Select which connection to try first (WiFi→Ethernet or Ethernet→WiFi)
- **Automatic Fallback**: 20-second timeout with automatic failover
- **Web Configuration**: Beautiful responsive web interface (Sarayu Gateway)
- **Persistent Storage**: Configuration saved to NVS flash memory
- **Current & Previous Config Display**: View and restore previous settings

## Hardware Requirements

- **ESP32-S3 WROOM-1 N16R8** (16MB Flash + 8MB PSRAM)
- **W5500 Ethernet Module**
- Ethernet Cable
- USB-C Cable for power/programming

## Wiring

### W5500 to ESP32-S3

| W5500 | ESP32-S3 |
|-------|----------|
| VCC   | 3.3V     |
| GND   | GND      |
| MOSI  | GPIO 11  |
| MISO  | GPIO 13  |
| SCK   | GPIO 12  |
| CS    | GPIO 10  |
| RST   | GPIO 9   |

## Arduino IDE Setup

### Required Libraries

Install via Library Manager (Sketch → Include Library → Manage Libraries):
- **Ethernet** (by Arduino)
- **ArduinoJson** (by Benoit Blanchon) - version 6.x
- **WebServer** (included with ESP32 core)
- **Preferences** (included with ESP32 core)

### Board Settings

- **Board**: ESP32S3 Dev Module
- **Flash Size**: 16MB (128Mb)
- **PSRAM**: OPI PSRAM
- **USB CDC On Boot**: Enabled
- **Partition Scheme**: 16M Flash (3MB APP/9.9MB FATFS)

## Usage

### First Time Setup

1. **Upload the sketch** to your ESP32-S3
2. **Open Serial Monitor** (115200 baud) to see connection info
3. **Connect to WiFi AP**:
   - SSID: `Sarayu-Gateway-Setup`
   - Password: `sarayu123`
4. **Open Browser**: Navigate to `http://192.168.4.1`
5. **Configure Network**:
   - Select mode (WiFi/Ethernet/Both)
   - Enter WiFi credentials (if using WiFi)
   - Configure Ethernet (DHCP or Static IP)
   - Set priority (if using Both)
6. **Click "Save & Connect"**

### Network Modes

#### WiFi Only
- Connects to specified WiFi network
- Supports open or password-protected networks

#### Ethernet Only
- Connects via W5500 module
- Supports DHCP or static IP configuration

#### Both (WiFi + Ethernet)
- Connects to both networks simultaneously
- Priority determines which to try first
- 20-second timeout before trying alternate
- **Example**: Priority "Ethernet→WiFi"
  1. Try Ethernet for 20s
  2. If fails, try WiFi for 20s
  3. Loop continues

### Timeout Behavior

When mode is set to **"Both"**:
- **Priority: Ethernet First**
  - Tries Ethernet for 20 seconds
  - If fails → tries WiFi for 20 seconds
  - Continues trying both with 20s intervals

- **Priority: WiFi First**
  - Tries WiFi for 20 seconds
  - If fails → tries Ethernet for 20 seconds
  - Continues trying both with 20s intervals

### Accessing Configuration Portal

The AP mode is **always active**, so you can:
1. Connect to `Sarayu-Gateway-Setup` WiFi anytime
2. Navigate to `http://192.168.4.1`
3. Change configuration or view current status

## API Endpoints

The web server provides these endpoints:

- **GET /** - Configuration web interface
- **GET /status** - Get current and previous configuration (JSON)
- **POST /save** - Save new configuration (JSON)
- **POST /cancel** - Restore previous configuration

### Example Status Response

```json
{
  "current": {
    "mode": "both",
    "priority": "ethernet_first",
    "wifi": {
      "ssid": "MyWiFi",
      "security": "closed",
      "password": "mypassword"
    },
    "ethernet": {
      "ip_mode": "dhcp"
    }
  },
  "previous": {
    "mode": "wifi",
    "wifi": {
      "ssid": "OldWiFi",
      "security": "closed"
    }
  }
}
```

## Configuration Storage

All settings are stored in ESP32 NVS (Non-Volatile Storage):
- Survives power cycles
- Can be erased via Arduino IDE (Tools → Erase Flash → All Flash Contents)

## Serial Monitor Output

```
╔════════════════════════════════════════╗
║    Sarayu Gateway - Network Setup     ║
╚════════════════════════════════════════╝

📂 Loading configuration from NVS...
✓ Configuration loaded
  Mode: both
  WiFi SSID: MyNetwork
  Ethernet: dhcp

📡 Starting Access Point mode...
─────────────────────────────────────────
✓ AP Mode Active
  SSID    : Sarayu-Gateway-Setup
  Password: sarayu123
  IP      : 192.168.4.1

🌐 Open http://192.168.4.1 in your browser
═══════════════════════════════════════════

✓ Web server started
═══════════════════════════════════════════
```

## Troubleshooting

### W5500 Not Detected
- Check all 7 wiring connections
- Verify 3.3V power (not 5V!)
- Try different CS pin if needed

### WiFi Won't Connect
- Verify SSID and password are correct
- Check WiFi security type (open/closed)
- Ensure WiFi network is in range

### Ethernet No Link
- Check Ethernet cable connection
- Verify cable is connected to router/switch
- Check for link LED on W5500 module

### Can't Access Web Portal
- Ensure connected to `Sarayu-Gateway-Setup` WiFi
- Try `http://192.168.4.1` (not https)
- Clear browser cache
- Try different browser

### Configuration Not Saving
- Check Serial Monitor for error messages
- Try erasing flash (Tools → Erase Flash → All Flash Contents)
- Re-upload sketch

## Next Steps

This gateway is designed to be extended with:
- **Modbus TCP/IP Server** - Respond to Modbus requests over network
- **Modbus RTU to TCP Gateway** - Bridge serial Modbus devices to Ethernet
- **Data Logging** - Log sensor data to local storage or cloud
- **MQTT Client** - Publish data to MQTT brokers

## License

Open source - modify as needed for your project.

## Credits

Built for industrial IoT applications requiring reliable dual-network connectivity.
