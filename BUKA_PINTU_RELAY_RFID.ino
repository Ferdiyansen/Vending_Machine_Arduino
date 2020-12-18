#include <SPI.h>
#include <Servo.h>
#include <MFRC522.h>
int hall_sensor = 8;
int state,lockread;
int Buzzer = 6;
Servo serlock;
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  pinMode(LockPin, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(hall_sensor, INPUT);
  serlock.attach(7);
  serlock.write(90);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  //Serial.println("Approximate your card to the reader...");
  // Serial.println();
  digitalWrite(LockPin, LOW);
}
void readsensor()
{
 lockread = digitalRead(LockPin);
 state = digitalRead(hall_sensor);
 //Serial.print(lockread);
 //Serial.print(state);
 // delay(2000); 
}
void loop() 
{
  readsensor();
  sensor(); 
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor 
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {    
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  //Serial.println();
  //Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "B0 E6 48 3B" ) //change here the UID of the card/cards that you want to give access
  {   
    digitalWrite(LockPin, HIGH);
    Serial.print("Door Unlocked");
    digitalWrite(Buzzer, HIGH);
    delay(1000);
    digitalWrite(Buzzer, LOW);
    sensor();
    }
  else
  {
   Serial.println("You are not Authorised"); 
   digitalWrite(Buzzer, HIGH);
   delay(1000);
   digitalWrite(Buzzer, LOW);
  } 
}
void sensor()
{
 readsensor();
 if (lockread == HIGH){  
      readsensor();
      if(state==LOW){
      digitalWrite(LockPin, LOW);
      Serial.print("Door Closed");
      digitalWrite(Buzzer, HIGH);
      delay(2000);
      digitalWrite(Buzzer, LOW);
    }
  } 
 }
