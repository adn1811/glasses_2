/* GDES3015 Wearable Computing 
 * 1 button used to switch between 2 LEDS with fade sequences
 * Based on Arduino Fading example 
 */
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 9
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

int buttonPin = 6;     // button connected to digital pin 2
int buttonValue;

void setup() {
  // nothing happens in setup
  pinMode(buttonPin, INPUT_PULLUP);
  strip.begin();
  strip.show();
  Serial.begin(9600);
}

void loop() {
  buttonValue = digitalRead(buttonPin);
  Serial.println(buttonValue);

  if (buttonValue == LOW) {
        whitefade();     
  } else {
        rfade();
    }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
 
void whitefade() {
   uint16_t i, j;
  for (j = 0; j < 255; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, j, j, j);
    }
    strip.show();
    delay(10);
  }
  delay(150);
  
  for (j = 255; j > 0; j--) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, j, j, j);
    }
    strip.show();
    delay(10);
  }
  delay(150);
}



void rfade() {
 void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

