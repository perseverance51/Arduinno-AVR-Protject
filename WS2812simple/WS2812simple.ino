// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 80 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 200 // Time (in milliseconds) to pause between pixels

// 彩虹沿整个带状循环
void rainbow(unsigned int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<pixels.numPixels(); i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
     pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    }
   pixels.show(); // 更新当前带内容
    delay(wait);  // 暂停wait毫秒
  }
}

void theaterChaseRainbow(unsigned int wait) {
  int firstPixelHue = 0;     // 第一个像素从红色开始(色调0)
  for(int a=0; a<30; a++) {  // 重复30次
    for(int b=0; b<3; b++) { 
      pixels.clear();         //   将RAM中的所有像素设置为0(关闭)
      for(int c=b; c <pixels.numPixels(); c += 3) {
        int  hue   = firstPixelHue + c * 65536L / pixels.numPixels();
        uint32_t color = pixels.gamma32(pixels.ColorHSV(hue));
        pixels.setPixelColor(c, color); 
      }
      pixels.show();              
      delay(wait);               
      firstPixelHue += 65536 / 90; 
    }
  }
}
void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
//  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
//    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
//    // Here we're using a moderately bright green color:
//    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
//    pixels.show();   // Send the updated pixel colors to the hardware.
//    delay(DELAYVAL); // Pause before next pass through loop
//  }
theaterChaseRainbow(50);
rainbow(50);
}
