#include "KEY.H"

const int buttonPin = 2; // 按键位置
const int ledPin = 13;   // led位置LED_BUILTIN

int ledState = HIGH;       // 当前led状态
int buttonState;           // 读取的当前按键状态
int lastButtonState = LOW; // 上次读取的按键状态

long lastDebounceTime = 0; // 上次按键触发时间
long debounceDelay = 50;   // 去抖时间，根据实际情况调整

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP); //初始化按键
  pinMode(ledPin, OUTPUT);   //初始化led的状态

  digitalWrite(ledPin, ledState); // 初始化led的状态
}

void loop()
{

  int reading = digitalRead(buttonPin); // 读取按键状态赋值到一个变量

  if (reading != lastButtonState) // 如果按键状态与上一次不同，说明是由于抖动还是按键按下造成的
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // 等过了去抖时间，再次去检测按键的状态
    if (reading != buttonState) // 如果按键仍然保持上次的状态，我们认为这个按键按下是真实有效的
    {
      buttonState = reading;

      if (buttonState == HIGH)
      {
        ledState = !ledState; // 按下按键改变当前的led状态
      }
    }
  }

  digitalWrite(ledPin, ledState); // 把led的最终结果映射到对应的引脚

  lastButtonState = reading; // 保存当前值，一边下一个循环检测的时候使用
}
