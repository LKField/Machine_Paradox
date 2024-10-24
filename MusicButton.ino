#include <DFRobotDFPlayerMini.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//#define SERIAL_BAUD 9600
//#define SOFTWARE_SERIAL_BAUD 9600
#define BUSY LOW
#define BUTTON_PIN 11
#define KNOB_PIN 2
#define LED_PIN 7
#define TR_PIN 4
#define RGB_PIN 21
#define RGB_COUNT 10

const byte BUSY_PIN = 9;  //DFR busy pin is on D9
long TR;                  // define the touch sensor 
long pan_thresh = 90000;  // define the pan threshold 

bool buttonState = 0;  // variable for reading the pushbutton status
bool knobState = 0;

int new_index = 3; // index for media file
int min_index = 3; // minimum index for media files
int max_index = 6; // maximum index for media files 

DFRobotDFPlayerMini myDFPlayer;
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(RGB_COUNT, RGB_PIN, NEO_GRB + NEO_KHZ800);

// Play DFR audio and check for playback completion
void playAudio(int fileNumber) {
  myDFPlayer.playMp3Folder(fileNumber);
  delay(11000);
  // while (digitalRead(BUSY_PIN) == BUSY) {
  //   ;  // This loop executes while the DFR BUSY pin is LOW indicating playback in progress.
  // }
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB
  }
  Serial0.begin(9600);
  delay(10);

  // initialize pin modes:
  pinMode(BUSY_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(KNOB_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // initialize the RGB LEDs
  strip.begin();
  strip.setBrightness(20);
  strip.show();
  setRGB('O');

  Serial.println("Initializing DFPlayer...");

  // Initialize the DFPlayer Mini
  if (!myDFPlayer.begin(Serial0)) {
    Serial.println("DFPlayer Mini not detected. Please check connections and if SD card is inserted.");
    while (true) {
      ;
    }
  }
  Serial.println("DFPlayer initialized!");

  // myDFPlayer.setTimeOut(500);
  myDFPlayer.volume(30);
  // myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  // myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  // playAudio(1);
}

void loop() {
  knobState = digitalRead(KNOB_PIN);                // read KNOB_PIN 

  if (knobState == HIGH) {                          // proceed with code if knobState is HIGH 
    myDFPlayer.play(1);                             // play "That's not how you turn me on, darling"
    strip.setBrightness(10);                        // set 'fire' to low 
    Serial.print("Knob State: ");             
    Serial.println(knobState);
    
    while (knobState == HIGH) {
      digitalWrite(LED_PIN, HIGH);                  // turn front indicator light on
      setRGB('B');                                  // turn RGB LEDs to 'blue fire'
      buttonState = digitalRead(BUTTON_PIN);        // read BUTTON_PIN
      digitalRead(BUSY_PIN);                        // read BUSY_PIN 
      TR = touchRead(TR_PIN);                       // read TR for capacitive touch 
      delay(100);                                   // delay to allow cap touch read 
    //  Serial.println(TR);
      
    if (buttonState == HIGH && BUSY == LOW){        // button press code 
      strip.setBrightness(100);                     // set 'fire' to high 
      new_index = random(min_index,max_index+1);    // random index generator to audio file 
      Serial.println(new_index);
      myDFPlayer.play(new_index);                   // play the random audio file 
        // Serial.print("Button State: ");
        // Serial.println(TR);
      }
      else if (TR > pan_thresh && BUSY == LOW) {    // capacitive touch sensor code 
        myDFPlayer.play(2);                         // play "No, no, touch me where I'm hot"
        strip.setBrightness(10);
        setRGB('R');
      //  Serial.print("Capacitive Touch State: ");
      //  Serial.println(TR)
        while (TR > pan_thresh) {                   // while the threshold is met 
          TR = touchRead(TR_PIN);                   // read TR_PIN again 
          delay(100);                               // delay to allow cap touch read 
          Serial.print("Nada");
        }
      } else if (BUSY == LOW) {                     // No input is being activated
        Serial.print("No inputs pressed: ");
        Serial.println(TR);
        strip.setBrightness(10);
      }
    knobState = digitalRead(KNOB_PIN);              // reread the KNOB_PIN value 
    }

  } else {                                          // knobState is LOW - turn everything off 
  //  Serial.print("Knob State: ");
  //  Serial.println(knobState);
    digitalWrite(LED_PIN, LOW);
    setRGB('O');
    delay(10);
  }
}


// RGB color defining function 
void setRGB(char color) {
  if (color == 'R') {
    strip.clear();
    strip.show();
    // RGBs turn ON RED 'fire'
    //Serial.println("Color set to Red Fire");
    for(int i = strip.numPixels()-1; i >= 0; i--){
      strip.setPixelColor(i, random(100, 255), random(50), 0, 0);   // random brightness of LEDs to try to create red 'fire' effect 
      strip.show();
    }
  } else if (color == 'B') {
      strip.clear();
      strip.show();
      // RGBs turn ON BLUE 'fire 
      //Serial.println("Color set to Blue Fire");
      for(int i = strip.numPixels()-1; i >= 0; i--){
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
