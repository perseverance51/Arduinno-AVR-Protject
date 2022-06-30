//-----------------------------------------------------------------
//  名称: 74HC148扩展中断
//-----------------------------------------------------------------
//  说明: 通过74LS148扩展外部中断,对于外部的8个控制开关,任意一个
//      合上都将在pin引脚输出低电平,触发外部中断,优先级最高的是
//      输入引脚7,最低的是输入引脚0.中断触发后,中断例程通过读取
//      3,4,5的输出值,判断是哪一路开关触发了中断.
//
//-----------------------------------------------------------------
//相关引脚定义
#define pin (2) //INT0中断输入
#define LED   (14)//AD0引脚

const uint8_t LED_Pins[] = {6, 7, 8, 9, 10, 11, 12, 13}; //8只LED引脚
uint8_t LED_Status = HIGH;
volatile uint8_t IO_Status;
//-----------------------------------------------------------------
// 初始配置
//-----------------------------------------------------------------
void setup() {  
   Serial.begin(9600);
  pinMode(pin, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
for(unsigned char i =0;i< 8;i++){
pinMode(LED_Pins[i],OUTPUT);
digitalWrite(LED_Pins[i],HIGH);
//pinMode(3, INPUT_PULLUP);
//pinMode(4, INPUT_PULLUP);
//pinMode(5, INPUT_PULLUP);
DDRD &= 0xC7;//将3,4,5端口设置为输入模式，同上
}
/*中断mode：
LOW 当引脚为低电平时，触发中断
CHANGE 当引脚电平发生改变时，触发中断
RISING 当引脚由低电平变为高电平时，触发中断
FALLING 当引脚由高电平变为低电平时，触发中断.
*/
attachInterrupt(digitalPinToInterrupt(pin),ISR_LEDControl, FALLING);


}
//-----------------------------------------------------------------
// 主循环
//-----------------------------------------------------------------
void loop() {
digitalWrite(LED,!digitalRead(LED));
delay(1000);
}
//-----------------------------------------------------------------
// INT0中断程序(当有按键按下时,GS为零,触发INT0中断)
// 中断控制点亮按键对应的LED
//-----------------------------------------------------------------
void ISR_LEDControl() { 
 for(unsigned char i =0;i< 8;i++) digitalWrite(LED_Pins[i],HIGH); 
 IO_Status = PIND & 0x38  ;
 Serial.println(IO_Status,HEX);
 switch(IO_Status){
  case 0x38: digitalWrite(LED_Pins[0],LOW);break;
  case 0x30: digitalWrite(LED_Pins[1],LOW);break;
  case 0x28: digitalWrite(LED_Pins[2],LOW);break;
  case 0x20: digitalWrite(LED_Pins[3],LOW);break;
  case 0x18: digitalWrite(LED_Pins[4],LOW);break;
  case 0x10: digitalWrite(LED_Pins[5],LOW);break;
  case 0x08: digitalWrite(LED_Pins[6],LOW);break;
  case 0x00: digitalWrite(LED_Pins[7],LOW);break;
 }
}
