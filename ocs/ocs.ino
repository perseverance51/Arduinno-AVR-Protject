
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
MCUFRIEND_kbv tft;

const unsigned char XP=7,XM=A1,YP=A2,YM=6; //ID=0x5408
const int TS_LEFT=772,TS_RT=151,TS_TOP=953,TS_BOT=156;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 200
#define MAXPRESSURE 1000

// 颜色值:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
//RGB颜色
#define RGB(r,g,b) (((r&0xF8)<<8)|((g&0xFC)<<3)|(b>>3))
#define GREY      RGB(127, 127, 127)
#define DARKGREY  RGB(64, 64, 64)
#define TURQUOISE RGB(0, 128, 128)
#define PINK      RGB(255, 128, 192)
#define OLIVE     RGB(128, 128, 0)
#define PURPLE    RGB(128, 0, 128)
#define AZURE     RGB(0, 128, 255)
#define ORANGE    RGB(255,128,64)

#define ch1     A5
#define max_buf 321
#define max     320
#define _ms     150
#define vatel   5

int xpos, ypos;
uint8_t PENRADIUS = 1;
uint8_t Orientation = 1;    //屏幕旋转
int i,value;
int time[]={0,7,20,46,102,224,460};
int _adc,_us;
int _id; //点击的按钮id
int buf[max_buf];
int buf_old[max];
bool hold=false;
long t;
int delay_us=0;
int Freq,Cycl,Duty,Pw,V_max,V_min,V_mid,Vpp;
int i1,i2,i3;
int Tv=209;  //触发电压
String sj[]={" x1:1 "," x10:1 ","x100:1"};
int mode=0;
float _Vmax,_Vmin,_Vmid,_Vrms;
int old_Freq,old_Duty;
bool parameter=false;
int adc_i=8;
/*
//主菜单
void man_menu(void){
  tft.fillScreen(BLACK);
  tft.setTextSize(1);
  tft.setTextColor(WHITE, BLACK);
  tft.setCursor(60, 20);
  tft.print("plase select menu");
  
  btn_osc.initButton(&tft,100,60,120,40,WHITE,CYAN,BLACK, "OSC",2);
  btn_pwm.initButton(&tft,100,110,120,40,WHITE,CYAN,BLACK, "PWM",2);
  btn_osc.drawButton(false);
  btn_pwm.drawButton(false);
  while (1) {
    update_button_list(buttons);
    if (btn_osc.justPressed()) {
      btn_osc.drawButton(true);
      osc();
    }

  }
}*/

void setup(void){
  tft.reset();
  tft.begin(0x5408);
  tft.setRotation(Orientation);
  osc();
}

void draw_btn(int x,int y,int w,int h,String lable){
  tft.setTextColor(WHITE, BLUE);
  tft.drawRoundRect(x, y, w, h, 3, RED);
  tft.setCursor(x+3, y+9);
  tft.print(lable);
}

//示波器
void osc(void){
  tft.fillScreen(BLACK);
  tft.fillRect(0, 0, tft.width(), 30, BLUE);
  tft.fillRect(0, 210, tft.width(), 30, BLUE);
  tft.setTextSize(0);
  
  draw_btn(2,212,48,25," Auto");
  draw_btn(55,212,48,25," x1:1 ");
  draw_btn(108,212,48,25,"  D+");
  draw_btn(162,212,48,25,"  D-");
  draw_btn(217,212,48,25,"measure");
  draw_btn(271,212,48,25," Hold");

  while(1){
    bool down =Touch_getXY();
    if(down&&ypos<230&&ypos>200){
      if(xpos>2&&xpos<48){          //Auto
        _id=0;
        
        delay(100);
      }else if(xpos>55&&xpos<103){   //衰减
        _id=1;
        mode++;
        if(mode>2){mode=0;}
        draw_btn(55,212,48,25,sj[mode]);
      }else if(xpos>108&&xpos<157){  //D+
        _id=2;
        _us+=1;
        if(_us>=6){_us=6;}
      }else if(xpos>162&&xpos<210){  //D-
        _id=3;
        _us-=1;
        if(_us<=0){_us=0;}
      }else if(xpos>217&&xpos<266){  //测量
        _id=4;
        tft.fillRect(0, 0, tft.width(), 30, BLUE);
        if(parameter){
          parameter=false;
        }else{
          parameter=true;
        }
        //delay(100);
      }else if(xpos>271&&xpos<320){  //hold
        _id=5;
        tft.setTextColor(WHITE, BLACK);
        tft.setCursor(5, 40);
        if(hold){
          hold=false;
          tft.print("    ");
        }else{
          hold=true;
          tft.print("HOLD");
        }
        delay(100);
      }
    }else if(down&&ypos<200&&ypos>20){  //触发电压
      tft.drawLine(0, Tv, 5, Tv, BLACK);
      Tv=ypos+10;
    }
   
    if(hold==false){
        sampling();
        measure();
        display_cls();
        display();
    }
  }
}

