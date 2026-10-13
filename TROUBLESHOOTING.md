# Troubleshooting Guide - ESP32-S3 with W5500

## Common Issues and Solutions

### 1. "No Hardware Detected" Error

**Symptoms:**
- Serial output shows "No Hardware - Check wiring and SPI pins!"
- W5500 not responding to SPI commands

**Solutions:**

#### Check Power Connections
- [ ] Verify W5500 VCC is connected to ESP32-S3 **3.3V** (NOT 5V!)
- [ ] Verify GND is connected
- [ ] Use multimeter to check voltage at W5500 VCC pin (should be 3.3V)
- [ ] Try connecting VCC directly to ESP32-S3 3.3V pin

#### Check SPI Connections
- [ ] Verify MOSI is connected to GPIO 11
- [ ] Verify MISO is connected to GPIO 13
- [ ] Verify SCK is connected to GPIO 12
- [ ] Verify CS is connected to GPIO 10
- [ ] Use short jumper wires (< 20cm)
- [ ] Ensure all connections are firm

#### Try Different CS Pin
```cpp
// In your sketch, try changing CS pin:
#define W5500_CS 5  // Try GPIO 5 instead of 10
```

#### Add Pull-up Resistor
- Add 10kΩ resistor between W5500 CS pin and 3.3V
- This can help with signal integrity

---

### 2. "Link OFF - Check Ethernet Cable" Error

**Symptoms:**
- W5500 is detected but shows "Link OFF"
- No IP address obtained
- Link LED on W5500 not lit

**Solutions:**

#### Check Cable Connections
- [ ] Ensure Ethernet cable is fully inserted into W5500 RJ45 port
- [ ] Ensure other end is connected to active router/switch port
- [ ] Try different Ethernet cable (must be Cat5 or better)
- [ ] Try different router/switch port

#### Check Router/Switch
- [ ] Verify router/switch is powered on
- [ ] Check port LED on router/switch lights up
- [ ] Try connecting another device to same port to verify it works

#### Cable Type
- [ ] Use straight-through cable (not crossover)
- [ ] Cable should be Cat5, Cat5e, or Cat6

---

### 3. "Failed to Obtain IP Address via DHCP" Error

**Symptoms:**
- W5500 detected and Link is ON
- DHCP times out without getting IP address

**Solutions:**

#### Increase DHCP Timeout
```cpp
// In your sketch, increase timeout:
Ethernet.begin(mac, 60000, 4000);  // 60 sec total, 4 sec response
```

#### Check Router DHCP Settings
- [ ] Log into router admin panel
- [ ] Verify DHCP server is enabled
- [ ] Check available IP addresses in DHCP pool
- [ ] Check DHCP lease time settings

#### Try Static IP Instead
- Use `03_W5500_Static_IP_Test` sketch
- Configure IP address manually
- Ensure IP is not used by another device

#### Check Network Security
- [ ] Disable MAC address filtering temporarily
- [ ] Check if your router blocks new devices
- [ ] Try connecting to different network (mobile hotspot with Ethernet adapter)

---

### 4. Upload Fails to ESP32-S3

**Symptoms:**
- "Failed to connect to ESP32" error
- "A fatal error occurred" message
- Upload times out

**Solutions:**

#### Put ESP32-S3 into Download Mode
1. Hold **BOOT** button
2. Press **RESET** button (while holding BOOT)
3. Release **RESET** button
4. Release **BOOT** button
5. Click Upload in Arduino IDE

#### Check USB Connection
- [ ] Use USB cable that supports data (not charge-only)
- [ ] Try different USB port on computer
- [ ] Try different USB cable

#### Arduino IDE Settings
- **Tools → USB CDC On Boot:** "Enabled"
- **Tools → Upload Speed:** Try 115200 (slower but more reliable)
- **Tools → Port:** Select correct COM port

#### Driver Issues (Windows)
- Install CH340 or CP2102 drivers if needed
- Check Device Manager for unknown devices

