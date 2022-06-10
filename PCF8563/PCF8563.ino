#include <Wire.h>
#include <Rtc_Pcf8563.h>//点击这里会自动打开管理库页面: http://librarymanager/All#Rtc_Pcf8563
/* add the lcd support */ 
#include <LiquidCrystal.h>//点击这里会自动打开管理库页面: http://librarymanager/All#LiquidCrystal

//init the real time clock
Rtc_Pcf8563 rtc;

/* initialize the library objects */
// LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LiquidCrystal lcd(4 ,9 ,5 ,6 ,7 ,8);


const long interval = 1000;//设置延时时间间隔

unsigned long previousMillis = 0;
 unsigned char weeklist[7][3]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
void setup()
{
   pinMode(LED_BUILTIN, OUTPUT);//板载led灯
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);//初始化LCD1602,16代表每行可显示16个字符，2代表可显示的行数
  
/**程序第一次烧录时，需要设定一次开始的时间到pcf8563里面**/
//Proteus仿真可以不用初始化pcf8563，会主动读取电脑系统时间。
//在仿真时也可以启用，则会从下面的设置时间开始运行并显示。
 /*  
// rtc.initClock();
  //程序第一次烧录时，设定一次开始的时间。
// rtc.setDate(2, 1, 1, 0, 22);  //日，周，月，世纪，年
// rtc.setTime(14, 25, 40);  //hr, min, sec
*/
}

void loop()
{
  unsigned char *week1;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
 digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));//状态翻转
   /**下面是显示具体时-分-秒**/
  lcd.setCursor(3, 1);
// lcd.print(rtc.formatTime(RTCC_TIME_HM));//显示格式00:00
  lcd.print(rtc.formatTime());//显示格式：14:39:22
  lcd.setCursor(13, 0);     
          switch(rtc.getWeekday()){
            case 7: lcd.print("Sun");break;
            case 6: lcd.print("Sat");break;
            case 5: lcd.print("Fri");break;
            case 4: lcd.print("Thu");break;
            case 3: lcd.print("Wed");break;
            case 2: lcd.print("Tue");break;
            case 1: lcd.print("Mon");break;
         default :lcd.print("---");break;
          } 
//  lcd.setCursor(13, 1); 
//   lcd.print(*weeklist[rtc.getWeekday()]);//显示星期1代表日，2->星期一
 /**下面是显示日期**/
  lcd.setCursor(2,0);
  lcd.print(rtc.formatDate(RTCC_DATE_ASIA));//显示格式：2022年1月2日
 // lcd.print(rtc.formatDate()); //显示格式：/00/00/00
     previousMillis = currentMillis;
  }     
}
