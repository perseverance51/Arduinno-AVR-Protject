int DIN =7;           //TLC5615 1脚
int SCLK =6;          //TLC5615 2脚
int CS =5;            //TLC5615 3脚

int i;          //循环变量
int j;          //循环变量
int a;          //写入DA值 ，十进制 0-1023
int v;          //函数中使用的变量
void WriteTLC5615(int data)     //TLC5615 DAC函数
{
           //Serial.print(data);
           //Serial.print(" ");
           digitalWrite(CS,LOW ); //片选低表示使能，开始接受数据
           digitalWrite(SCLK,LOW ); //时钟先是低，每高低变化一次读一位数据
  
  v=data;     //从函数获得数据值
  v>>=2;      //二进制只能处理8位，10位数据右移2位 （0-1023）
  if (v & B10000000)    //读最高位即第10位
            {
            digitalWrite(DIN,  HIGH);
            digitalWrite(SCLK, HIGH);
            digitalWrite(SCLK, LOW );
            //Serial.print("1");
            }
            else
            {
            digitalWrite(DIN,  LOW);
            digitalWrite(SCLK, HIGH);
            digitalWrite(SCLK, LOW );
            //Serial.print("0");
            }
  if (v & B01000000)    //读次高位即第9位
            {
            digitalWrite(DIN,  HIGH);
            digitalWrite(SCLK, HIGH);
            digitalWrite(SCLK, LOW );
            //Serial.print("1");
            }
            else
            {
            digitalWrite(DIN,  LOW);
            digitalWrite(SCLK, HIGH);
            digitalWrite(SCLK, LOW );
            //Serial.print("0");
            }       //完成最高2位写入

  v=data;       //因为上面右移，导致最低两位数据丢失，重新赋值给V
         
    for(i=0;i<8;i++)    //按位读出低8位数据并写入
         {      
            if (v & B10000000)    //位比较，可以参考TLC5615库，但是不比较最高的第10位，因为这个比较似乎只能在8位内完成。            
            {
            digitalWrite(DIN,  HIGH);
            digitalWrite(SCLK, HIGH);
            digitalWrite(SCLK, LOW );
            //Serial.print("1");
            }
            else
            {
            digitalWrite(DIN,  LOW);
            digitalWrite(SCLK, HIGH);
            digitalWrite(SCLK, LOW );
            //Serial.print("0");
            }
            v = v<<1;     //向左位移
         }        //完成后8位写入
            

            digitalWrite(DIN,  LOW);    //前面完成了有效的2+8位数据后，按TLC5615的设计，后面补两位任意数据达到12位数据
            digitalWrite(SCLK, HIGH);
            digitalWrite(SCLK, LOW );
            //Serial.print("0");
            digitalWrite(DIN,  LOW);
            digitalWrite(SCLK, HIGH);
            digitalWrite(SCLK, LOW );
            //Serial.print("0");  //完成后2位无意义填充数据写入，达到2+8+2=12位数据写入

            digitalWrite(CS,HIGH ); //片选禁止，表示数据传输完成，开始一次DAC转换
           //Serial.println();
}
void setup()
{
  //Serial.begin(9600);
  pinMode(DIN, OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(CS, OUTPUT);
}
void loop()
{
  for(j=0;j<20;j++)
  {
  a = j*20;  //最高400，对应5Vx2x400/1024=4V ，接近4V的一个锯齿波280HZ
  WriteTLC5615(a); //a这里不方便用表达式，故多一个变量
  //delay(20);  //取消注释，加上延时，成为呼吸灯，每秒2次左右
  }
}
