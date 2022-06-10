/**非自锁按键控制模式：按一下得电，再按一下失电，通过中断，实现状态的改变**/

#define led 6
#define interruptPin 2
volatile byte State = LOW;
void setup() {
  pinMode(led, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), use, FALLING);//开中断，下降沿触发
}
 
void loop() {
  digitalWrite(led, State);
}

/**中断服务函数**/
void use() {
  State = !State;
}
