//library usage
#include <Servo.h>. //motor library
Servo s1;
#include <FastLED.h> //LED library
#include <Arduino.h>

#include <Keypad.h> //Keypad library



//components declarion 

  //components controlled by time
    //LED*************
#define LED_PIN 13
#define NUM_LEDS 20
CRGB leds[NUM_LEDS];
int BrightPot = A0;
int BrightPotVal = 0;
int BrightOutVal = 0;

int RedPot = A1;
int RedPotVal = 0;
int RedOutVal = 0;

int GreenPot = A2;
int GreenPotVal = 0;
int GreenOutVal = 0;

int BluePot = A3;
int BluePotVal = 0;
int BlueOutVal = 0;

//buzzer***************
const int buzzer = 51;
const float songSpeed = 1.0;

// Defining frequency of each music note
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_G5 784
#define NOTE_A5 880
#define NOTE_B5 988

// Music notes of the song, 0 is a rest/pulse
int notes[] = {
    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_D5, NOTE_E5, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
    NOTE_C5, NOTE_A4, NOTE_B4, 0,

    NOTE_A4, NOTE_A4,
    //Repeat of first part
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_D5, NOTE_E5, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
    NOTE_C5, NOTE_A4, NOTE_B4, 0,
    //End of Repeat

    NOTE_E5, 0, 0, NOTE_F5, 0, 0,
    NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
    NOTE_D5, 0, 0, NOTE_C5, 0, 0,
    NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

    NOTE_E5, 0, 0, NOTE_F5, 0, 0,
    NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
    NOTE_D5, 0, 0, NOTE_C5, 0, 0,
    NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4};

// Durations (in ms) of each music note of the song
// Quarter Note is 250 ms when songSpeed = 1.0
int durations[] = {
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 125, 250, 125,

    125, 125, 250, 125, 125,
    250, 125, 250, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 375,

    250, 125,
    //Rpeat of First Part
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 125, 250, 125,

    125, 125, 250, 125, 125,
    250, 125, 250, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 375,
    //End of Repeat

    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 125, 125, 125, 375,
    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 500,

    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 125, 125, 125, 375,
    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 500};

const int totalNotes = sizeof(notes) / sizeof(int);



//Keypad **************
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {23,25,27,29};
byte colPins[COLS] = {31,33,35,37};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  //if server sent out signal {
  //servo**************
  s1.attach(49);
  //only turn once and turn back to effectively push the button
  s1. write(0);
  delay(1000);
  s1.write(180);
  delay(1000);
  s1.write(0);

  //buzzer **************
  const int totalNotes = sizeof(notes) / sizeof(int);
  // Loop through each note
  for (int i = 0; i < totalNotes; i++)
  {
    const int currentNote = notes[i];
    float wait = durations[i] / songSpeed;
    // Play tone if currentNote is not 0 frequency, otherwise pause (noTone)
    if (currentNote != 0)
    {
      tone(buzzer, notes[i], wait); // tone(pin, frequency, duration)
    }
    else
    {
      noTone(buzzer);
    }
    // delay is used to wait for tone to finish playing before moving to next loop
    delay(wait);
  }



  //led***********
  // put your setup code here, to run once:
 
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  
   FastLED.setBrightness(BrightOutVal);
  BrightPotVal = analogRead(BrightPot);
  BrightOutVal = map(BrightPotVal, 0, 1023, 0, 255);
  analogWrite(NUM_LEDS, BrightOutVal);

  if (BrightOutVal <= 5){
    Serial.print("");
  }
  if (BrightOutVal >= 10){
    Serial.print("Brightness Value= ");
    Serial.println(BrightOutVal);
  }

  //Red led
  RedPotVal = analogRead(RedPot);
  RedOutVal = map(RedPotVal, 0, 1023, 0, 255);
  analogWrite(NUM_LEDS, RedOutVal);
  if (RedOutVal <= 5){
    Serial.print("");
  }
  if (RedOutVal >= 10){
    Serial.print("Red Value= ");
    Serial.println(RedOutVal);
  }

   //Green Led
  GreenPotVal = analogRead(GreenPot);
  GreenOutVal = map(GreenPotVal, 0, 1023, 0, 255);
  analogWrite(NUM_LEDS, GreenOutVal);
  if (GreenOutVal <= 5){
    Serial.print("");
  }
  if (GreenOutVal >= 10){
    Serial.print("Green Value= ");
    Serial.println(GreenOutVal);
  }


    //Blue Led
  BluePotVal = analogRead(BluePot);
  BlueOutVal = map(BluePotVal, 0, 1023, 0, 255);
  analogWrite(NUM_LEDS, BlueOutVal);
  if (BlueOutVal <= 5){
    Serial.print("");
  }
  if (BlueOutVal >= 10){
    Serial.print("Blue Value= ");
    Serial.println(BlueOutVal);
  }

  for (int i = 0; i <= NUM_LEDS-1; i++){

    leds[i] = CRGB(RedOutVal, GreenOutVal, BlueOutVal);
    FastLED.show();
    delay(100);

  }
  for (int i = NUM_LEDS -1; i>0; i--){
    leds[i] = CRGB(RedOutVal, GreenOutVal, BlueOutVal);
    FastLED.show();
    FastLED.clear();
    delay(100);
  }




}

void loop() {
  // put your main code here, to run repeatedly:
  // Brightness
  FastLED.setBrightness(BrightOutVal);
  BrightPotVal = analogRead(BrightPot);
  BrightOutVal = map(BrightPotVal, 0, 1023, 0, 255);
  analogWrite(NUM_LEDS, BrightOutVal);

  if (BrightOutVal <= 5){
    Serial.print("");
  }
  if (BrightOutVal >= 10){
    Serial.print("Brightness Value= ");
    Serial.println(BrightOutVal);
  }

  //Red led
  RedPotVal = analogRead(RedPot);
  RedOutVal = map(RedPotVal, 0, 1023, 0, 255);
  analogWrite(NUM_LEDS, RedOutVal);
  if (RedOutVal <= 5){
    Serial.print("");
  }
  if (RedOutVal >= 10){
    Serial.print("Red Value= ");
    Serial.println(RedOutVal);
  }

   //Green Led
  GreenPotVal = analogRead(GreenPot);
  GreenOutVal = map(GreenPotVal, 0, 1023, 0, 255);
  analogWrite(NUM_LEDS, GreenOutVal);
  if (GreenOutVal <= 5){
    Serial.print("");
  }
  if (GreenOutVal >= 10){
    Serial.print("Green Value= ");
    Serial.println(GreenOutVal);
  }


    //Blue Led
  BluePotVal = analogRead(BluePot);
  BlueOutVal = map(BluePotVal, 0, 1023, 0, 255);
  analogWrite(NUM_LEDS, BlueOutVal);
  if (BlueOutVal <= 5){
    Serial.print("");
  }
  if (BlueOutVal >= 10){
    Serial.print("Blue Value= ");
    Serial.println(BlueOutVal);
  }

  for (int i = 0; i <= NUM_LEDS-1; i++){

    leds[i] = CRGB(RedOutVal, GreenOutVal, BlueOutVal);
    FastLED.show();
    delay(100);

  }
  for (int i = NUM_LEDS -1; i>0; i--){
    leds[i] = CRGB(RedOutVal, GreenOutVal, BlueOutVal);
    FastLED.show();
    FastLED.clear();
    delay(100);
  }



  //loop for keypad
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
  }



}