//获取触屏位置
bool Touch_getXY(void){
  tp = ts.getPoint();   //tp.x, tp.y的值从ADC读取
  pinMode(XM, OUTPUT);  //恢复共享引脚
  pinMode(YP, OUTPUT);
  bool pressed = (tp.z>MINPRESSURE && tp.z<MAXPRESSURE);
  //模屏竖屏坐标计算
  if (pressed) {
    switch (Orientation) {
      case 0:
        xpos = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
        ypos = map(tp.y, TS_TOP, TS_BOT, 0, tft.height());
        break;
      case 1:
        xpos = map(tp.y, TS_TOP, TS_BOT, 0, tft.width());
        ypos = map(tp.x, TS_RT, TS_LEFT, 0, tft.height());
        break;
      case 2:
        xpos = map(tp.x, TS_RT, TS_LEFT, 0, tft.width());
        ypos = map(tp.y, TS_BOT, TS_TOP, 0, tft.height());
        break;
      case 3:
        xpos = map(tp.y, TS_BOT, TS_TOP, 0, tft.width());
        ypos = map(tp.y, TS_LEFT, TS_RT, 0, tft.height());
        break;
    }
    /*
    tft.setTextColor(WHITE,BLUE);
    tft.setCursor(250, 10);
    tft.print("x=" + String(xpos) + " y=" + String(ypos) + "   ");*/
  }
  return pressed;
}

void loop(){
  
  
}


//ADC采样通道
void ADC_pin(uint16_t pin){
  switch(pin){
    case A0: //A0
      ADMUX =_BV(REFS0);break;
    case A1: //A1
      ADMUX =_BV(REFS0)|_BV(MUX0);break;
    case A2: //A2
      ADMUX =_BV(REFS0)|_BV(MUX1);break;
    case A3: //A3
      ADMUX =_BV(REFS0)|_BV(MUX0)|_BV(MUX1);break;
    case A4: //A4
      ADMUX =_BV(REFS0)|_BV(MUX2);break;
    case A5: //A5
      ADMUX =_BV(REFS0)|_BV(MUX0)|_BV(MUX2);break;
    case A6: //A6
      ADMUX =_BV(REFS0)|_BV(MUX1)|_BV(MUX2);break;
    case A7: //A7
      ADMUX=_BV(REFS0)|_BV(MUX0)|_BV(MUX1)|_BV(MUX2);
      break;
    default:
      break;
  }
  //ADMUX |= (1<<REFS1)|(1<<REFS0);//内部1.1V参考电压
}

//ADC分频，采样速率
void ADC_adcsra(int key) {
  switch (key){
    case 4://ADC Sample=16MHz/4/13=307.6KHz,实测142.8KHz
      ADCSRA = _BV(ADPS1); //7us采样一次
      break;
    case 8://ADC Sample=16MHz/8/13=153.8KHz,实测100KHz
      ADCSRA = _BV(ADPS0)|_BV(ADPS1);  //10us采样一次
      break;
    case 16://ADC Sample=16MHz/16/13=76.8KHz,实测58.8KHz
      ADCSRA = _BV(ADPS2);  //17us采样一次
      break;
    case 32://ADC Sample=16MHz/32/13= 38.4KHz,实测33.3KHz
      ADCSRA = _BV(ADPS2)|_BV(ADPS0);  //30us采样一次
      break;
    case 64://ADC Sample=16MHz/64/13= 19.2KHz,实测17.8KHz
      ADCSRA = _BV(ADPS2)|_BV(ADPS1);  //56us采样一次
      break;
    case 128://ADC Sample=16MHz/128/13=9600Hz,实测8928Hz
      ADCSRA =_BV(ADPS2)|_BV(ADPS1)|_BV(ADPS0);  //112us
      break;
    default:
      break;
  }
  ADCSRA |= _BV(ADEN);
}

//获取ADC采样值
int _analogRead(void){
  bitClear(ADCSRA, ADIF);
  ADCSRA |= _BV(ADSC);
  loop_until_bit_is_set(ADCSRA, ADIF);
  return ADC;
}

