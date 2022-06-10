/*74HC595控制1位共阳数码管
 * 

  */

unsigned char table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};

const byte Pin_DS = 11;   //data
const byte Pin_ST_CP = 12;  //latch
const byte Pin_SH_CP = 13; //clock
const byte CT = 10; 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(Pin_ST_CP, OUTPUT);//ST_CP
  pinMode(Pin_DS, OUTPUT);//DS
  pinMode(Pin_SH_CP, OUTPUT);//SH_CP
  digitalWrite(Pin_DS, LOW);
   pinMode(CT, OUTPUT);
  digitalWrite(CT, HIGH); 
}

void loop() {
    int i=0;
do{
// for(;i<10;i++){
    digitalWrite(CT, HIGH); 
    digitalWrite(Pin_ST_CP, LOW); //将ST_CP口上面加低电平让芯片准备好接收数据
    shiftOut(Pin_DS, Pin_SH_CP, MSBFIRST, table[i]);//串行数据输出，高位在先 MSBFIRST  LSBFIRST    
    digitalWrite(Pin_ST_CP, HIGH); //将ST_CP这个针脚恢复到高电平
    delay(500);
    digitalWrite(CT, LOW); 
   i++;
  }
  while(i%=10);//当i等于10时，让i等于0
}
