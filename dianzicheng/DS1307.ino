/* 
 *  PCF8574+LCD1602+MPX4250电子秤
 * Created:   2022年6月22日23:44:21
 * Processor: ATmega328P
 * Compiler:  Arduino AVR
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>//点击这里会自动打开管理库页面: http://librarymanager/All#LiquidCrystal_I2C
#define  pinBuzzer (5)
char SensorPort = 3; // Set MAP sensor input on Analog port 5

double SensorValue = 0; //Save Sensor input Voltage
float ResultkPa = 0; // Save Result in kPa
float ResultBar = 0; // Save Result in Bar
LiquidCrystal_I2C lcd(0x27,16,2);
float delta=1e-5;
bool comparDoubleNum(float x,float y)//当x与0之差的绝对值小于0.00001（即：1e-5）时 认为x等于y
{
    /*if(x>y)  return 1;
    else if(x<y)  return -1;
    else  return 0;*/
    //上面的写法会出现浮点数计算精度的误差 。需要改用下面的方法来比较浮点数x和y之间的大小关系。
    if((x-y)>delta) return 1;//x>y
    else if((x-y)<-delta) return 0;//x < y
    else return 1;//x ==y
}

//单纯比较两个浮点数是否相等
int isEqual(double x,double y)
{
    if(fabs(x-y)>delta)  0;//不等
    else return 1;//相等
}
void buzzer()
{
  long frequency = 800; //频率, 单位Hz

   //用tone()函数发出频率为frequency的波形
   tone(pinBuzzer, frequency );
   delay(200); //等待1000毫秒  
   noTone(pinBuzzer);//停止发声
  // delay(2000); //等待2000毫秒
}
void setup ()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
 pinMode(pinBuzzer, OUTPUT); //设置pinBuzzer脚为输出状态
}

void loop () 
{    String s1 = "g";
    String s2 = "kg";
  String stringOne;
     SensorValue = analogRead(SensorPort);
     ResultkPa = (SensorValue*(.00488)/(.022)+20);
    //1Kpa = 0.0101972kg/cm2,
     ResultBar = (ResultkPa * 0.01) - 1.0172; //multiply (1 kPa x 0.01 bar) and deduct atmospheric pressure
Serial.println(ResultBar);
lcd.setCursor(0,0);
if(ResultBar<1.0&&fabs(ResultBar-1)>1e-6)
//if(comparDoubleNum(ResultBar,1.0) ==false)//同上
{ 
  ResultBar *=1000;//换算成克 
 stringOne = String(ResultBar, 2);
  stringOne.concat(s1);
}else
{
stringOne = String(ResultBar, 2);
  stringOne.concat(s2);
}
lcd.clear();
 lcd.print(stringOne);    
stringOne="";
 // lcd.print("hello world");
     ResultkPa = 0;
    ResultBar = 0;
    SensorValue = 0;
  delay(300);
buzzer();
}
