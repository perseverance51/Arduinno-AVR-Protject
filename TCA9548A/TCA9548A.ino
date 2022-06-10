#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


// Select I2C BUS
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.print(bus);
}

void setup() {
  Serial.begin(115200);

  // Start I2C communication with the Multiplexer
  Wire.begin();

  // Init OLED display on bus number 2 (display 1)
  TCA9548A(1);
  if(!display1.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  } 
  // Clear the buffer
  display1.clearDisplay();

  // Write to OLED on bus number 2
  TCA9548A(1);
  display1.setTextSize(8);
  display1.setTextColor(WHITE);
  display1.setCursor(45, 10);
  // Display static text
  display1.println("123");
  display1.display(); 
  
 delay(2000);
  Serial.println(F("READY"));
}
 
void loop() {
    TCA9548A(1);
  if(!display1.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  } 
  // Clear the buffer
  display1.clearDisplay();

  // Write to OLED on bus number 2
  TCA9548A(1);
  display1.setTextSize(8);
  display1.setTextColor(WHITE);
  display1.setCursor(45, 10);
  // Display static text
  display1.println("123");
  display1.display();

   delay(2000);
   
}
