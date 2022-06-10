/*
 * IRrecvDemo
 * =====================功能说明=====================
 * 演示如何利用Arduino开发板接收红外遥控器控制信号，
 * 并将接收到的红外遥控器信号内容通过串口监视器显示出来。
 * 
 * 本程序基于Ken Shirriff开发的IRremote库。如需获得该库文件
 * 可前往以下网址获得：
 * http://arcfn.com （Ken Shirriff个人博客）                              
 * 
 * 
 * =====================电路连接======================
 *   红外接收器 1838B OUT 引脚 ---  Arduino Uno 11  引脚 
 *   红外接收器 1838B VCC 引脚 ---  Arduino Uno +5V 引脚 
 *   红外接收器 1838B GND 引脚 ---  Arduino Uno GND 引脚 
 *         
  */
 
#include <IRremote.h>
 
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);  //定义接收引脚为11脚.
decode_results results;    //声明一个IRremote库函数独有的变量类型(decode_resultc)



void setup()
{
  Serial.begin(9600);
  // 假如启动过程出现问题，提示用户启动失败
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  pinMode(8,OUTPUT);
  pinMode(8,LOW);
}
 
void loop() {
  if (irrecv.decode(&results)) { //检查是否接收到红外遥控信号
    Serial.print(results.value); //输出10进制接收到的数据指令信息
    Serial.print(" ");
    Serial.println(results.value,HEX); //输出16进制接收到的数据指令信息
      digitalWrite(8,HIGH);
    irrecv.resume();                    //接收下一指令
  }
  delay(200);
}
