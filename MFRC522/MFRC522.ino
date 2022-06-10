/*按下按钮开始储存卡的数据，绿灯常亮。
 * 再次按下退出，开始门锁功能，黄灯常亮，
 * 如果有已经储存的卡放置在读卡器前绿灯亮一下然后熄灭，
 * 反之红灯亮一下。
 * 
 */
#include <MFRC522.h>//如果没有此库点击后面的链接会自动打开管理库搜索对应的库名称: http://librarymanager/All#MFRC522
#define SS_PIN 10
#define RST_PIN 5
#define Button_Pin 4
#define yellow_Led 5
#define green_Led 6
#define red_Led 7
//按钮用的定义//
unsigned char val = 0;//变量val 存储按钮的状态
unsigned char old_val = 0;//暂存val变量的上一个时间状态
unsigned char state1=0;
unsigned char Button1=0;
unsigned char kacck=0; //让"开始储存卡"只用一次
static int CardNumber = 0; //卡的储存次数
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
byte nuidPICC[8][4];
void setup() {
Serial.begin(9600);
SPI.begin(); // Init SPI bus
rfid.PCD_Init(); // Init MFRC522
rfid.PCD_SetAntennaGain(rfid.RxGain_max);
pinMode(yellow_Led,OUTPUT);
pinMode(green_Led,OUTPUT);
pinMode(red_Led,OUTPUT);
pinMode(Button_Pin,INPUT);
blink_LED();
digitalWrite(yellow_Led,HIGH);
}
void loop() {
Button_Press();
while(Button1 == 1) {
Button_Press();
if((Button1 == 1)&&(kacck==0)) {
delay (10);
kacck = 1;
}
if ( ! rfid.PICC_IsNewCardPresent())
return;
if ( ! rfid.PICC_ReadCardSerial())
return;
MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
// 检测是否为支持的卡片
if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
Serial.println(F("你的卡可能不受支持"));
}
if (Store_CheckCard() ) {
Serial.println(F("新的卡已经检测到了。"));
// 将NUID存储到nuidPICC数组中
for (byte i = 0; i < 4; i++) {
nuidPICC[CardNumber][i] = rfid.uid.uidByte[i];
}
Serial.println(F("NUID:"));
Serial.print(F("十六进制为: "));
printHex(rfid.uid.uidByte, rfid.uid.size);
Serial.println();
for (byte a = 0; a < 8; a++){
Serial.println();
for (byte i = 0; i < 4; i++) {
Serial.print(nuidPICC[a][i] < 0x10 ? " 0" : " ");
Serial.print(nuidPICC[a][i],HEX);
}
}
CardNumber++;
}
else Serial.println(F("已经读取过这个卡了。"));
}
//储存卡
// 如果传感器/读卡器上没有新卡，则返回主程序。这将在空闲时保存整个进程。
if ( ! rfid.PICC_IsNewCardPresent())
return;
// 验证是否已读取NUID
if ( ! rfid.PICC_ReadCardSerial())
return;
if (Checkcard2() ) {
for (byte i = 0; i < 4; i++) {
Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
Serial.print(rfid.uid.uidByte[i],HEX);
}
Serial.println(F("通过"));
digitalWrite(green_Led, HIGH); // turn the LED on (HIGH is the voltage level)
delay(500); // wait for a second
digitalWrite(green_Led, LOW); // turn the LED off by making the voltage LOW
delay(500);
}
else {
Serial.println();
Serial.println(F("未通过"));
for (byte i = 0; i < 4; i++) {
Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
Serial.print(rfid.uid.uidByte[i],HEX);
}
digitalWrite(red_Led, HIGH); // turn the LED on (HIGH is the voltage level)
delay(500); // wait for a second
digitalWrite(red_Led, LOW); // turn the LED off by making the voltage LOW
delay(500);
}
// 停止 PICC
rfid.PICC_HaltA();
// 停止加密 on PCD
rfid.PCD_StopCrypto1();
}
///闪烁灯
void blink_LED(){
unsigned short delay_Time=40;
for(int j=0;j<3;j++){
for(int i=5;i<8;i++){
digitalWrite(i, HIGH);
delay(delay_Time);
digitalWrite(i, LOW);
delay(delay_Time);
}
for(int i=7;i>4;i--){
digitalWrite(i, HIGH);
delay(delay_Time);
digitalWrite(i, LOW);
delay(delay_Time);
}
}
}
//在储存卡的时候检测卡片是否储存在芯片里/
int Store_CheckCard(){
unsigned short i=0;
unsigned short Store_CheckCard_unm1=0;
while(i<8)
{
for(unsigned short i1=0;i1<8;i1++)
{
if(rfid.uid.uidByte[0] == nuidPICC[i][0] &
rfid.uid.uidByte[1] == nuidPICC[i][1] &
rfid.uid.uidByte[2] == nuidPICC[i][2] &
rfid.uid.uidByte[3] == nuidPICC[i][3])
{
Store_CheckCard_unm1++;
}
i++;
}
}
if (Store_CheckCard_unm1 == 0){
return 1;
Store_CheckCard_unm1 =0;
}
else return 0;
}
//在读取卡的时候检测卡片是否储存在芯片里
int Checkcard2(){
unsigned short i=0;
unsigned short Checkcard2_unm1=0;
while(i<8)
{
for(unsigned short i1=0;i1<8;i1++)
{
if(rfid.uid.uidByte[0] == nuidPICC[i][0] &
rfid.uid.uidByte[1] == nuidPICC[i][1] &
rfid.uid.uidByte[2] == nuidPICC[i][2] &
rfid.uid.uidByte[3] == nuidPICC[i][3])
{
Checkcard2_unm1++;
}
i++;
}
}
if (Checkcard2_unm1 != 0){
return 1;
Checkcard2_unm1 =0;
}
else return 0;
}
//按下按钮开始写入卡的UNID
void Button_Press(){
//按下按钮
val = digitalRead(Button_Pin);//读取输入数值并且存储
if((val==LOW)&&(old_val==HIGH))//检查按钮的变化情况
{
state1++;
}
if(state1==1){
Button1 = 1;
digitalWrite(green_Led,HIGH);
digitalWrite(yellow_Led,LOW);
}
if((state1==2)||(state1==0)){
state1=0;
Button1 = 0;
digitalWrite(green_Led,LOW);
digitalWrite(yellow_Led,HIGH);
}
old_val=val;//val现在是旧的了，让我们暂存一下
}
/**
* Helper routine to dump a byte array as hex values to Serial.
*/
void printHex(byte *buffer, byte bufferSize) {
for (byte i = 0; i < bufferSize; i++) {
Serial.print(buffer[i] < 0x10 ? " 0" : " ");
Serial.print(buffer[i], HEX);
}
}
