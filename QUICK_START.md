# Quick Start Guide - ESP32-S3 with W5500

## Getting Started in 5 Minutes

### Step 1: Wire the Hardware (2 minutes)
Connect your W5500 to ESP32-S3 according to the table:

| W5500 | ESP32-S3 |
|-------|----------|
| VCC   | 3.3V     |
| GND   | GND      |
| MOSI  | GPIO 11  |
| MISO  | GPIO 13  |
| SCK   | GPIO 12  |
| CS    | GPIO 10  |
| RST   | GPIO 9   |

**Important:** Use 3.3V, NOT 5V!

### Step 2: Connect Cables
- Connect ESP32-S3 to computer via USB-C
- Connect Ethernet cable from W5500 to your router

### Step 3: Arduino IDE Setup (1 minute)
1. Install ESP32 board support:
   - **File → Preferences**
   - Add URL: `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
   - **Tools → Board → Boards Manager** → Install "esp32"

2. Select board and configure:
   - **Tools → Board → ESP32 Arduino → ESP32S3 Dev Module**
   - **Tools → Flash Size → 16MB (128Mb)**
   - **Tools → PSRAM → OPI PSRAM**
   - **Tools → USB CDC On Boot → Enabled**

3. Install library:
   - **Sketch → Include Library → Manage Libraries**
   - Search for "Ethernet" and install

### Step 4: Upload First Test (2 minutes)
1. Open `01_W5500_Basic_Test/01_W5500_Basic_Test.ino`
2. Click Upload button
3. Open Serial Monitor (115200 baud)
4. Watch for "✓ W5500 detected" message

### Expected Output
```
=================================
ESP32-S3 W5500 Basic Test
=================================

Initializing W5500...
CS Pin: GPIO10
MOSI Pin: GPIO11
MISO Pin: GPIO13
SCK Pin: GPIO12

Testing SPI communication...
✓ W5500 initialized successfully!
✓ IP Address: 192.168.1.XXX
✓ Subnet Mask: 255.255.255.0
✓ Gateway: 192.168.1.1
✓ DNS Server: 192.168.1.1
Link Status: Connected

=================================
Test complete!
=================================
```

## What to Do If It Doesn't Work

### No W5500 Detected
- **Check wiring** - verify all 7 connections
- **Check power** - must be 3.3V, not 5V
- **Try different CS pin** - change `#define W5500_CS 10` to another GPIO

### No IP Address
- **Check Ethernet cable** - try different cable
- **Check router** - ensure DHCP is enabled
- **Try static IP** - upload `03_W5500_Static_IP_Test` instead

### Upload Fails
- **Hold BOOT button** during upload
- **Check USB cable** - use data cable, not charge-only
- **Lower upload speed** - Tools → Upload Speed → 115200

## Next Steps

After successful basic test:

1. ✅ **Test DHCP** - Upload `02_W5500_DHCP_Test`
2. ✅ **Test Static IP** - Upload `03_W5500_Static_IP_Test`
3. ✅ **Test Web Client** - Upload `04_W5500_Web_Client`
4. ✅ **Test Web Server** - Upload `05_W5500_Web_Server`

## Additional Resources

- See `README.md` for detailed documentation
- See `WIRING_DIAGRAM.md` for visual wiring guide
- See `TROUBLESHOOTING.md` for common issues

## Need Help?

Check these in order:
1. Wiring connections (most common issue)
2. Power supply (3.3V requirement)
3. Ethernet cable and router settings
4. Arduino IDE board and library installation

Good luck! 🚀
