#include <LiquidCrystal.h>
#include <dht.h>
#include <IRremote.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 53
#define RST_PIN 4
MFRC522 mfrc522(SS_PIN, RST_PIN);         

IRrecv irrecv(10);
decode_results results;
long lastPressTime=0;
int state = LOW;
LiquidCrystal lcd(31,30,37,35,34,32);

dht DHT;
#define DHT11_PIN 8

#define SLOW 16769055
#define FAST 16748655
#define ONE 16724175
#define TWO 16718055
#define THREE 16743045

int alarm;
int flag;
int buzzer = 46;//the pin of the active buzzer
float control=1.0;
int intensity=255;


int coolant=0;
int respin=A5;

const int forward = 7;

int MotorThres=0;
int motorSpeed=0;

int trigPin = 11;    // Trigger
int echoPin = 12;    // Echo
long duration, cm, inches;

void setup() {
  pinMode(forward,OUTPUT); 
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer,OUTPUT);
   
  irrecv.enableIRIn();
  pinMode(26,OUTPUT);
  analogWrite(26,120);
  lcd.begin(16,2);
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       

}

void loop() {
  //Card key set up
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  //Show UID 
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase(); 
  if (content.substring(1) == "3A DD D7 81") {
        flag =1;
       delay(1000);
  }
  
 
 if(content.substring(1) != "3A DD D7 81"){
    Serial.println(0);
    Serial.println(0);
    Serial.println(0);
    Serial.println(0);
    Serial.println(0);
    flag =0;
    int i;
    for(i=0;i<200;i++){
      digitalWrite(buzzer,HIGH);
      delay(1);//wait for 1ms
      digitalWrite(buzzer,LOW);
      delay(1);//wait for 1ms
    } 
    delay(1000);
  }
  while(flag){
      digitalWrite(trigPin, LOW);
      delayMicroseconds(5);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      pinMode(echoPin, INPUT);
      duration = pulseIn(echoPin, HIGH);
      //Convert time into a distance
      cm = (duration/2) / 29.1;     
      if (cm<=10){
        MotorThres=0;  
      }else if (cm<=30){
        MotorThres=100;
      }else if (cm<50){
        MotorThres=175;
      }else{
        MotorThres=250;
      }
      //Remote Control
       if (irrecv.decode(&results)){
        if (results.value==SLOW){
          if (control > 0 ){
            control = control - 0.1;
          }else {
            control = 0;}
         }
         else if (results.value==FAST){
          if (control <1){
            control = control + 0.1;
          }else{
            control =1;}  
          }
          else if(results.value==ONE){
            intensity=0;
          }else if(results.value==TWO){
            intensity=50;
          }else if(results.value==THREE){
            intensity=255;
          } 
        irrecv.resume();  
        }
        analogWrite(2,intensity);
        analogWrite(3,intensity);
        
        motorSpeed=MotorThres*control; 
        analogWrite(forward,motorSpeed);
          
        int chk = DHT.read11(DHT11_PIN);
        coolant=analogRead(respin);
        delay(50);
        if (coolant <=10 || DHT.temperature>=90){
          alarm=1; 
        }else {
          alarm=0;
        }
        if (alarm){
          int i;
          for(i=0;i<200;i++){
             digitalWrite(buzzer,HIGH);
             delay(1);//wait for 1ms
             digitalWrite(buzzer,LOW);
             delay(1);//wait for 1ms
          } 
        }
        Serial.print(cm);
        Serial.println();
        delay(50);
        Serial.print(DHT.temperature);
        Serial.println();
        delay(50); 
        Serial.print(coolant);
        Serial.println();
        delay(50); 
        Serial.print(motorSpeed);
        Serial.println();
        delay(50);
        Serial.print(intensity);
        Serial.println(); 
      
        lcd.setCursor(0,0);
        lcd.print(motorSpeed);
        lcd.setCursor(9,0);
        lcd.print(coolant);
        lcd.setCursor(0,1);
        lcd.print(DHT.temperature);
          
        delay(1000);
  } // end of while(flag)  
}// end of loop()
