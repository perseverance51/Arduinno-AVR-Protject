/*所需库： https://github.com/Makuna/Rtc
// DS1302模块接线说明:
// DS1302 CLK/SCLK --> 5
// DS1302 DAT/IO --> 4
// DS1302 RST/CE --> 2
// DS1302 VCC --> 3.3v - 5v
// DS1302 GND --> GND
本次实验演示：利用DS1302自带的31字节静态RAM进行其他数据存储

 */

#include <ThreeWire.h> //点击这里会自动打开管理库并搜索:http://librarymanager/All#Rtc_by_Makuna 
#include <RtcDS1302.h>

ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

#define countof(a) (sizeof(a) / sizeof(a[0]))

const char data[] = "perseverance51-9527-2022-6-27";//字符长度：30

void setup () 
{
    Serial.begin(9600);
    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);   
    Rtc.Begin();
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();
    //判断时钟是否正在运行
    if (!Rtc.IsDateTimeValid()) 
    {
        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }
    //判断是否写保护
    if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }
    //判断时钟是否正在运行
    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }
    //获取日期和时间
    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    
  /* 在第二次烧录时注释掉以下内容，以查看信息是否长期存储 */
    // 在RTC的内存中存储数据
 /*
    uint8_t count = sizeof(data);
    uint8_t written = Rtc.SetMemory((const uint8_t*)data, count); // 这包括字符串的空结束符
    if (written != count) 
    {
        Serial.print("something didn't match, count = ");
        Serial.print(count, DEC);
        Serial.print(", written = ");
        Serial.print(written, DEC);
        Serial.println();
    }
 */
/* 注释结束部分*/

}

void loop () 
{
    RtcDateTime now = Rtc.GetDateTime();

    printDateTime(now);//打印获取到的时间数据，
    Serial.println(" +");
//判断时钟是否正在运行
    if (!now.IsValid())
    {
//常见原因:
// 1)设备电池电量不足，甚至电池缺失，电源线被断开
        Serial.println("RTC lost confidence in the DateTime!");
    }
    delay(5000);
    // 读数据
    uint8_t buff[30];
    const uint8_t count = sizeof(buff);
    // get our data
    uint8_t gotten = Rtc.GetMemory(buff, count);//获取DS1302 静态ram数据
    //判断字符长度是否相等
    if (gotten != count) 
    {
        Serial.print("something didn't match, count = ");
        Serial.print(count, DEC);
        Serial.print(", gotten = ");
        Serial.print(gotten, DEC);
        Serial.println();
    }

    Serial.print("data read (");
    Serial.print(gotten);
    Serial.print(") = \"");
    // 输出字符串，但如果得到null则终止
    for (uint8_t ch = 0; ch < gotten && buff[ch]; ch++)
    {
        Serial.print((char)buff[ch]);
    }
    Serial.println("\"");
    
    delay(5000);
}



void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}
