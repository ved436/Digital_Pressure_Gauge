# Digital Pressure Gauge (EV Monitor)

A simple embedded systems project that measures and displays atmospheric pressure and temperature in real time using an Arduino UNO R4, BMP180 sensor, and OLED display.

The system continuously monitors environmental conditions and provides visual status indication through LEDs based on pressure variations.

## Features

- Real-time pressure monitoring (hPa)
- Real-time temperature monitoring (°C)
- 128×64 OLED display output
- Green LED indicates stable pressure
- Red LED indicates significant pressure change
- I2C communication for sensor and display
- Low-cost and beginner-friendly implementation

## Hardware Used

- Arduino UNO R4 Minima
- BMP180 Pressure & Temperature Sensor
- 0.96" OLED Display (SSD1306)
- Green LED
- Red LED
- 220Ω Resistors
- Breadboard
- Jumper Wires

## Circuit Connections

### BMP180

| BMP180 | Arduino UNO R4 |
|---------|---------------|
| VCC | 3.3V |
| GND | GND |
| SDA | SDA (A4) |
| SCL | SCL (A5) |

### OLED Display

| OLED | Arduino UNO R4 |
|-------|---------------|
| VCC | 5V |
| GND | GND |
| SDA | SDA (A4) |
| SCL | SCL (A5) |

### LEDs

| Component | Arduino Pin |
|------------|------------|
| Green LED | D7 |
| Red LED | D8 |

## Working Principle

1. BMP180 measures atmospheric pressure and temperature.
2. Arduino reads sensor values through I2C communication.
3. OLED displays live readings.
4. Pressure variation is compared with the previous reading.
5. If pressure change exceeds 0.3 hPa:
   - Red LED turns ON
   - Green LED turns OFF
6. Otherwise:
   - Green LED remains ON
   - Red LED remains OFF

## Libraries Required

```cpp
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
