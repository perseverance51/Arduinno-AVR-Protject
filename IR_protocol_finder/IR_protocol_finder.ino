
#include <IRremote.h>//如果没有此库点击后面的链接会自动打开管理库搜索对应的库名称: http://librarymanager/All#IRremote

#define RECEIVER_PIN D5 // define the IR receiver pin

IRrecv receiver(RECEIVER_PIN); // create a receiver object of the IRrecv class
decode_results results; // create a results object of the decode_results class
unsigned long key_value = 0; // variable to store the pressed key value

void setup() {
  Serial.begin(9600); // begin serial communication with a baud rate of 9600
  receiver.enableIRIn(); // enable the receiver
  receiver.blink13(true); // enable blinking of the built-in LED when an IR signal is received
}

void loop() {
  if (receiver.decode(&results)) {
    if (results.value == 0XFFFFFFFF) {
      results.value = key_value;
    }
    Serial.println(results.value, HEX);
    switch (results.decode_type) {
      case NEC:
        Serial.println("NEC");
        break;
      case SONY:
        Serial.println("SONY");
        break;
      case RC5:
        Serial.println("RC5");
        break;
      case RC6:
        Serial.println("RC6");
        break;
      case DISH:
        Serial.println("DISH");
        break;
      case SHARP:
        Serial.println("SHARP");
        break;
      case JVC:
        Serial.println("JVC");
        break;
      case KASEIKYO:
        Serial.println("KASEIKYO");
        break;
      case KASEIKYO_JVC:
        Serial.println("KASEIKYO_JVC");
        break; 
      case KASEIKYO_DENON:
        Serial.println("KASEIKYO_DENON");
        break;
      case KASEIKYO_SHARP:
        Serial.println("KASEIKYO_SHARP");
        break;                             
      case KASEIKYO_MITSUBISHI:
        Serial.println("KASEIKYO_MITSUBISHI");
        break;
      case SAMSUNG:
        Serial.println("SAMSUNG");
        break;
      case LG:
        Serial.println("LG");
        break ;
      case LG2:
        Serial.println("LG2");
        break ;
      case WHYNTER:
        Serial.println("WHYNTER");
        break;
      case PANASONIC:
        Serial.println("PANASONIC");
        break;
      case DENON:
        Serial.println("DENON");
        break;
      case BOSEWAVE:
        Serial.println("BOSEWAVE");
        break;
      case LEGO_PF:
        Serial.println("LEGO_PF");
        break;
      case MAGIQUEST:
        Serial.println("MAGIQUEST");
        break;
      case ONKYO:
        Serial.println("ONKYO");
        break; 
       case APPLE:
        Serial.println("APPLE");
        break;       
      default:
      case UNKNOWN:
        Serial.println("UNKNOWN");
        break ;
    }
    key_value = results.value;
    receiver.resume();
  }
}
