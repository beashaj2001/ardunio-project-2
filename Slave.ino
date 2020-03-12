#include <SoftwareSerial.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(3,5,7,8,9,13);//Initializes LCD
SoftwareSerial BTSerial(10, 11); //RX|TX of bluetooth connected to arduino
int buzzerPin = 6; //Buzzer pin will connected to 6th pin of arduino
void setup()
{
  lcd.begin(16,2);
   pinMode(buzzerPin, OUTPUT);
  pinMode(9, OUTPUT);
   pinMode(2, OUTPUT);
   pinMode(4, OUTPUT); 
  pinMode(12, OUTPUT);
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400); 
}

void loop()
{

  if (BTSerial.available())
  {
    char c=BTSerial.read();//read data from slave bluetooth
    /////Object detection///////
    if(c=='1')//check if data is one
    {
       beep(20); //initialize buzzer with delay 20.
        lcd.setCursor(0,0);
lcd.print("ALERT!!!!!");//prints Alert in LCD first column
lcd.setCursor(0,1);
lcd.print("Intruder!!!!");prints intruder in LCD second column
      Serial.write(c);
      /////Blinks Red LED/////////////
       digitalWrite(12, HIGH);  
  delay(1000);                      
  digitalWrite(12, LOW);   
  delay(1000); 
  ////////////////
  //////Sends SMS via GSM module///////////
       Serial.print("\r");
    delay(1000);
    Serial.print("AT+CMGF=1\r");//set msg send mode
    delay(1000);
    Serial.print("AT+CMGS=\"+919182977648\"\r");//Number for msg transimissin
    delay(1000);
    //The text of the message to be sent.
    Serial.print("Alert!!! Object detected!!!");
    delay(1000);
    Serial.write(0x1A);
    delay(1000);
      
    }
    ///////////////////////
    ///////Temperature greater than max threshold(33 degree)///////
     if(c=='2')//check if data is two
    {
       beep1(20);//initialize buzzer with delay 20.
       lcd.setCursor(0,0);
lcd.print("Very hot");//prints Very hot in LCD first column
lcd.setCursor(0,1);
lcd.print("Switch on AC");//prints switch on AC in LCD second column
      Serial.write(c);
      ////Blink yellow LED////////
       digitalWrite(4, HIGH);   
  delay(1000);                      
  digitalWrite(4, LOW);   
  delay(1000); 
  //////////////////////////
  //////Sends SMS via GSM module///////////
       Serial.print("\r");
    delay(1000);
    Serial.print("AT+CMGF=1\r");//set msg send mode
    delay(1000);
    Serial.print("AT+CMGS=\"+919182977648\"\r");//Number for msg transimission
    delay(1000);
    Serial.print("Very hot!!! Switch on AC!!!");
    delay(1000);
    Serial.write(0x1A);
    delay(1000);
    }
    //////////////////////////////////
     ///////Temperature less than min threshold(16 degree)///////
     if(c=='3')//check data is 3
    {
       beep2(20);//initialize buzzer with delay 20.
        lcd.setCursor(0,0);
lcd.print("Very Cool");//prints Very cool in LCD first column
lcd.setCursor(0,1);
lcd.print("Switch off AC");//prints switch off AC in LCD second column
      Serial.write(c);
      ////////Blink green LED////////////
       digitalWrite(2, HIGH);   
  delay(1000);                      
  digitalWrite(2, LOW);   
  delay(1000); 
  /////////////////////////////////////
   //////Sends SMS via GSM module///////////
       Serial.print("\r");
    delay(1000);
    Serial.print("AT+CMGF=1\r");//set msg send mode
    delay(1000);
    Serial.print("AT+CMGS=\"+919182977648\"\r");;//Number for msg transimission
    delay(1000);
    delay(1000);
    Serial.print("Very cool!!!Switch OFF AC");
    delay(1000);
    Serial.write(0x1A);
    delay(1000);
      
    }
   ///////////////////////////////////
    analogWrite(buzzerPin, 0);//Keep buzzer low
    lcd.setCursor(0,0);
lcd.print("Processing...........");//print processing in LCD first column
lcd.setCursor(0,1);
lcd.print("You are safe!!!!");//print You are safe in LCD second column
  }
 ///Buzzer beep functions///
void beep(unsigned char delayms) { 
  analogWrite(buzzerPin, 5); 
  delay(delayms);
  analogWrite(buzzerPin ,10);
  delay(delayms); 
}
void beep1(unsigned char delayms) { 
  analogWrite(buzzerPin, 5);
  delay(delayms); 
  analogWrite(buzzerPin ,2);
  delay(delayms);
  Serial.print("hic");
}
void beep2(unsigned char delayms) { 
  analogWrite(buzzerPin, 7); 
  delay(delayms);
  analogWrite(buzzerPin ,9); 
  delay(delayms);
 Serial.print("hih");
}
