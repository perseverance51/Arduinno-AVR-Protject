/**非自锁按键控制模式：按一下得电，再按一下失电，只要按钮被按下，状态就改变**/
#define KEY (5)   //操作对象
#define LED (6)  //控制对象 （板载 LED_BUILTIN 13 ）
char keyFlag = 0;//按键状态
void setup() {
  Serial.begin(9600);
  pinMode(KEY,INPUT_PULLUP);//上拉输入模式
  pinMode(LED,OUTPUT);
}
void loop() {
  if(digitalRead(KEY) == 1){//注意这里是1不是0
    delay(10);//消抖处理
    if(digitalRead(KEY) == 1){//注意这里是1不是0
      keyFlag = 1 - keyFlag ;
      Serial.println(keyFlag);
      while(digitalRead(KEY));//等待按键被释放
    }
  }
  if(keyFlag == 1){
    digitalWrite(LED,HIGH);
  }else{
    digitalWrite(LED,LOW);
  }
}
