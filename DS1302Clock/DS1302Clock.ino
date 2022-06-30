// DS1302:  RST pin    -> Arduino Digital 2
//          DAT pin   -> Arduino Digital 3
//          CLK pin  -> Arduino Digital 5
#include <LiquidCrystal.h>
#include <DS1302.h>//https://gitee.com/li-baoyu/arduino/tree/master/DS1302
#define buzzer (10)
LiquidCrystal lcd(12, 11, 9, 8, 7, 6);
DS1302 rtc(2, 3, 5);
int j=0;//记录定时设定分钟数
int time=0;//remine the last time 
int button=13;//13口控制按钮
boolean onoff= LOW; //记录按钮状态
boolean timefix=LOW;//记时器开关，LOW表示未定时，HIGH表示定时
unsigned long buttonHoldTime = 0;//按钮按下持续时间
int buttonStateOld;//按钮上一时刻状态
int buttonState;//按钮本时刻状态
 
void ting()//控制蜂鸣器发声
{
    int checkstate = digitalRead(button);
    for(int i=0;i<80;i++)//输出一个频率的声音
    {
      digitalWrite(buzzer,HIGH);//发声音
      delay(10);//延时1ms
      digitalWrite(buzzer,LOW);//不发声音
      delay(10);//延时ms
    }
    for(int i=0;i<100;i++)//输出另一个频率的声音,这里的100与前面的80一样，用来控制频率，可以自己调节
    {
      digitalWrite(buzzer,HIGH);
      delay(5);
      digitalWrite(buzzer,LOW);
      delay(5);
    }
}
 
void clockdate()//1602显示时间
{
        lcd.clear(); //清屏
        lcd.setCursor(0,0);
        lcd.print(rtc.getDateStr(FORMAT_LONG,FORMAT_BIGENDIAN, '-'));//从1302的库文件可以看出，这里有下面几种格式FORMAT_BIGENDIAN:2010-01-01;FORMAT_LITTLEENDIAN:01-01-2010
        lcd.setCursor(11,0);
        lcd.print(rtc.getDOWStr());
        lcd.setCursor(14,0);
        lcd.print("    ");
        lcd.setCursor(0, 1) ;
        lcd.print(rtc.getTimeStr());
}
 
void setup()
{
  lcd.begin(16, 2);  //初始化LCD
  pinMode(buzzer,OUTPUT);//设置数字IO脚模式，OUTPUT为输出
  pinMode(button,INPUT);//设置引脚为输入模式
  // 设置时钟初始值
  rtc.halt(false);
  rtc.writeProtect(false);
 
  rtc.setDOW(MONDAY);        // 设置星期
  rtc.setTime(22, 12,00);     //设置时间10:12:00
  rtc.setDate(27, 6, 2022);   // 设置日期2022-6-27
  rtc.writeProtect(true);
}
 
void loop()
{ 
  buttonState = digitalRead(button);
  delay(20);
  if (buttonState==HIGH && buttonStateOld==LOW)//按钮状态发生变化
  {
    buttonHoldTime = millis();//用millis()时间函数来记时，该函数最长记录时间为9小时22分，由于本程序最多记录60分钟，所以可以使用
    buttonStateOld = buttonState;
 
    if (onoff==HIGH)//当进入定时设置状态时
    {
          if (j>59)
          {
              j=0;
              timefix=LOW;
          }
          else
          {
              j=j+1;
              timefix=HIGH;
               
          }
          lcd.setCursor(11,0); 
          lcd.print(j); 
    }
  }
  else if (buttonState ==HIGH && buttonStateOld==HIGH)//判断按钮是否持续按下
  {
     if (millis()-buttonHoldTime>3000)//当按钮持续按下3秒种进入定时状态
     {
        buttonStateOld=LOW;
        if (onoff==LOW)//进入
        {
          j=0;
          timefix=LOW;
          lcd.clear(); //清屏
          lcd.setCursor(0,0);
          lcd.print("Fixed Time:");
          lcd.setCursor(11,0); 
          lcd.print(j); 
          lcd.setCursor(13,0);
          lcd.print("min");
           
          onoff=HIGH;
        }
        else//退出
        {
          clockdate();
  //        Serial.println(rtc.getTimeStr());
          buttonHoldTime = millis();
          onoff= LOW;
        }
     }
     else
     {
       buttonStateOld =buttonState;
     }
  }
  else
  {
    buttonStateOld =buttonState;
  }
   if (onoff==LOW)
   {
     clockdate();
   } 
   if (timefix==HIGH && j>0 && onoff==LOW)
    {
      unsigned long delaytime=j*60000 - 1000;//把分钟计算成秒
 
      if ((millis()-buttonHoldTime)>=delaytime )
      {
          do
          {
            buttonState = digitalRead(button);
            ting();
          }while (buttonState==LOW);//当按下按钮后，停止蜂鸣
          j=0;
      }
      else
      {
        clockdate();
      }
    }
 
  delay(800);
}
