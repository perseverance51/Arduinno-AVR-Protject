/*
  Blink
通过串口打印出程序烧录时间。
*/
struct People {
  char *name;
  int age;
  float Height;
} ;
// People *stu = &People {"chen",12,46.8};



void setup() {
 Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  Serial.println(__DATE__);//打印烧录日期Jan  3 2022
  Serial.println(__TIME__);//打印烧录时间11:10:49
   People *stu ;
   stu->name = "chen";
  stu->age = 12;
  stu->Height = 46.2;
 Serial.println(stu->name);
  Serial.println(stu->age);
  Serial.println(stu->Height);

  Serial.println(stu->name);
}
