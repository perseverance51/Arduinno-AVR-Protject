int led = 13;
void setup() {                  
  pinMode(led, OUTPUT);
  DDRC=0xff;//端口C设置为输出
  PORTC=0x00;//端口C初始值设置为0  
  Serial.begin(9600);  
}

void loop() {
digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
PORTC=0xff;//点亮二极管
  Serial.println(PORTC,HEX);
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // 熄灭led
  PORTC=0x00;//熄灭二极管
  Serial.println(PORTC,HEX);
  delay(1000);               // wait for a second
}
