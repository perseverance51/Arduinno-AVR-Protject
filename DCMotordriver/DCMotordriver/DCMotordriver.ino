/*H桥PWM直流电动机驱动代码
 * JC_Button库下载地址：https://www.arduino.cc/reference/en/libraries/jc_button/
 */
#include <JC_Button.h>
int PWM_Value;
byte Enable_Pin = 13;
byte PWM1_Pin = 11;
byte PWM2_Pin = 10;
byte PWM_Pin = 11;
Button UP(9, 25, true, true);
Button Down(8, 25, true, true);
Button Left(7, 25, true, true);
Button Right(6, 25, true, true);
void setup() {
pinMode(Enable_Pin, OUTPUT);
pinMode(PWM1_Pin, OUTPUT);
pinMode(PWM2_Pin, OUTPUT);
UP.begin();
Down.begin();
Left.begin();
Right.begin();
digitalWrite(Enable_Pin, LOW);
PWM_Value = 0;
analogWrite(PWM1_Pin, PWM_Value);
analogWrite(PWM2_Pin, PWM_Value);
}
void loop()
{
digitalWrite(Enable_Pin, HIGH);
UP.read();
Down.read();
Left.read();
Right.read();
if (UP.wasReleased() && PWM_Value < 250)
{
PWM_Value +=5;
}
if (Down.wasReleased() && PWM_Value > 5)
{
PWM_Value -=5;
}
if (Left.wasReleased())
{
PWM_Pin = PWM1_Pin;
analogWrite(PWM2_Pin, 0);
}
if (Right.wasReleased())
{
PWM_Pin = PWM2_Pin;
analogWrite(PWM1_Pin, 0);
}
analogWrite(PWM_Pin, PWM_Value);
}
