
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>//点击这里会自动打开管理库页面: http://librarymanager/All#LiquidCrystal_I2C
//#include <DS18B20.h>
//DS18B20 ds(2);
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#include <OneWire.h>
OneWire  ds(0); 
void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);//在第一行的第二个字符开始显示内容
  lcd.print("N00000000");
  lcd.setCursor(3,1);//在第二行的第二个字符开始显示字符
  lcd.print("PERSEG");
}


void loop()
{
    byte type_s;
    byte addr[8];
      byte data[12];
  float celsius, fahrenheit;
    if ( !ds.search(addr)) {
      lcd.setCursor(2,0);//在第一行的第二个字符开始显示内容
   lcd.println("No addresses");
    ds.reset_search();
    delay(250);
    return;
  }
      lcd.setCursor(0,0);//在第一行的第二个字符开始显示内容
    lcd.print("Ad:");
     lcd.setCursor(3,1);
 for (byte  i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
   lcd.print(data[i], HEX);
  }
   int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
    lcd.setCursor(10,1);
     lcd.print(celsius);
   //  lcd.print("C");

  
  delay(10000);
}
