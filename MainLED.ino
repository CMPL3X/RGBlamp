// MAIN V1

#include <Wire.h>
#include <U8g2lib.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 2
#define NUM_LEDS 1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 4, /* data=*/ 3);

const int button1Pin = 0;
const int button2Pin = 1;
const int button3Pin = 5;
const int button4Pin = 10;
const int buttonPin = 9;
const int redPin = 8;
const int greenPin = 7;
const int bluePin = 6;

int mode = 0;
int R = 0;
int G = 0;
int B = 0;
int StrSpeed = 40;
int lock = 0;
int lock2 = 0;
int lock3 = 0;
int lock4 = 0;

void setup() {
  Serial.begin(115200);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  strip.begin();
  strip.show();
  display.begin();
  display.clearBuffer();
  display.setFont(u8g2_font_ncenB10_tr);
  ledColor(strip.Color(0, 0, 0));
}

void loop() {
  int button1State = digitalRead(button1Pin);
  int button2State = digitalRead(button2Pin);
  int button3State = digitalRead(button3Pin);
  int button4State = digitalRead(button4Pin);
  int buttonState = digitalRead(buttonPin);
  if (R >= 251 ) {
      R = 0;
    } 
  if (G >= 251 ) {
    G = 0;
  } 
  if (B >= 251 ) {
    B = 0;
  } 
  display.clearBuffer();
  display.setFont(u8g2_font_helvR18_tr);
  display.setCursor(70, 30);
  display.print("250");
  display.setFont(u8g2_font_profont12_tr);
  display.setCursor(100, 45);
  display.print("MAX");
  display.setFont(u8g2_font_ncenB10_tr);
  display.setCursor(0, 15);
  display.print("R: " + String(R));
  display.setCursor(0, 30);
  display.print("G: " + String(G));
  display.setCursor(0, 45);
  display.print("B: " + String(B));
  display.setFont(u8g2_font_profont12_tr);
  display.setCursor(0, 60);
  display.print("bttn4: mode");
  display.setFont(u8g2_font_ncenB10_tr);
  display.sendBuffer();
  while (lock4 == 1) {
    delay(1000);
    lock4 = 0;
  }
  if (button1State == HIGH) {
    R += 25;
    ledStripColor(R, G, B);
    ledColor(strip.Color(R, G, B));
    display.clearBuffer();
  }else if (button2State == HIGH) {
    G += 25;
    ledStripColor(R, G, B);
    ledColor(strip.Color(R, G, B));
    display.clearBuffer();
  }else if (button3State == HIGH) {
    B += 25;
    ledStripColor(R, G, B);
    ledColor(strip.Color(R, G, B));
    display.clearBuffer();
  }else if (button4State == HIGH) {
    display.clearBuffer();
    lock = 1;
    display.setCursor(0, 15);
    display.print("1  Rainbow");
    display.setCursor(0, 30);
    display.print("2  W / B");
    display.sendBuffer();
    display.setCursor(0, 45);
    display.print("3  R / B");
    display.sendBuffer();
    display.setCursor(0, 60);
    display.print("4  Strobe");
    display.sendBuffer();
    delay(2000);
    while (lock == 1){
      int button1State = digitalRead(button1Pin);
      int button2State = digitalRead(button2Pin);
      int button3State = digitalRead(button3Pin);
      int button4State = digitalRead(button4Pin);
      int buttonState = digitalRead(buttonPin);
      if (button1State == HIGH){
        mode = 1;
        lock = 0;
        lock2 = 1;
        lock3 = 1;
        display.clearBuffer();
      }
      if (button2State == HIGH){
        mode = 2;
        lock = 0;
        lock2 = 1;
        lock3 = 1;
        display.clearBuffer();
      }
      if (button3State == HIGH){
        mode = 3;
        lock = 0;
        lock2 = 1;
        lock3 = 1;
        display.clearBuffer();
      }
      if (button4State == HIGH){
        mode = 4;
        lock = 0;
        lock2 = 1;
        lock3 = 1;
        display.clearBuffer();
      }
    }
  }
  if (lock3 == 1){
    display.setCursor(0, 15);
    display.print("Fx");
    display.sendBuffer();
    delay(1000);
    lock3 = 0;
  }
  while (lock2 == 1){
    int button4State = digitalRead(button4Pin);
    if (mode == 1){
      display.clearBuffer();
      display.setCursor(0, 15);
      display.print("Rainbow");
      display.setCursor(55, 30);
      display.print("Fx");
      display.sendBuffer();
      rainbowEffect();
      if (button4State == HIGH) {
        mode = 0;
        lock2 = 0;
        lock4 = 1;
      }
    }else if (mode == 2){
      display.clearBuffer();
      display.setCursor(0, 15);
      display.print("W / B");
      display.sendBuffer();
      fadeToWhite();
      fadeToBlack();
      if (button4State == HIGH) {
        mode = 0;
        lock2 = 0;
        lock4 = 1;
      }
    }else if (mode == 3){
      display.clearBuffer();
      display.setCursor(0, 15);
      display.print("R / B");
      display.sendBuffer();
      fadeToRed();
      fadeToBlack2();
      if (button4State == HIGH) {
        mode = 0;
        lock2 = 0;
        lock4 = 1;
      }
    }else if (mode == 4){
      display.clearBuffer();
      display.setCursor(0, 15);
      display.print("Strobe");
      display.setCursor(0, 30);
      display.print("Speed: " + String(StrSpeed));
      int button2State = digitalRead(button2Pin);
      int button3State = digitalRead(button3Pin);
      if (button2State == HIGH) {
        StrSpeed -= 5;
      } else if (button3State == HIGH) {
        StrSpeed += 5;
      }
      if (StrSpeed <= 0) {
        StrSpeed = 5;
      }
      display.sendBuffer();
      ledStripColor(255, 255, 255);
      ledColor(strip.Color(255, 255, 255));
      delay(StrSpeed);
      ledStripColor(0, 0, 0);
      ledColor(strip.Color(0, 0, 0));
      delay(StrSpeed);
      if (button4State == HIGH) {
        mode = 0;
        lock2 = 0;
        lock4 = 1;
      }
    }
  }
  delay(200);
}

void ledColor(uint32_t color) {
  strip.fill(color, 0, strip.numPixels());
  strip.show();
}

void ledStripColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void rainbowEffect() {
  int delayTime = 10;

  for (int i = 0; i <= 255; i++) {
    analogWrite(redPin, 255 - i);
    analogWrite(greenPin, i);
    analogWrite(bluePin, 0);
    delay(delayTime);
  }

  for (int i = 0; i <= 255; i++) {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255 - i);
    analogWrite(bluePin, i);
    delay(delayTime);
  }

  for (int i = 0; i <= 255; i++) {
    analogWrite(redPin, i);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 255 - i);
    delay(delayTime);
  }
}

void fadeToWhite() {
  for (int i = 0; i <= 255; i++) {
    analogWrite(redPin, i);
    analogWrite(greenPin, i);
    analogWrite(bluePin, i);
    delay(10);
  }
}

void fadeToBlack() {
  for (int i = 255; i >= 0; i--) {
    analogWrite(redPin, i);
    analogWrite(greenPin, i);
    analogWrite(bluePin, i);
    delay(10);
  }
}

void fadeToBlack2() {
  for (int i = 255; i >= 0; i--) {
    analogWrite(redPin, i);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    delay(10);
  }
}

void fadeToRed() {
  for (int i = 0; i <= 255; i++) {
    analogWrite(redPin, i);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    delay(10);
  }
}
