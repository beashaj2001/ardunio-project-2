#include <Wire.h>
#include "DHT.h"
//Humidity sensor pin 3
#define DHTPIN 3 
#define DHTTYPE DHT11
#include "RTClib.h"
#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11);  //RX|TX connection to Bluetooth
RTC_DS1307 rtc; 
 const int trigPin = 2;//Trigger pin of Ultrasonic sensor
const int echoPin = 8;//Echo pin of Ultrasonic sensor
char c = ' ';
String last="";
 long duration;
int distance,flag=0;
DHT dht(DHTPIN, DHTTYPE);//Humidity sensor initilization 
void setup() 
{
    Serial.begin(9600);
    dht.begin();
    Serial.println("Arduino is ready");
    Serial.println("Remember to select Both NL & CR in the serial monitor");
    pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
    BTserial.begin(38400);  
    //To Check RTC connection
    if (! rtc.begin()) 
  {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) 
  {
    Serial.print("RTC is NOT running!");
    return;
  }
  
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //rtc.adjust(DateTime(2020, 3, 10, 7, 36, 0));
  
}
 
void loop()
{
  DateTime now = rtc.now();
   float t = dht.readTemperature();//Temperature from humidity sensor
   Serial.print(t);
  String time=(String)now.hour()+":"+(String)now.minute()+":"+(String)now.second();//Current time from RTC
//Ultrasonic sensor
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
///////////////////////
distance= duration*0.034/2;//Distance in Cm using ultrasonic sensor
Serial.print("Distance: ");
Serial.println(distance);
if(distance<10)//if distance less than 10cm it sends signal to slave via bluetooth
{
 BTserial.write('1'); 
 last=time;//It stores the object deteced time
}
if(t>=33.00&&(now.hour()%2==0)&&flag==1)//if temperature is greater than 33 degree cel and if current hour is even numbered then its send msg to slave via bluetooth
{
   flag=0;//set flag to 0 for running only one time
   BTserial.write('2'); 
   Serial.println("hi");
}
if(now.hour()%2!=0)//setting flag if hour is odd numbered
{
  flag=1;
}
if(t<=16.00&&(now.hour()%2==0)&&flag==1)//if temperature is less than 16 degree cel and if current hour is even numbered then its send msg to slave via bluetooth
{
{
  flag=0;
   BTserial.write('3'); 
}
Serial.println("Object detected on "+last);
 delay(500);
}
