//-----------------------------------------------------------------
//  名称: 16键解码芯片74C922应用
//-----------------------------------------------------------------
//  说明: 本例因为使用了74C922解码芯片,使得程序代码非常简单
//      在按下不同按键时,数码管将显示对应键值.
//
//-----------------------------------------------------------------
#define pin (2)
//0~9的共阳数码管段码表
const uint8_t  CA_SEGCODE[] PROGMEM = 
  { 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
volatile uint8_t KEY_Status;
void setup() {
 Serial.begin(9600);
 pinMode(LED_BUILTIN,OUTPUT);
 //pinMode(14, INPUT_PULLUP);
//pinMode(15, INPUT_PULLUP);
//pinMode(16, INPUT_PULLUP);
//pinMode(17, INPUT_PULLUP);
/*74C922引脚输出到Arduino*/
DDRC &= 0xF0;//将14,15,16,17端口设置为输入模式，同上
PORTC &= 0xF0; //端口C高4位设置为低电平，低4位保持不变
/*BCD数码管驱动引脚*/
DDRD |= 0xF0;//将4,5,6,7端口设置为输出模式
PORTD &= 0xF0; //端口C高4位保持不变，低4位输出低电平

 /*中断mode：
LOW 当引脚为低电平时，触发中断
CHANGE 当引脚电平发生改变时，触发中断
RISING 当引脚由低电平变为高电平时，触发中断
FALLING 当引脚由高电平变为低电平时，触发中断.
*/
 attachInterrupt(digitalPinToInterrupt(pin),ISR_KEYControl, FALLING);
}

void loop() {
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  delay(1000);
}
/*中断服务函数*/
void ISR_KEYControl() { 
 KEY_Status = PINC & 0x0F  ;//获取低四位的数据
 Serial.println(KEY_Status,HEX);
  KEY_Status <<=4 ;//将获取的数据移到高四位
  PORTD &=0x0f;//清空寄存器高四位的数据
  PORTD |=KEY_Status;//将数据赋值到高四位
}
