
String input_string; // 声明变量 input_string ，用于存储串口输入的数据
// 获取串口数据函数
void GetSerialStuff(String& input_string) {
  String temp_string = ""; // 声明变量 temp_string，用于临时存储串口输入的数据
  while(Serial.available()) { // 当串口有数据时，循环执行
    temp_string += (char)Serial.read();  // 把读取的串口数据，逐个组合到inStr变量里
    delay(2);
  }
if(temp_string.length()!=0){
     input_string = temp_string; // 把引用指针的变量赋值给 input_string
    Serial.println("received data:" +  input_string );//打印字符串
              }
}
void setup() {
Serial.begin(9600);
pinMode(LED_BUILTIN, OUTPUT );

}

void loop() {
 GetSerialStuff(input_string); // 获取串口的数据
if(input_string != "") { // 如果 串口不为空，则
  if(!input_string.compareTo("on"))
   {//相等返回0
     Serial.println("ON");
    digitalWrite(LED_BUILTIN,HIGH);
    }
   if(!input_string.compareTo("off"))
  {
   Serial.println("OFF");
    digitalWrite(LED_BUILTIN,LOW);
   }
    input_string="";//清空数据
  }

 }
