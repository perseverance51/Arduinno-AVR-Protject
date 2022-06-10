/**非自锁按键控制模式：按一下得电，再按一下失电，只要按钮被按下，状态就改变**/
#define ledPin 6
#define buttonPin 5


// variables will change:
uint8_t buttonState = 1;              // variable for reading the pushbutton status
bool buttonStateFlag =true;
bool ledStateFlag=false;
void setup() 
{
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);//
}


void loop()
{
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH&&buttonStateFlag==true)
{
    ledStateFlag=!ledStateFlag;
    digitalWrite(ledPin, ledStateFlag);
    buttonStateFlag=false;
  }
  else if(buttonState == LOW)
{
    buttonStateFlag=true;
    while(!digitalRead(buttonPin));//按键不释放，就一直停在这里
  }
}
