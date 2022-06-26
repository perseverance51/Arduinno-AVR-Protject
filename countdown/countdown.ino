/* 
 * 按键控制2位数码管倒计时
 * Created:   周六 6月 25 2022
 * Processor: Arduino Uno
 * Compiler:  Arduino AVR
 */
    int num=60;            //定义倒计时数字
    int count=0;           //定义计数值
    int start_key = 10;   //开始按键
    int pause_key = 11;   //暂停按键
    int reset_key = 12;   //复位按键
         //0-9对应的16进制数据
    const uint8_t CA_SEGCODE[] = 
      { 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
  //用数组指定2位8段数码管所连接的段引脚(或称段码引脚)
  const uint8_t ledPins_SEG[] = { 0,1,2, 3, 4, 5, 6, 7 };
  //用数组指定2位8段数码管的位引脚(或称位码引脚)
  const uint8_t ledPins_DIG[] = {8,9};
      //待显示到数码管的2个数字
  const uint8_t DATEx[] = {(uint8_t)num/10,(uint8_t)num%10};

   
  int start_flag=0;    //是否开启倒计时标志位
  int reset_flag=0;    //复位倒计时数标志位
  //-----------------------------------------------------------------
  // 初始配置
  //-----------------------------------------------------------------
  uint8_t i;
  void setup() 
  {

      for(i=0;i<10;i++)                 //设置各引脚模式
      pinMode(ledPins_SEG[i],OUTPUT);
      for(i=0;i<2;i++)
      pinMode(ledPins_DIG[i],OUTPUT);
      for(i=10;i<13;i++)
      {
          pinMode(i,INPUT_PULLUP);
      }
  }
  //-----------------------------------------------------------------
  // 主循环
  //-----------------------------------------------------------------
  void loop() 
  {
  const uint8_t DATEx[] = {num/10,num%10};    //待显示的两位数字
   
      for (i = 0; i < 3; i++)   //循环扫描数码管
      {       
          DIG_OUTPUT(i);   //操作位码
          SEG_OUTPUT(CA_SEGCODE[DATEx[i]]);  //操作段码
          delay(1);
          count++;   //每延时1ms，count+1
          key_scan();  //按键扫描子函数
          
          if(start_flag==1 && count>300)      //当开启了倒计时，每300ms倒计时-1（本来是1000ms，这里为了演示效果调到了300）
          {
                  num--;   //倒计时数-1
                  count=0; //计数归零
          }
          
          if(reset_flag==1)   //当复位标志位为1
              {
                  num=60;       //倒计时数设置为60
                  reset_flag=0; //复位标志位归0
                  start_flag=0; //开始倒计时标志位归0
              }
              
          if(num<0)    //当倒计时完毕，倒计时数重新设置为60
          num=60;
      }
      
      
      
   
  }
  //-----------------------------------------------------------------
  // 段码输出函数
  //-----------------------------------------------------------------
  void SEG_OUTPUT(uint8_t x) {
      for (uint8_t j = 0; j < 8; j++) {   //发送段码
              if((x>>j & 0x01) != 0x00)
              digitalWrite(ledPins_SEG[j],HIGH);
              else 
              digitalWrite(ledPins_SEG[j],LOW);
          }
      }
  //-----------------------------------------------------------------
  // 位码输出函数
  //-----------------------------------------------------------------
  void DIG_OUTPUT(uint8_t dx) {
      for (uint8_t j = 0; j < 2; j++) {   //发送位码(2位)
          if(dx != j)
          digitalWrite(ledPins_DIG[j],LOW);
          else
          digitalWrite(ledPins_DIG[j],HIGH);
      }
  }
   
  void key_scan()    //按键扫描子函数
  {
      if(digitalRead(start_key)==LOW)   //当启动倒计时按键按下
      {
          delay(10);   //消抖延时
          if(digitalRead(start_key)==LOW)  
             start_flag=1;     //开始倒计时标志位置位1。以下操作暂停按键、复位按键原理类似
     }
     
     if(digitalRead(pause_key)==LOW)
     {
         delay(10);
         if(digitalRead(pause_key)==LOW)
             start_flag=0;
     }
     
     if(digitalRead(reset_key)==LOW)
     {
         delay(10);
         if(digitalRead(reset_key)==LOW)
             reset_flag=1;
     }
 }
