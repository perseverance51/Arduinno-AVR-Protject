int R[] = {2,7,A5,5,13,A4,12,A2}; //行
int C[] = {6,11,10,3,A3,4,8,9};   //列
 
unsigned char biglove[8][8] =       //大“心型”的数据
{
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,1,1,0,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,1,1,0,0,0,
};
 
unsigned char smalllove[8][8] =      //小“心型”的数据
{
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,1,0,0,1,0,0,
  0,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,0,0,0,0,0,
};
 
void setup()
{
   //循环定义行列PIN 为输出模式
  for(int i = 0;i<8;i++)
  {
    pinMode(R[i],OUTPUT);
    pinMode(C[i],OUTPUT);
  }
}
 
void loop()
{
  for(int i = 0 ; i < 100 ; i++)        //循环显示100次
  {
    Display(biglove);                   //显示大”心形“
  }
  delay(500);
  for(int i = 0 ; i < 50 ; i++)         //循环显示50次
  {   
    Display(smalllove);                 //显示小“心形”
  }
   delay(500);
}
 
void Display(unsigned char dat[8][8])   //显示函数
{
  for(int c = 0; c<8;c++)
  {
    digitalWrite(C,LOW);//选通第c列
 
    //循环
    for(int r = 0;r<8;r++)
    {
      digitalWrite(R[r],dat[r]);
    }
    delay(5);
    Clear();  //清空显示去除余晖
  }
}
 
void Clear()                          //清空显示
{
  for(int i = 0;i<8;i++)
  {
    digitalWrite(R[i],LOW);
    digitalWrite(C[i],HIGH);
  }
}
