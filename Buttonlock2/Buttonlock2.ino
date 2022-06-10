/**非自锁按键控制模式：按一下得电，再按一下失电,只有按键被释放状态才改变**/

const byte buttonPin = 5;// 定义按键输入针脚号为2号针脚
const byte ledPin = 6;
// 定义按键状态变量初始值为0
unsigned char ButtonState=0;
unsigned  char  ButtonLastState=1;
unsigned char ButtonCounter =0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  pinMode(buttonPin,INPUT_PULLUP);//输入上拉

}

void loop() {
  ButtonState = digitalRead(buttonPin);
  if(ButtonState != ButtonLastState)
  {
   if(ButtonState)
    {
        Serial.println("on");
        ButtonCounter++;
    }
    else
    {
      Serial.println("off");  
    }
  }
  ButtonLastState = ButtonState;
  if(ButtonCounter%2)//取模后做判断
  {
    digitalWrite(ledPin,HIGH);  
  }
  else
  {
    digitalWrite(ledPin,LOW);  
  }
}
