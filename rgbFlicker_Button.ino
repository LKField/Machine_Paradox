// This code will read a pushbutton and a capacitive sensor and change the RGB LEDs accordingly 
#include <Adafruit_NeoPixel.h>

// Define the LED, Button, and Capacitive Sensor Pins as constants 
#define LED_PIN 21
#define LED_COUNT 10
#define BUTTON_PIN 11
#define CAP_PIN 8

// Define the touch sensor and threshold 
long TR;
long threshold = 100000;

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int buttonState = 0;  // variable for reading the pushbutton status

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT);
  // initialize the RGB LEDs 
  strip.begin();
  strip.show();
  strip.setBrightness(100);
  setRGB('O');    // RGBs turn OFF
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON_PIN);

  setRGB('R');  // RGBs turn ON Red 
 
  if (buttonState == HIGH) {  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    setRGB('O');    // RGBs turn OFF

    // PLAY BUTTON SOUND HERE 
    Serial.println("PLAY BUTTON SOUND HERE");
  
  } else {    // if the pushbutton is NOT pressed. buttonState is LOW - 'else'
    // read the capacitive sensor
    TR = touchRead(CAP_PIN);
    Serial.println(TR);
    
    if (TR > threshold){   // check if the capactive sensor is above threshold - pressed 
      setRGB('B');    // RGBs turn ON Blue 
      //PLAY CAPACITIVE SENSOR SOUND HERE 
      Serial.println("PLAY CAPACITIVE SENSOR SOUND HERE");
      delay(100);     // delay to keep the blue on - will be removed when audio plays 
    }
     else {   // if the capacitive sensor is NOT pressed 
      setRGB('R');    // RGBs turn ON Red 
    }
  }
}

// RGB color defining function 
void setRGB(char color) {
  if (color == 'R') {
    strip.clear();
    strip.show();
    // RGBs turn ON RED 'fire'
    Serial.println("Color set to Red Fire");
    for(int i = strip.numPixels()-1; i >= 0; i--){
      strip.setPixelColor(i, random(100, 255), random(50), 0, 0);   // random brightness of LEDs to try to create red 'fire' effect 
      strip.show();
    }
  } else if (color == 'B') {
      strip.clear();
      strip.show();
      // RGBs turn ON BLUE 'fire 
      Serial.println("Color set to Blue Fire");
      for(int i = strip.numPixels()-1; i >= 0; i--){
        // strip.setPixelColor(i, 0, 0, random(200, 255), 0);   // random brightness of LEDs to try to create blue 'fire' effect 
        strip.setPixelColor(i, 0, random(50), random(100, 255), 0);   // random brightness of LEDs to try to create blue 'fire' effect 
        strip.show();
      }
  } else if (color == 'O') {
    // RGBs turn OFF  
    strip.clear();
    strip.show();
  } else {
    Serial.println("Color not supported");
  }
}