
/*
 Stepper Motor Control 
 *4相5线步进电机 28YBJ-48
* 步进电机跟随电位器旋转
* (或者其他传感器)使用0号模拟口输入
* 使用arduino IDE自带的Stepper.h库文件
* 
* 如果编译报缺少库点击下方链接跳转字库下载页面
* 点击这里会自动打开管理库页面: http://librarymanager/All#Stepper
* 除此之外，还要修改库源文件
* 此程序需要修改库文件：C:\Users\Administrator\Documents\Arduino\libraries\Stepper\src\Stepper.cpp
* 本代码实现功能：
* 正转一圈，停3秒，
* 反转一圈，循环

 */

#include <Stepper.h>

const int stepsPerRevolution = 4;  // change this to fit the number of steps per revolution

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  //  设置转速set the speed at 120 rpm
  myStepper.setSpeed(120);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
 while(1){
  myStepper.step(4);
  delay(3000);

  myStepper.step(-4);
  delay(3000);
}
}