//采样
void sampling(){
  ADC_pin(ch1);         //使用ch1采样(触摸屏会更改)
  ADC_adcsra(8);        //使用4分频采样
  //切换通道后前10次采样是错的，不要
  for(i=0;i<15;i++){_analogRead();}
  t = micros();         //采样开始时间
  for(i=0;i<max_buf;i++){
    buf[i]=_analogRead();
    if(time[_us]>0){delayMicroseconds(time[_us]);}
  }
  t = (micros()-t)/max_buf; //采样1次时间
  ADC_adcsra(128);      //恢复128分频给触摸屏
}

//计算参数
void measure(void){
  V_max = buf[0];V_min = buf[0];
  for(i=0;i<max;i++){
    V_max = ((V_max<buf[i])?buf[i]:V_max);//最大值
    V_min = ((V_min>buf[i])?buf[i]:V_min);//最小值
  }
  V_mid = (V_max+V_min)/2; //平均值
  Vpp   = (V_max-V_min);   //峰峰值
  int H=map(Tv,30,210,1023,0);//触发值
  
  if(Vpp==V_max&&V_mid*2==Vpp){ //方波
    //周期开始点
    for (i=0; i<max;i++){
      if(buf[i]<V_mid&&buf[i+1]>V_mid)
        {i1=i;break;}
      }
    for(i=i1+1;i<max;i++){
      //周期内高电平结束点
      if(buf[i]>V_mid&&buf[i+1]<V_mid){i2=i;}
      //周期结束点
      if(buf[i]<V_mid&&buf[i+1]>V_mid)
        {i3=i;break;}
    }
    Cycl=(i3-i1);  //周期时间=周期结速点-周期开始点
    Pw=(i2-i1);     //低电平时间
   
    Duty =(Pw*100)/Cycl; //占空比=低电平时间/周期时间
    Freq =1000000/Cycl/t; //频率
    if(Vpp<H){
      Cycl=0;Pw=0;Duty=0;Freq=0;
    }else if(Freq<0){Freq=old_Freq;Duty=old_Duty;}
  }
  
}

//显示
void display(void){
  for(i=0;i<max+1;i++){
    buf[i]=map(buf[i],0,1023,209,31);     //计算坐标
  }
  for(i=0;i<max;i++){
    tft.drawLine(i, buf[i], i, buf[i+1], WHITE);
    buf_old[i]=buf[i];
  }
  display_v();
  old_Freq=Freq;
  old_Duty=Duty;
}

void display_v(void){
  int a=0;
  tft.setTextColor(WHITE,BLUE);
  if(parameter){
   
    //衰减倍数
    if(mode==0){
      a=1;
    }else if(mode==1){
      a=10;
    }else if(mode==2){
      a=100;
    }
    _Vmax=V_max*vatel/1023;
    _Vmin=V_min*vatel/1023;
    _Vmid=V_mid*vatel/1023;
    _Vrms=Vpp*vatel/1023;
  
    tft.setCursor(2, 5);
    tft.print("Freq:");
    tft.print(Freq);
    tft.print("Hz     ");
    tft.setCursor(2, 20);
    tft.print("Cycl:");
    tft.print(Cycl*t);
    tft.print("us    ");
    tft.setCursor(85, 5);
    tft.print("Pw:");
    tft.print(Pw*t);
    tft.print("us  ");
    tft.setCursor(85, 20);
    tft.print("Duty:");
    tft.print(Duty);
    tft.print("%   ");
  
    tft.setCursor(155, 5);
    tft.print("Vmax:");
    tft.print(_Vmax*a);
    tft.print("V   ");
    tft.setCursor(155, 20);
    tft.print("Vmin:");
    tft.print(_Vmin*a);
    tft.print("V   ");
    tft.setCursor(235, 5);
    tft.print("Vmid:");
    tft.print(_Vmid*a);
    tft.print("V  ");
    tft.setCursor(235, 20);
    tft.print("Vrms:");
    tft.print(_Vrms*a);
    tft.print("V  ");
  }else{
    tft.setTextColor(WHITE,BLUE);
    tft.setCursor(5, 14);
    tft.print("Arduino Digital OSC V2.0");
    tft.setCursor(250, 20);
    tft.print("Delay:"+String(time[_us]) +"us  ");
  }
}


//清除
void display_cls(void){
  for(i=0;i<max;i++){
    tft.drawLine(i, buf_old[i], i, buf_old[i+1], BLACK);
  }
  
  //绘网格
  for(i=32;i<=320;i+=32){  //竖线
    tft.drawLine(i, 30, i, 210, DARKGREY);
  }
  for(i=60;i<=180;i+=30){ //横线
    tft.drawLine(0, i, 320, i, DARKGREY);
  }
  tft.drawLine(0, 120, 320, 120, RED);
  tft.drawLine(160, 30, 160, 210, RED);
  //触发电压
  tft.drawLine(0, Tv, 3, Tv, YELLOW);
  
}
