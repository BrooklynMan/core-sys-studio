// authors: yumeng wang, adam mcbride, nico, and caio
// with code from: sean huges, marco weibel

#include <SoftwareSerial.h>

SoftwareSerial xbeeSerial(2, 3);  //RX, TX

const int buttonPin = 8;  //button
const int redLedPin = 6;  //red led
const int greenLedPin = 5;  //green led
const int potPin = A0; //potentiometer

int potVal = 0; //value of the potentiometer
int buttonState = HIGH;  //starting value of button

const char myName0[] = "Adam ";
const char myName1[] = "Nico ";
const char myName2[] = "Caio ";
const char myName3[] = "Adam ";

const char* const groupName[] = { myName0, myName1, myName2, myName3 };

//String buffer = "";
void setup() {
  Serial.begin(9600);
  Serial.println("Broadcasting your name. See if others receive it.");

  xbeeSerial.begin(9600);
  xbeeSerial.println("Hey, it's Adam!");

  pinMode(buttonPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

}

void loop() {
  broadcast();
  serialCheck();
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {

    if (xbeeSerial.available()) {

      potVal = analogRead(potPin);

      xbeeSerial.println(myName0 + potVal + '\n');

      digitalWrite(greenLedPin, HIGH);
      delay(500);
      digitalWrite(greenLedPin, LOW);
    }
  }
}

void serialCheck() {

  if (Serial.available()) {
    
    xbeeSerial.write(Serial.read());
    String buffer;

    //Serial.println("work!");

    buffer = xbeeSerial.readStringUntil('\n');

    for (int i = 0; i < 4; i++) {
      if (buffer.startsWith(groupName[i], 0)) {
        Serial.println(buffer);
        int brightness = xbeeSerial.parseInt();
        digitalWrite(redLedPin, brightness);
        delay(500);
        digitalWrite(redLedPin, LOW);
      }
    }
  } else {
    
    //Serial.println("not printing");
    
  }
}