---

### 5. Intermittent Connection Issues

**Symptoms:**
- Connection works sometimes but not always
- Random disconnections
- Unreliable behavior

**Solutions:**

#### Improve Power Supply
- [ ] Use USB power supply with adequate current (1A minimum)
- [ ] Add 100µF capacitor between ESP32-S3 VCC and GND
- [ ] Add 10µF capacitor between W5500 VCC and GND

#### Reduce SPI Speed
```cpp
// Add after SPI.begin():
SPI.setClockDivider(SPI_CLOCK_DIV8);  // Slower but more stable
```

#### Shorten Connections
- [ ] Use shortest possible jumper wires
- [ ] Keep wires away from power supplies
- [ ] Avoid running SPI wires parallel to power wires

#### Add Delays
```cpp
void setup() {
  // ... SPI initialization ...
  delay(500);  // Add delay before Ethernet.begin()
  Ethernet.begin(mac);
}
```

---

### 6. Web Server Not Accessible

**Symptoms:**
- ESP32 reports IP address
- Cannot access web page in browser

**Solutions:**

#### Verify IP and Network
- [ ] Ping ESP32 IP from computer: `ping 192.168.1.XXX`
- [ ] Ensure computer and ESP32 are on same network/subnet
- [ ] Check firewall settings on computer

#### Browser Issues
- [ ] Try different browser
- [ ] Use private/incognito mode
- [ ] Clear browser cache
- [ ] Type `http://` explicitly: `http://192.168.1.XXX`

#### Check Serial Output
- [ ] Verify "New client connected" appears when accessing
- [ ] Look for error messages

---

### 7. MAC Address Conflicts

**Symptoms:**
- Multiple ESP32 devices on network interfere with each other
- Connection drops when second device connects

**Solutions:**

#### Use Unique MAC Addresses
```cpp
// Device 1:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Device 2:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };

// Device 3:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF };
```

Change the last byte for each device!

---

### 8. Library Compilation Errors

**Symptoms:**
- "Ethernet.h: No such file or directory"
- Compilation errors

**Solutions:**

#### Install Ethernet Library
1. **Sketch → Include Library → Manage Libraries**
2. Search for "Ethernet"
3. Install "Ethernet by Arduino"

#### Try Alternative Libraries
If standard Ethernet library doesn't work:
- Try "Ethernet2" library
- Try "Ethernet3" library
- These are specifically updated for W5500

---

## Diagnostic Sketch

Use this to check your setup:

```cpp
#include <SPI.h>
#include <Ethernet.h>

#define W5500_CS 10

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n=== W5500 Diagnostic ===\n");
  
  SPI.begin(12, 13, 11, W5500_CS);
  Ethernet.init(W5500_CS);
  
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  
  Serial.print("Hardware Status: ");
  Serial.println(Ethernet.hardwareStatus());
  
  Ethernet.begin(mac, 5000, 5000);
  
  Serial.print("Link Status: ");
  Serial.println(Ethernet.linkStatus());
  
  Serial.print("IP Address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {}
```

**Expected Output:**
- Hardware Status: 4 (W5500)
- Link Status: 1 (Link ON)
- IP Address: 192.168.1.XXX

---

## Still Having Issues?

### Check These Systematically:

1. **Physical Layer:**
   - Power (3.3V at W5500)
   - All 7 wire connections
   - Cable quality and connections

2. **SPI Communication:**
   - Correct GPIO pins
   - SPI initialization
   - CS pin configuration

3. **Network Layer:**
   - DHCP server availability
   - IP configuration
   - Network connectivity

4. **Software Layer:**
   - Correct library installed
   - Correct board selected
   - Code compiles without errors

### Get Help:
If still stuck, gather this information:
- Which test sketch you're running
- Complete Serial Monitor output
- Your wiring setup (photo if possible)
- Arduino IDE version
- ESP32 board package version
