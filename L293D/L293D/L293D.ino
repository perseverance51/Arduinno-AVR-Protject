/*
  MX1508 四通道双路有刷直流马达驱动模块
  简易控制电机（MOTOR-A）连续正转,PWM设置为占空比：50%，频率2000

  1、安装库：// 点击这里会自动打开管理库页面: http://librarymanager/All#MX1508
  2、实验接线方法
  MX1508模块   Ardunio Uno
  GND---------GND接地线
  VCC---------5V 接电源
  IN1---------D9（PWM）
  IN2 ------- D10(PWM)
*/

#include <MX1508.h>

#define PINA 9
#define PINB 10
#define NUMPWM 2
#define PWM 500 //脉宽宽度，占空比50%，最大值1000对应100%
#define interruptPin 2    //定义中引脚2或者3号引脚都可以
//FAST_DECAY or SLOW_DECAY
MX1508 motorA(PINA, PINB, FAST_DECAY, NUMPWM);
volatile bool State = false;//初始状态
int resolution = 1000;

void use() {
  State = !State;
}
void setup() {
    Serial.begin(115200);
     pinMode(interruptPin, INPUT_PULLUP);//内部上拉
     attachInterrupt(digitalPinToInterrupt(interruptPin), use, FALLING);//开中断，下降沿触发
    //设置pwm频率
    motorA.setPWM16(2,resolution); // prescaler at 8, resolution 1000, PWM frequency = 16Mhz/8/1000=2000Hz
  // prescalar 1=1, 2=8, 3=64, 4=256, 5 =1028
    /*------------ setPWM16 Class function is defined as below-----------------
   void MX1508::setPWM16(uint8_t prescaler, unsigned int resolution){
   if(prescaler > 5 || prescaler == 0) prescaler = 3; // default to 64 if not in range.
    DDRB  |= _BV(PB1) | _BV(PB2);       // set pin 9and 10 as outputs 
      TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11);    // non-inverting PWM, mode 14 fastPWM, TOP =ICR1
    TCCR1B = _BV(WGM13) | _BV(WGM12) | prescaler ;  
    ICR1 = resolution;
    _pwmResolution = resolution;
    _useAnalogWrite16 = true; 
  }
  */
  }

void loop() {
  if(State)motorA.motorGo(PWM);
else motorA.motorGo(0);
}
