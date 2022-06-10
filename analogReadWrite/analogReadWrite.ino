
/*模拟信号输入和模拟量输出
 * 
 */
const unsigned char analogOutPin=3;
const int analogInPin = A1;
unsigned int sensorValue = 0;
unsigned outputValue = 0;
                   
void setup() {
// pinMode(analogOutPin,OUTPUT);
// pinMode(analogInPin,INPUT);
 Serial.begin(9600);  //打开串口，设置波特率为9600bps
 delay(1000);
}
 
void loop() {
 int value=0;            //定义值为0，也可以在程序一开始定义
 value=analogRead(analogInPin);  //读取模拟信号输入的值为value
 outputValue = map(value,0,1023,0,255);
 analogWrite(analogOutPin, outputValue);
// constrain(value, 0, 255);
 float val=value*(5.0/1023.0);   //由于模拟信号输入的值为0到1023的值，即为0到5v的值，这里可以转换一下
 Serial.print("sensor = ");    //输出该点的电平是多少

  Serial.println(value);
 Serial.print("valtic = "); 
   Serial.println(val);
  Serial.print("\t output = ");    //输出该点的电平是多少
 Serial.println(outputValue);
 
 delay(1000);

 //val=value*(5.0/1023.0);

}
