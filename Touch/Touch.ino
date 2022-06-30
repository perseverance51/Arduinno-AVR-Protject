// readCapacitivePin
//输入:Arduino pin number
//输出:一个数值范围：从0到17表示
//引脚上有多少电容值
//当你触摸大头针或其他任何东西时,
//数值会变大
#define ledPin  13
int capval;
void setup()
{
pinMode(ledPin, OUTPUT);
Serial.begin(9600);
Serial.println("Touch senser");
}
 
void loop ()
{
digitalWrite(ledPin,LOW);//板载led
capval = readCapacitivePin(8);//触摸引脚
Serial.println(capval, DEC);
if (capval > 2) {
// turn LED on:
digitalWrite(ledPin, HIGH);
delay(10);
}
}

uint8_t readCapacitivePin(int pinToMeasure) {
  // Variables used to translate from Arduino to AVR pin naming
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
//这里我们转换输入的引脚编号
// Arduino pin number to AVR PORT, pin, DDR，
//要操作的寄存器位。
  byte bitmask;
  port = portOutputRegister(digitalPinToPort(pinToMeasure));
  ddr = portModeRegister(digitalPinToPort(pinToMeasure));
  bitmask = digitalPinToBitMask(pinToMeasure);
  pin = portInputRegister(digitalPinToPort(pinToMeasure));
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  uint8_t SREG_old = SREG; //back up the AVR Status Register
  // Prevent the timer IRQ from disturbing our measurement
  noInterrupts();//取消中断
  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;
 
//当接触到离开需要多长时间。
//减少每次读取引脚之间的硬件周期数，
//增加灵敏度。
  uint8_t cycles = 17;
  if (*pin & bitmask) { cycles =  0;}
  else if (*pin & bitmask) { cycles =  1;}
  else if (*pin & bitmask) { cycles =  2;}
  else if (*pin & bitmask) { cycles =  3;}
  else if (*pin & bitmask) { cycles =  4;}
  else if (*pin & bitmask) { cycles =  5;}
  else if (*pin & bitmask) { cycles =  6;}
  else if (*pin & bitmask) { cycles =  7;}
  else if (*pin & bitmask) { cycles =  8;}
  else if (*pin & bitmask) { cycles =  9;}
  else if (*pin & bitmask) { cycles = 10;}
  else if (*pin & bitmask) { cycles = 11;}
  else if (*pin & bitmask) { cycles = 12;}
  else if (*pin & bitmask) { cycles = 13;}
  else if (*pin & bitmask) { cycles = 14;}
  else if (*pin & bitmask) { cycles = 15;}
  else if (*pin & bitmask) { cycles = 16;}
 
  // time -critical section结束;将中断重新打开(如果它们之前是打开的)，或者关闭(如果它们之前是关闭的)
  SREG = SREG_old;
 
//放电引脚再次设置低和输出
//如果你想的话，把针放低是很重要的
//可以触摸超过一个传感器在同一时间-如果
//当你触摸时，传感器被左拉高
//如果有两个传感器，你的身体就会在它们之间传递电荷
//传感器。
  *port &= ~(bitmask);
  *ddr  |= bitmask;
 
  return cycles;
}
