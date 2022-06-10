#ifndef __KEY_H__
#define __KEY_H__   

     
#include <Arduino.h> 
#include <stdint.h>

typedef struct Key_t {

        uint8_t inited : 1;     //引脚是否已经初始化

        uint8_t press : 1;                //按下表示，1表示发生了按下事件，等待用户处理

        uint8_t release : 1;        //松开标志，1表示发送了松开事件，等待用户处理

        uint8_t state : 1;                //按键的稳定状态

        uint8_t states : 4;                //最近的4次采样

        uint8_t pin;                        //按键的编号或者所在引脚

} Key_t;



#ifdef __cplusplus

extern "C" {

#endif



//初始化一个按键

void Key_Init(Key_t* key, uint8_t pin);



//扫描一下按键，一般每隔5个毫秒扫描一次即可

//连续4次扫描就需要20个毫秒了，如果4次检测都是低电平才判断为低电平。

//由于一般情况下都是只处理按下事件，有按下事件返回1

uint8_t Key_Scan(Key_t* key);



//获取按键所在引脚的状态，高电平返回1，低电平返回0

uint8_t Key_GetPinState(Key_t* key);



//检查按键是否存在按下事件

static inline uint8_t Key_HasPressEvent(Key_t* key)

{

        return key->press;

}



//清除按键的按下事件标志

static inline void Key_ClearPressEvent(Key_t* key)

{

        key->press = 0;

}



//检查按键是否存在松开事件

static inline uint8_t Key_HasReleaseEvent(Key_t* key)

{

        return key->release;

}



//清除按键松开事件标志

static inline void Key_ClearReleaseEvent(Key_t* key)

{

        key->release = 0;

}



#ifdef __cplusplus

}

#endif



#endif //__KEY_H__
