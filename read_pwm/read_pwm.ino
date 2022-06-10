//读取 PPM 信号 from 2 channels of an RC reciever
//读取信号时，保证发送信号为单任务执行，

//接收机两个通道分别接arduino的数字口2、3脚
//Most Arduino boards have two external interrupts: numbers 0 (on digital pin 2) and 1 (on digital pin 3). 
//The Arduino Mega has an additional four: numbers 2 (pin 21), 3 (pin 20), 4 (pin 19), and 5 (pin 18).
int ppm1 = 2;  
int ppm2 = 3;

volatile unsigned long rc1_PulseStartTicks = 0;
volatile unsigned long rc1_low_PulseStartTicks = 0;
volatile unsigned long  rc1_val=0;  
volatile unsigned long  rc1_low=0;

#define MAX_ARRRAY 64
unsigned long value[ MAX_ARRRAY] = {};
volatile int count = 0;

void setup() 
{

        Serial.begin(115200);  

        //PPM inputs from RC receiver
        pinMode(ppm1, INPUT); 
        digitalWrite(ppm1,LOW);
        rc1_low_PulseStartTicks = micros(); 
        
        // 电平变化即触发中断
        attachInterrupt(0, rc1, CHANGE);    
}

void rc1()
{
        if(count >= MAX_ARRRAY)
            return;
            
        // did the pin change to high or low?
        if (digitalRead( ppm1 ) == HIGH)
        {
                if(rc1_low_PulseStartTicks > 0)
                {
                   rc1_PulseStartTicks = micros();    // store the current micros() value
                  
                  rc1_low = micros() - rc1_low_PulseStartTicks; //获取低电平脉宽时间
                  value[count++] = rc1_low;
                  rc1_low_PulseStartTicks = 0;                 
                }

        }
        else
        {               
                if(rc1_PulseStartTicks > 0)
                {
                        rc1_val = micros() - rc1_PulseStartTicks; //高电平脉宽时间
                        value[count++] = rc1_val;
                                              
                        rc1_PulseStartTicks = 0;
                        rc1_low_PulseStartTicks = micros();
                }                    
        } 
}


void loop() 
{  
  if(count>=MAX_ARRRAY)
  {     
     Serial.println("//==============================================================");
    for(int index=0;index<MAX_ARRRAY;index++)
    {
        //Serial.println(value[index]);
        if( (index%2) == 0)
        {
                      Serial.println("digitalWrite(fly_pin, LOW);");
                      Serial.print("delayMicroseconds(");
                      Serial.print(value[index]);         
                      Serial.println(");");
        }
        else
        {
                      Serial.println("digitalWrite(fly_pin, HIGH);");
                      Serial.print("delayMicroseconds(");
                      Serial.print(value[index]);         
                      Serial.println(");");
          
        }
    }

    count = 0;
    
  }
}
