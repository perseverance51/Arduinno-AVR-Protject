 #define RED_A       (2)   //东西向指示灯
 #define YELLOW_A    (3)
 #define GREEN_A     (4)
 #define RED_B       (5)   //南北向指示灯
 #define YELLOW_B    (6)
 #define GREEN_B     (7)
     
    //定义闪烁次数及操作类型变量定义
  uint8_t Flash_Count = 0, display_Type = 1;
  uint8_t YELLOW_State = HIGH;
  //定义黄色LED初始状态
  void setup()
  {
      for(int i=2;i<8;i++)   //设置led所接引脚为输出模式
      pinMode(i,OUTPUT);
  }
   
  void loop() 
  {
      switch (display_Type)  
      {
          case 1://东西向绿灯与南北向红灯亮
              digitalWrite(RED_A,HIGH);
              digitalWrite(YELLOW_A,HIGH);
              digitalWrite(GREEN_A,LOW);
              digitalWrite(RED_B,LOW);
              digitalWrite(YELLOW_B,HIGH);
              digitalWrite(GREEN_B,HIGH);
              delay(3000);
              display_Type=2;
              break;
          case 2://东西向黄灯开始闪烁,绿灯关闭
              delay(200);
              if(YELLOW_State==HIGH)  YELLOW_State=LOW;
              else  YELLOW_State=HIGH;
              digitalWrite(YELLOW_A,YELLOW_State);
              digitalWrite(GREEN_A,HIGH);
              if(++Flash_Count != 10) return;  //闪烁5次
              Flash_Count=0;       //计数归零
              display_Type=3;
              break;
          case 3://东西向红灯与南北向绿灯亮
              digitalWrite(RED_A,LOW);
              digitalWrite(YELLOW_A,HIGH);
              digitalWrite(GREEN_A,HIGH);
              digitalWrite(RED_B,HIGH);
              digitalWrite(YELLOW_B,HIGH);
              digitalWrite(GREEN_B,LOW);
              delay(3000);
              display_Type=4;
              break;
          case 4://南北向黄灯开始闪烁
              delay(200);
              if(YELLOW_State==HIGH)  YELLOW_State=LOW;
              else  YELLOW_State=HIGH;
              digitalWrite(YELLOW_B,YELLOW_State);
              digitalWrite(GREEN_B,HIGH);
              if(++Flash_Count != 10) return; //闪烁5次
              Flash_Count=0;    //计数归零
              display_Type=1;   //回到第一种操作
              break;
      }
  }
