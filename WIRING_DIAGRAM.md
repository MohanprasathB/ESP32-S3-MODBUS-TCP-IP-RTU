# ESP32-S3 WROOM1 to W5500 Wiring Diagram

## Pin Connection Table

```
ESP32-S3 WROOM1          W5500 Module
================          ============
3.3V            -------> VCC
GND             -------> GND
GPIO 11 (MOSI)  -------> MOSI (or SDI/DI)
GPIO 13 (MISO)  -------> MISO (or SDO/DO)
GPIO 12 (SCK)   -------> SCK (or SCLK)
GPIO 10 (CS)    -------> CS (or SCS)
GPIO 9 (RST)    -------> RST (or RESET) [Optional]
```

## Visual Wiring Guide

```
     ESP32-S3 WROOM1                    W5500 Module
    ┌─────────────────┐              ┌──────────────┐
    │                 │              │              │
    │     3.3V ●──────┼──────────────┼──●  VCC     │
    │      GND ●──────┼──────────────┼──●  GND     │
    │                 │              │              │
    │  GPIO 11 ●──────┼──────────────┼──●  MOSI    │
    │  GPIO 13 ●──────┼──────────────┼──●  MISO    │
    │  GPIO 12 ●──────┼──────────────┼──●  SCK     │
    │  GPIO 10 ●──────┼──────────────┼──●  CS      │
    │   GPIO 9 ●──────┼──────────────┼──●  RST     │
    │                 │              │              │
    │                 │              │  ┌─────────┐ │
    │                 │              │  │Ethernet │ │
    │                 │              │  │  Port   │ │
    │                 │              │  └─────────┘ │
    └─────────────────┘              └──────────────┘
         USB-C                         [RJ45 Port]
```

## Important Notes

### Power Supply
- **NEVER** connect 5V to W5500 VCC - use 3.3V only!
- ESP32-S3 can be powered via USB-C
- W5500 draws approximately 100-150mA during operation
- Ensure your power supply can handle both modules

### SPI Pins
The pins used are the default HSPI pins for ESP32-S3:
- **MOSI**: GPIO 11 (Master Out Slave In)
- **MISO**: GPIO 13 (Master In Slave Out)
- **SCK**: GPIO 12 (Serial Clock)
- **CS**: GPIO 10 (Chip Select) - can be any GPIO

### Optional RST Pin
- The RST (reset) pin connection is optional but recommended
- Using GPIO 9 allows software reset of the W5500
- If not used, W5500 will reset on power-up only

### Alternative Pins
You can use different GPIO pins if needed. Just modify these lines in the code:
```cpp
#define W5500_CS    10  // Change to your CS pin
#define W5500_RST   9   // Change to your RST pin
#define SPI_MOSI    11  // Change to your MOSI pin
#define SPI_MISO    13  // Change to your MISO pin
#define SPI_SCK     12  // Change to your SCK pin
```

## W5500 Module Variations

Different W5500 modules may have slightly different pin labels:

| Common Labels | Alternative Labels |
|---------------|-------------------|
| MOSI          | SDI, DI, SI       |
| MISO          | SDO, DO, SO       |
| SCK           | SCLK, CLK         |
| CS            | SCS, SS           |
| RST           | RESET, nRST       |

Refer to your specific module's documentation for exact pin labels.

## Connection Checklist

Before powering up:
- [ ] VCC connected to 3.3V (not 5V!)
- [ ] GND connected
- [ ] MOSI connected to GPIO 11
- [ ] MISO connected to GPIO 13
- [ ] SCK connected to GPIO 12
- [ ] CS connected to GPIO 10
- [ ] RST connected to GPIO 9 (optional)
- [ ] All connections are secure
- [ ] No short circuits between pins
- [ ] Ethernet cable connected to W5500 RJ45 port
- [ ] Ethernet cable connected to router/switch

## Troubleshooting

### No Response from W5500
1. Check all connections match the table above
2. Verify 3.3V power is present
3. Ensure GND is connected
4. Try removing RST connection
5. Check for bent or damaged pins

### Intermittent Connection
1. Use shorter jumper wires (< 20cm recommended)
2. Ensure solid connections (no loose wires)
3. Add a 0.1µF capacitor between VCC and GND on W5500
4. Keep wires away from power supplies and motors

### Link LED Not Lighting
1. Check Ethernet cable
2. Verify cable is connected to active network port
3. Try different Ethernet cable
4. Check router/switch port is working
