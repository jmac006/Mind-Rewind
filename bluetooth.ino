#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Brain.h>

Brain brain(Serial);
int attention;

const int BUTTON_PIN = 5;
const int RED_LED = 3;
const int BLUE_LED = 2;
const int RX = 7;
const int TX = 8;

//RS = PIN4, Enable = PIN5, D4-D7 = PIN6,12,9,13
LiquidCrystal lcd(4,5,6,12,9,13); 

SoftwareSerial mySerial(RX, TX); // RX, TX

int buttonCount = 0;
int buttonPressed = 0;
int buttonState = 0;
int bluetoothRead = -1;

void test(){
  lcd.setCursor(0,0);
  lcd.print("testing");
  lcd.setCursor(0,1);
  lcd.print("BlueTooth");
}
void turnOn(){
  lcd.setCursor(0,0);
  lcd.print("");
  lcd.setCursor(0,1);
  lcd.print("");
}
void turnOff(){
 
}
void setup() {
  attention = brain.readAttention();
	Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  //pinMode(BLUE_LED, OUTPUT);
  //pinMode(RED_LED, OUTPUT);
	
  lcd.begin(16,2);
  analogWrite(11,255); //Powers the EEG headset
}

void checkButtonPress() {
  buttonPressed = digitalRead(BUTTON_PIN);
  if(buttonPressed != buttonState) { //if the button state has changed
    if(buttonPressed == HIGH) {
      buttonCount++;
      //Serial.println(buttonCount);
    }
  }
  buttonState = buttonPressed;
}

void checkBluetooth() {
  if (mySerial.available()) {
    Serial.println("bluetooth is available");
    bluetoothRead = mySerial.read();  
    Serial.println("Got input:");
    if (bluetoothRead == 1)
    {
      // Non-zero input means "turn on LED".
      Serial.println("Red LED On");
      Serial.println(bluetoothRead);
      analogWrite(RED_LED, 255);
    }
    else if (bluetoothRead == 2)
    {
      // Input value zero means "turn off LED".
      Serial.println("Blue LED on");
      Serial.println(bluetoothRead);
      analogWrite(BLUE_LED, 255);
    } 
    else if (bluetoothRead == 3)
    {
      // Input value zero means "turn off LED".
      Serial.println("Red LED off");
      Serial.println(bluetoothRead);
      digitalWrite(RED_LED, LOW);
    }
    else if (bluetoothRead == 4)
    {
      // Input value zero means "turn off LED".
      //Serial.println("Blue LED off");
      //Serial.println(bluetoothRead);
      //digitalWrite(BLUE_LED, LOW);
      test();
    }
  }
}

void loop() { 
  checkButtonPress();
	checkBluetooth();
}
