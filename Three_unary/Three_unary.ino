
#define button PA4
#define PC13 LED_BUILTIN
boolean State = false ;
enum DAY
{
      MON=1, TUE, WED, THU, FRI, SAT, SUN
};

void setup() {
  Serial.begin(9600);
pinMode(button,INPUT_PULLUP);  
pinMode(PC13,OUTPUT);
digitalWrite(PC13,HIGH);
digitalWrite(button,HIGH);
}

void loop() {
  while(1){
State = digitalRead(button);
Serial.println(State);
State == HIGH ? digitalWrite(PC13,HIGH) : digitalWrite(PC13,LOW);
delay(1000);
enum DAY day;
    day = SAT;
    char buffer[8];
sprintf(buffer, "Today = %d\n", day);
Serial.print(buffer);
//三目运算等价于
//if(Status == true){
//    digitalWrite(PC13,HIGH);
//}else{
//  digitalWrite(PC13,LOW);
//  }
}
}
