#include<LiquidCrystal.h>
LiquidCrystal lcd(4,5,0,1,2,3);////RS,E,DB4-DB7
void setup(){
    lcd.begin(16,2);
        lcd.print("PERSEVERANCE");
          delay(2000);
  lcd.clear();
}
void loop(){
  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("hELLO WORLD!");
   
    lcd.setCursor(0,1);
    lcd.print("PERSEVERANCE");

    delay(3000);
}
