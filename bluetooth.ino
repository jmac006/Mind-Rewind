#include <SoftwareSerial.h>

#define BLUE_LED 2
#define RED_LED 3

SoftwareSerial mySerial(7, 8); // RX, TX

void setup() {  
	Serial.begin(9600);
	// If the baudrate of the HM-10 module has been updated,
	// you may need to change 9600 by another value
	// Once you have found the correct baudrate,
	// you can update it using AT+BAUDx command 
	// e.g. AT+BAUD0 for 9600 bauds
	mySerial.begin(9600);
}

void loop() {  
	int c;
	if (mySerial.available()) {
		Serial.println("bluetooth is available");
		c = mySerial.read();  
		Serial.println("Got input:");
		if (c == 1)
		{
			// Non-zero input means "turn on LED".
			Serial.println("Red LED On");
			Serial.println(c);
      analogWrite(RED_LED, 255);
		}
		else if (c == 2)
		{
			// Input value zero means "turn off LED".
			Serial.println("Blue LED on");
			Serial.println(c);
			digitalWrite(BLUE_LED, HIGH);
		} 
		else if (c == 3)
		{
			// Input value zero means "turn off LED".
			Serial.println("Red LED off");
			Serial.println(c);
			digitalWrite(RED_LED, LOW);
		}
		else if (c == 4)
		{
			// Input value zero means "turn off LED".
			Serial.println("Blue LED off");
			Serial.println(c);
			digitalWrite(BLUE_LED, LOW);
		}
	}
}
