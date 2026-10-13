# ESP32-S3 WROOM-1 N16R8 DevKit Board Setup

## Your Board Specifications
- **Model:** ESP32-S3 WROOM-1 N16R8
- **Flash Memory:** 16MB
- **PSRAM:** 8MB (Octal SPI)
- **USB:** Native USB support (no external USB-UART chip needed)

## Arduino IDE Configuration

### Step 1: Install ESP32 Board Support
1. Open Arduino IDE
2. Go to **File → Preferences**
3. Add this URL to "Additional Board Manager URLs":
   ```
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```
4. Go to **Tools → Board → Boards Manager**
5. Search for "ESP32"
6. Install **"esp32 by Espressif Systems"** (version 2.0.11 or later recommended)

### Step 2: Board Settings
After installing, configure these settings under **Tools** menu:

| Setting | Value |
|---------|-------|
| **Board** | ESP32S3 Dev Module |
| **USB CDC On Boot** | Enabled |
| **USB DFU On Boot** | Disabled |
| **USB Mode** | Hardware CDC and JTAG |
| **CPU Frequency** | 240MHz (WiFi) |
| **Flash Mode** | QIO 80MHz |
| **Flash Size** | 16MB (128Mb) |
| **PSRAM** | OPI PSRAM |
| **Partition Scheme** | 16M Flash (3MB APP/9.9MB FATFS) |
| **Upload Mode** | UART0 / Hardware CDC |
| **Upload Speed** | 921600 |

### Step 3: Verify Port Selection
- **Tools → Port** → Select the COM port for your ESP32-S3
- On Windows: Usually appears as "USB Serial Device (COMx)" or "USB JTAG/serial debug unit"

## Board Features

### Advantages for This Project:
✅ **16MB Flash** - Plenty of space for Modbus TCP/IP and RTU protocols  
✅ **8MB PSRAM** - Large buffers for network data and Modbus registers  
✅ **240MHz CPU** - Fast processing for real-time Modbus communication  
✅ **Native USB** - More reliable uploads, no need for USB-UART drivers  
✅ **Hardware SPI** - Perfect for W5500 Ethernet module  

### Pin Availability:
Your board has plenty of GPIO pins available for:
- SPI communication with W5500
- UART for Modbus RTU
- Additional I/O for sensors/actuators

## USB Connection Notes

### Your board uses Native USB:
- No external USB-UART chip (like CH340 or CP2102)
- Direct USB connection to ESP32-S3
- More reliable and faster communication

### First Time Upload:
If upload fails on first attempt:
1. Hold the **BOOT** button
2. Press the **RESET** button (while holding BOOT)
3. Release **RESET**
4. Release **BOOT**
5. Click Upload in Arduino IDE

After first successful upload, subsequent uploads should work automatically.

## Testing Your Board

### Quick Test Sketch:
```cpp
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n=== ESP32-S3 Board Info ===");
  Serial.print("Chip Model: ");
  Serial.println(ESP.getChipModel());
  Serial.print("Chip Revision: ");
  Serial.println(ESP.getChipRevision());
  Serial.print("CPU Frequency: ");
  Serial.print(ESP.getCpuFreqMHz());
  Serial.println(" MHz");
  Serial.print("Flash Size: ");
  Serial.print(ESP.getFlashChipSize() / (1024 * 1024));
  Serial.println(" MB");
  Serial.print("PSRAM Size: ");
  Serial.print(ESP.getPsramSize() / (1024 * 1024));
  Serial.println(" MB");
  Serial.print("Free Heap: ");
  Serial.print(ESP.getFreeHeap() / 1024);
  Serial.println(" KB");
  Serial.print("Free PSRAM: ");
  Serial.print(ESP.getFreePsram() / 1024);
  Serial.println(" KB");
}

void loop() {
  delay(1000);
}
```

Expected output:
```
=== ESP32-S3 Board Info ===
Chip Model: ESP32-S3
Chip Revision: 0
CPU Frequency: 240 MHz
Flash Size: 16 MB
PSRAM Size: 8 MB
Free Heap: ~300 KB
Free PSRAM: ~8000 KB
```

## Memory Usage Tips

### With 16MB Flash and 8MB PSRAM, you can:
- Store large lookup tables in Flash
- Use PSRAM for large Modbus register maps (up to 65535 registers!)
- Buffer multiple network connections
- Log data locally before transmission
- Store configuration files in SPIFFS/LittleFS

### Accessing PSRAM:
```cpp
// Allocate from PSRAM
void* buffer = ps_malloc(1024 * 1024);  // 1MB buffer in PSRAM

// Check PSRAM availability
if (psramFound()) {
  Serial.println("PSRAM is available");
  Serial.print("PSRAM size: ");
  Serial.println(ESP.getPsramSize());
}
```

## Power Considerations

Your board can be powered via:
- **USB-C port** (5V, recommended for development)
- **5V pin** (external 5V supply)
- **3.3V pin** (external regulated 3.3V supply)

For W5500 + ESP32-S3:
- Total current draw: ~250-400mA (depending on activity)
- USB port can typically supply 500mA-1A (adequate)
- For production, use 5V/1A power supply minimum

## Troubleshooting

### "Timed out waiting for packet header" during upload:
1. Try the BOOT+RESET button sequence above
2. Lower upload speed to 115200
3. Try different USB cable (must support data)
4. Try different USB port

### Board not detected in Arduino IDE:
1. Check USB cable supports data transfer
2. Try installing CP210x or CH340 drivers (some variants use these)
3. Check Windows Device Manager for USB devices

### Serial Monitor shows garbage:
- Ensure baud rate is set to 115200
- Check "USB CDC On Boot" is Enabled

## Next Steps

Now that your board is configured:
1. ✅ Verify board setup with test sketch above
2. ✅ Wire W5500 to ESP32-S3 (see WIRING_DIAGRAM.md)
3. ✅ Upload 01_W5500_Basic_Test sketch
4. ✅ Proceed with remaining tests

Your board is ideal for this project! 🚀
