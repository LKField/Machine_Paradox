#include <Adafruit_NeoPixel.h>

#define LED_PIN 21
#define LED_COUNT 10
#define BUTTON_PIN 11

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int buttonState = 0;  // variable for reading the pushbutton status

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT);
  // initialize the RGB LEDs 
  strip.begin();
  strip.show();
  strip.setBrightness(50);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON_PIN);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // RGBs turn OFF  
    strip.clear();
    strip.show();
  } else {
    // RGBs turn ON Red 
    for(int i = strip.numPixels()-1; i >= 0; i--){
      strip.setPixelColor(i, random(100, 200), random(50), 0, 0);   // random brightness of LEDs to try to create 'fire' effect 
      strip.show();
      // add a delay to make the flicker slower 
      delay(10);
    }
  }
}
