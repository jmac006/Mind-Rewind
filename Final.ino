#include <Brain.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

Brain brain(Serial);
int attention;

const int BUTTON_PIN = 2;
const int RED_LED = 3;
const int RX = 7;
const int TX = 8;

//RS = PIN4, Enable = PIN5, D4-D7 = PIN6,12,9,13
LiquidCrystal lcd(4,5,6,12,9,13); 

SoftwareSerial mySerial(RX, TX); // RX, TX

int buttonPressed = 0;
int buttonState = 0;
int bluetoothRead = -1;
int currentPageNumber = 1;
int startingPageNumber = 1;
bool isLCDOn = false;
bool start = false;

void turnLCDOn(){
  lcd.setCursor(0,0);
  lcd.print("Welcome!");
  isLCDOn = true;
}
void printInformation(){
  //Output recommendation of pages to re-read
}
void setup() {
  attention = brain.readAttention();
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  //pinMode(RED_LED, OUTPUT);
  
  lcd.begin(16,2);
  analogWrite(11,255); //Powers the EEG headset
}

void checkButtonPress() {
  buttonPressed = digitalRead(BUTTON_PIN);
  if(buttonPressed != buttonState) { //if the button state has changed
    if(buttonPressed == HIGH) { //if there's a button press
      currentPageNumber++;
      Serial.println(currentPageNumber);
      lcd.clear();
      String outputPageNum = "Current Page: " + String(currentPageNumber);
      lcd.print(outputPageNum);
    }
    delay(5); //prevent double click
  }
  buttonState = buttonPressed;
}

void checkBluetooth() {
  if (mySerial.available()) {
    Serial.println("bluetooth is available");
    bluetoothRead = mySerial.read();  
    Serial.println("Got input:");
    if (bluetoothRead == 0)
    {
      //Stops collecting brain information, outputs the recommendation of pages to re-read
      printInformation();
      lcd.print("All done!");
    }
    else if (bluetoothRead == 0xFF)
    {
      turnLCDOn();
    }
    else if ((bluetoothRead != 0 || bluetoothRead != 0xFF) && isLCDOn)
    {
      //If the bluetoothRead is anything else, the user entered a page number.
      //The LCD must be on to enter the current page number.
      startingPageNumber = bluetoothRead;
      currentPageNumber = bluetoothRead;
      lcd.clear();
      String outputPageNum = "Current Page: " + String(currentPageNumber);
      lcd.print(outputPageNum);
      start = true;
    }
    
  }
}

void processBrainWaves() {
  if (brain.update()) {
    Serial.println(brain.readErrors());
    Serial.println(brain.readCSV());
    attention = brain.readAttention();
    Serial.println(attention);
    delay(1000);
  }
  if(attention > 10){
    lcd.setCursor(0,0);
    lcd.print("testing");
    lcd.setCursor(0,1);
    lcd.print("EEG");
  }
}
void loop() { 
  checkButtonPress();
  checkBluetooth(); //shouldn't go into here after it start
  if(start) {
    processBrainWaves();
  }
  
}
