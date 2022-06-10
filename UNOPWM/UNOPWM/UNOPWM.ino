/*
 * TCCRnA和TCCRnB就是用来设置时钟的计数位数
 * WGM：用来设置时钟的模式
 * CS:时钟选择位
 * 输出模式控制位（COMnA和COMnB:使能/禁用/反相 输出A和输出B
 * 输出比较器（OCRnA和OCRnB）：当计数器等于这两个值时，输出值根据不同的模式进行变化
不同定时器的这些设置位稍有不同，
_BV()是把1左移N位的函数,_BV(7)相当于(1<<7)
OC2A、OC2B不是寄存器，只是pin11和pin3引脚的别名，其实物理上，OC2A是pin11、OC2B是pin3。不要把OC2A/B和 OCR2A/B搞混了
TCCR2A/B就是来控制Timer2如下的3个设置：
Waveform Generation Mode （波形产生模式）
Clock Select（降频预除数）
Compare Match Output Mode （比较输出模式）

 */
void setup() {
pinMode(3, OUTPUT);  
pinMode(11, OUTPUT);  
 //控制Timer2,快速PWM
//TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20); 
//相位修正PWM
TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20); 
TCCR2B = _BV(CS22);  //100 ->1/64分频

OCR2A = 180;  //对应作用于 pin11，
OCR2B = 50;  //对应作用于 pin3
  //CS2  分频系数  Frequency(频率)
  //001    1        31372.55
  //010    8        3921.16
  //011    32       980.39
  //100    64       490.20   <--DEFAULT
  //101    128      245.10
  //110    256      122.55
  //111    1024     30.64
}
void loop() {
}
