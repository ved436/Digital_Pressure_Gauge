#include <Wire.h> 
#include <Adafruit_BMP085.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 
 
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
 
// ===== LED PINS ===== 
#define GREEN_LED 7 
#define RED_LED 8 
 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); 
Adafruit_BMP085 bmp; 
 
// ===== PRESSURE VARIABLES ===== 
float prevPressure = 0; 
 
void setup() { 
  Serial.begin(9600); 
  Wire.begin();           // Start I2C bus 
 
  // LED setup 
  pinMode(GREEN_LED, OUTPUT); 
  pinMode(RED_LED, OUTPUT); 
 
  // OLED init 
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("OLED not found"); 
    while (1); 
  } 
 
  // BMP180 init 
  if (!bmp.begin()) { 
    Serial.println("BMP180 not found"); 
    while (1); 
  } 
 
  display.clearDisplay(); 
  display.display(); 
} 
 
void loop() { 
  float temp     = bmp.readTemperature(); 
  float pressure = bmp.readPressure() / 100.0;  // Pa to hPa 
 
  // ===== LED LOGIC ===== 
  float diff = abs(pressure - prevPressure); 
 
  digitalWrite(GREEN_LED, HIGH);   // Default: stable (green ON) 
  digitalWrite(RED_LED, LOW); 
   if (diff > 0.3) {               // Threshold: 0.3 hPa 
    digitalWrite(GREEN_LED, LOW); 
    digitalWrite(RED_LED, HIGH); 
  } 
 
  prevPressure = pressure; 
 
  // ===== DISPLAY ===== 
  display.clearDisplay(); 
 
  // TOP (YELLOW REGION) — Title 
  display.setTextSize(2); 
  display.setTextColor(WHITE); 
  display.setCursor(5, 2); 
  display.print("EV monitor"); 
 
  // Dividing LINE at y=25 
  display.drawLine(0, 25, 128, 25, WHITE); 
 
  // BOTTOM (BLUE REGION) — Readings 
  display.setTextSize(2); 
  display.setCursor(0, 30); 
  display.print("Temp:"); 
  display.print(temp, 1); 
  display.print("C"); 
 
  display.setCursor(0, 50); 
  display.print("PR:"); 
  display.print(pressure, 1); 
  display.print("Pa"); 
 
  display.display(); 
  delay(1000); 
}