#include <Brain.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

Brain brain(Serial);

class AttentionLevel
{
  public:
    int pageNumber;
    double average; //keeps track of average attention score
    AttentionLevel()
    {
      pageNumber = -500;
      average = -500;
    }
    AttentionLevel(int pnum, double mean)
    {
      pageNumber = pnum;
      average = mean;
    }
    bool operator< (const AttentionLevel &rhs)
    {
      return average < rhs.average;
    }
};

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
bool newPage = false;

double lowAttentionArr[10]; //lowest 10 scores

void turnLCDOn(){
  lcd.setCursor(0,0);
  lcd.print("Welcome!");
  isLCDOn = true;
}
void printInformation(){
  lcd.clear();
  //Output recommendation of pages to re-read
  double tempMin = 10000;
  int minimum = 0;
  for(int i = 0; i < 10; i++) {
    Serial.println("Low Score" + String(i+1) + " : " + String(lowAttentionArr[i]));
    //lcd.println("Low Score" + String(i+1) + " : " + String(lowAttentionArr[i]));
    if(tempMin > lowAttentionArr[i] && lowAttentionArr[i] > 0) {
      tempMin = lowAttentionArr[i];
      minimum = i;
    }
  }
  lcd.println("Review page " + String(minimum + 1));
  lcd.setCursor(0,1);
  lcd.println("Min Score: " + String(tempMin));
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
      newPage = true;
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

double sum = 0;
double average = 0;
int numOfInstances = 0;

void processBrainWaves() {
  
  if (brain.update()) {
    checkButtonPress();
    numOfInstances++;
    //Serial.println(brain.readErrors());
    //Serial.println(brain.readCSV());
    attention = brain.readAttention();
    //Serial.println(attention);
    delay(500);
    
    if(!newPage) 
    {
      sum += attention;
    }
    else {
      newPage = false;
    }
    //Serial.println("Mean: " + String(average));
    average = sum/numOfInstances;

    lowAttentionArr[currentPageNumber] = average;
    lcd.setCursor(0,1);
    lcd.print("Focus Score: " + String(attention));
  }
}
void loop() { 
  checkButtonPress();
  checkBluetooth(); //shouldn't go into here after it start
  if(start) {
    processBrainWaves();
  }
  
}
