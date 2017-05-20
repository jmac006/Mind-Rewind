#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

const int BUTTON_PIN = 5;
const int RED_LED = 3;
const int BLUE_LED = 2;

LiquidCrystal lcd(4,5,6,12,9,13);

SoftwareSerial mySerial(7, 8); // RX, TX

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
	Serial.begin(9600);
	// If the baudrate of the HM-10 module has been updated,
	// you may need to change 9600 by another value
	// Once you have found the correct baudrate,
	// you can update it using AT+BAUDx command 
	// e.g. AT+BAUD0 for 9600 bauds
  pinMode(BUTTON_PIN, INPUT);
  //pinMode(BLUE_LED, OUTPUT);
  //pinMode(RED_LED, OUTPUT);
	mySerial.begin(9600);
  
  lcd.begin(16,2);
}

void loop() {  
	
	buttonPressed = digitalRead(BUTTON_PIN);
	if(buttonPressed != buttonState) { //if the button state has changed
    if(buttonPressed == HIGH) {
      buttonCount++;
      //Serial.println(buttonCount);
    }
	}
  buttonState = buttonPressed;
  
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
