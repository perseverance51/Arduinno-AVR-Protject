/*电容测量
一个电容器通过一个电阻，在一个时间常数内充电，定义为T秒，其中
* c = r * c
* TC =以秒为单位的时间常数周期
* R =电阻(欧姆)
* C =电容，单位为法拉(1微法拉(ufd) = .0000001法拉= 10^-6法拉)
＊
*电容器在一个时间常数的电压定义为充电电压的63.2%。
*/

#define analogPin      0          // analog pin for measuring capacitor voltage
#define chargePin      13         //为电容器充电的引脚-连接到充电电阻的一端
#define dischargePin   11          //加快放电过程，但不是必需的
#define resistorValue  10000.0F   // 10K将此更改为您正在使用的任何电阻值
                                  // F formatter tells compiler it's a floating point value F格式化器告诉编译器它是一个浮点值

unsigned long startTime;
unsigned long elapsedTime;//决定了给电容器充电的时间

// 电容变量进行初始化
float microFarads;                // floating point variable to preserve precision, make calculations浮点变量保持精度，进行计算
float nanoFarads;

void setup(){
  pinMode(chargePin, OUTPUT);     // set chargePin to output
  digitalWrite(chargePin, LOW);  

  Serial.begin(9600);             // initialize serial transmission for debugging
}

void loop(){
  digitalWrite(chargePin, HIGH);  // set chargePin HIGH and capacitor charging
  startTime = millis();//开始计时器

  while(analogRead(analogPin) < 648){   // 647是1023的63.2%，相当于满量程电压，直到电容达到总电压的63.2%才退出
  }

  elapsedTime= millis() - startTime;//决定了给电容器充电的时间
 // convert milliseconds to seconds ( 10^-3 ) and Farads to microFarads ( 10^6 ),  net 10^3 (1000)  将毫秒换算成秒(10 ^-3)，将法拉换算成微法拉(10 ^6)，比完净10^3 (1000)
  microFarads = ((float)elapsedTime / resistorValue) * 1000;   
  Serial.print(elapsedTime);       // 将值打印到串口
  Serial.print(" mS    ");         //打印单位和回车


  if (microFarads > 1){//确定单元应该是uf的还是nf的，并相应打印
    Serial.print((long)microFarads);       // print the value to serial port
    Serial.println(" microFarads");         // print units and carriage return
  }
  else
  {
    // if value is smaller than one microFarad, convert to nanoFarads (10^-9 Farad). 
    // This is a workaround because Serial.print will not print floats
    //如果value小于1 microFarad，则转换为nanoFarads (10^-9 Farad)。
  //这是一个解决方案，因为串行。Print将不会打印浮点数

    nanoFarads = microFarads * 1000.0;      // multiply by 1000 to convert to nanoFarads (10^-9 Farads)//乘以1000转换为nanoFarads 
    Serial.print((long)nanoFarads);         // print the value to serial port
    Serial.println(" nanoFarads");          // print units and carriage return
  }

  /* dicharge the capacitor  */
    /*给电容器放电*/
  digitalWrite(chargePin, LOW);             // set charge pin to  LOW 停止充电电容器
  pinMode(dischargePin, OUTPUT);            // set discharge pin to output 允许电容器放电
  digitalWrite(dischargePin, LOW);          // set discharge pin LOW 
  while(analogRead(analogPin) > 0){         // wait until capacitor is completely discharged//等待直到电容器完全放电
  }

  pinMode(dischargePin, INPUT);            // set discharge pin back to input//防止电容器放电
}
