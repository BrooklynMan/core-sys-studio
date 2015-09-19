// with code from: sean huges, marco weibo 

#include <SoftwareSerial.h>

SoftwareSerial xbeeSerial(2, 3);  //RX, TX

const int button = 8;  //button
const int redLed = 6;  //red led
const int greenLed = 5;  //green led
const int pot = 0;  //potentiometer

int potVal = 0; //value of the potentiometer
int buttonState = LOW;  //starting value of button

//String friendMessage = "
String myName0 = "Adam ";
String myName1 = "Nico ";
String myName2 = "Caio ";
String myName3 = "Adam ";
String ender = "\n";

String groupName[] = { myName0, myName1, myName2, myName3 };

//String buffer = "";
void setup() {
  Serial.begin(9600);
  Serial.println("Broadcasting your name. See if others receive it.");

  xbeeSerial.begin(9600);
  xbeeSerial.println("Hey, it's Adam!");

  pinMode(button, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

}

void loop() {
  int buttonState = digitalRead(button);

  if (buttonState == HIGH) {

    potVal = analogRead(pot);

    xbeeSerial.println(myName0 + potVal + ender);
    // xbeeSerial.println(myName2 + potVal + ender);
    // xbeeSerial.println(myName3 + potVal + ender);

    digitalWrite(greenLed, HIGH);
    delay(500);
    digitalWrite(greenLed, LOW);
    //delay(1000);
  }

  serialCheck();
}

void serialCheck() {
  if (xbeeSerial.available() > 0) {
    String buffer;
    buffer = xbeeSerial.readStringUntil('\n');  //error
    if (buffer.startsWith(myName2, 0)) {
      Serial.println(buffer);
      int bright = xbeeSerial.parseInt();
      digitalWrite(redLed, bright);
      delay(500);
      digitalWrite(redLed, LOW);
    }
  }
}
