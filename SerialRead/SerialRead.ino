
/*
 * //程序示例一，接收一个字符并打印一个字符
String inputString;//定义一个字符串用来存放读取的数据
void setup() {
  Serial.begin(9600);//串口初始化
  Serial.setTimeout(2000);//设置设备等待数据流的最大时间间隔,默认情况下，该等待时间是1000毫秒。
}

void loop() {
  // 系统循环内不执行程序
}
//该方法自动检测缓冲区接受数据事件，一旦有数据接收，就会触发执行
void serialEvent(){
  while(Serial.available()>0){
    char inChar = (char)Serial.read();  //每次读取一个字节
    delayMicroseconds(2);  //延时等待下一个数据接收到
    inputString +=inChar;  //将接收的字节拼接到字符串
  }
  if(inputString){
  Serial.println(inputString);  //串口返回打印接收到的数据
  inputString=""; //清空接收的数据
  }
}

*/
//程序示例二，接收完一个字符串后再输出内容
void setup()
{
Serial.begin(9600);//设置波特率
}
void loop()
{
String comdata="";//使用字符串来接收，并初始化。
while (Serial.available() > 0)
{//判断有数据进来
comdata += char(Serial.read());//将接收到的字符串连起来，数据类型强制转换
delay(2);
}
if (comdata.length() > 0)
{//通过判断变量的数据长度，拉打印输出
Serial.print("串口接收到的数据:");
Serial.println(comdata);
comdata = "";//清空变量数据
}
}
