#include <Servo.h>
#include <Wire.h>

#define COIN_PIN 8

 //TOMBOL CONFIRM
const int buttonCONFIRM = 12;
const int buttonCANCEL = 13;
const int notifLED = 11;     // the number of the pushbutton pin
// const int ledPin =  10; 
 //ROLLER
 int in1= 6;
 int in2= 7;
 int enA = 5;
 int pos = 0;
int buttonState = 0;
Servo myservo;

void setup()
{
 
  // Debugging output
  Serial.begin(115200);
  // set up the LCD's number of rows and columns:
  myservo.attach(10);
  Serial.println("Ready...");
  pinMode(buttonCONFIRM,INPUT);
  pinMode(buttonCANCEL,INPUT);
  pinMode(in2,OUTPUT);
  pinMode(enA,OUTPUT);
  pinMode(in1,OUTPUT);
  //BUTTON
//  pinMode(ledPin, OUTPUT);
//  pinMode(buttonPin, INPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(notifLED, OUTPUT);
  pinMode(buttonCONFIRM, INPUT_PULLUP);
  pinMode(buttonCANCEL,INPUT_PULLUP);
  pinMode(COIN_PIN, INPUT);
  attachInterrupt(0, coinISR, RISING);  // COIN wire connected to D2;
}


// total amount of money collected;
float money = 0.0;

// gets incremented by the ISR;
// gets reset when coin was recognized (after train of pulses ends);
volatile int pulses = 0;
volatile long timeLastPulse = 0;


// executed for every pulse;
void coinISR()
{
  pulses++;
  timeLastPulse = millis();
}

    

void loop()
{
  //SERVO
  myservo.write(90);
  
  //BUTTON
  buttonState = digitalRead(buttonCONFIRM);
  
  //FREQUENCY CHECKER
  long timeFromLastPulse = millis() - timeLastPulse;
  
  //CONFIRM BUTTON
  
 
   
  //PULSE
  if (pulses > 0 && timeFromLastPulse > 1000)
  {
    // sequence of pulses stopped; determine the coin type;
    if ( pulses < 250)
    {
      Serial.print(pulses);
      Serial.println("lima ratus rupiah (5 pulses)");
      money += 500;
//      digitalWrite(LED,HIGH);
    }
    else if (pulses > 250)
    {
      Serial.print(pulses);
      Serial.println("seribu rupiah(10 pulses)");
      money += 1000;
//      digitalWrite(LED,HIGH);
    }
    else
    {
      Serial.print("Unknown coin: ");
      Serial.print(pulses);
      Serial.println(" pulses");
    }
    pulses = 0;
  }
  
//KELUARKAN KOIN
if (digitalRead(buttonCANCEL) == LOW) {
  Serial.println("CANCEL)");
  for (pos = 90 ; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
    }
    myservo.write(180);
    delay(1000);
    myservo.write(90);
    delay(1000);
     money = 0;
     buttonState = 0;
     digitalWrite(notifLED,LOW);
     Serial.println("NEXT...");
}
  else{
      digitalWrite(notifLED, LOW);
   }
  
//OPERASI MESIN SYARAT 2000 TERPENUHI
while (money >= 2000) {
  
digitalWrite(notifLED, HIGH);

//confirm
   if (digitalRead(buttonCONFIRM) == LOW) {
  Serial.println("CONFIRM");                
  digitalWrite(pinLed, HIGH);
}
  else{
      digitalWrite(pinLed, LOW);
   }
   
//cancel
   if (digitalRead(buttonCANCEL) == LOW) {
  Serial.println("CANCEL)");
  for (pos = 90 ; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
    }
    myservo.write(180);
    delay(1000);
    myservo.write(90);
    delay(1000);
     money = 0;
     buttonState = 0;
     digitalWrite(notifLED,LOW);
     Serial.println("NEXT...");
}
  else{
      digitalWrite(notifLED, HIGH);
   }

//JIKA CONFIRMASI  
    if (digitalRead(pinLed) == HIGH) {
        for( int i = 0; i<=3 ; i++){
     delay(500);
     analogWrite(enA,255);
     delay(1000);
     digitalWrite(in1,HIGH);
     //digitalWrite(LED,HIGH);
     delay(250);
     digitalWrite(in1,LOW);
     //digitalWrite(LED,LOW);
     delay(1000);
     }

     for (pos = 90 ; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
    }
    myservo.write(0);
    delay(1000);
    myservo.write(90);
    delay(1000);
     money = 0;
     buttonState = 0;
     Serial.println("NEXT...");
     digitalWrite(notifLED,LOW);
    }
    else{
     Serial.print("CANCEL");
    }
  }  
 }
