#include "key.h"



uint8_t Key_GetPinState(Key_t* key)

{

    if (1 == key->pin) {

        return 1;

    }

    else {

        return 0;

    }

}



//计算一个数字里面为1的位的个数

static inline uint8_t CountOne(uint8_t num)

{

    uint8_t high = (num & 0xf0) >> 4;

    uint8_t low = num & 0x0f;

    const uint8_t table[] = {

        0, 1, 1, 2,        //0000 0001 0010 0011

        1, 2, 2, 3,        //0100 0101 0110 0111

        1, 2, 2, 3, //1000 1001 1010 1011

        2, 3, 3, 4,        //1100 1101 1110 1111

    };



    return table[high] + table[low];

}



void Key_Init(Key_t* key, uint8_t pin)

{

    key->pin = pin;

    key->press = 0;

    key->release = 0;

    key->state = Key_GetPinState(key);

    key->states = key->state ? 0x0f : 0x00;

    key->inited = 1;

}



uint8_t Key_Scan(Key_t* key)

{

    uint8_t press = 0;

    uint8_t state = 0;

    uint8_t states = 0;



    if (key && key->inited) {

        //移出上一次的扫描状态并存入本次的扫描状态

        states = key->states;

        states <<= 1;

        states |= Key_GetPinState(key);

        key->states = states;



        state = CountOne(states) ? 1 : 0;        //4次采样全部为0才判定为低电平

        if (state != key->state) {          //引脚状态发生变化

            key->state = state;

            if (state) {

                key->release = 1;

            }

            else {

                press = 1;

                key->press = 1;

            }

        }

    }



    return press;

}
