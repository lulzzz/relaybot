// relaybot
// Aeroponics relay control
// Mist on/off Timer functions -> 1 -12V solenoid valve
// Lights on/off Timer functions
// Nutes infusion pump
// PH infusion pump


//THIRD-PARTY LIBRARIES

#include <TimeLib.h>
#include <Wire.h>

// constants won’t change. They’re used here to set pin numbers:
const int relay1 = 6; // the number of the relay1 pin - tied to 12V water solenoid
const int relay2 = 7; // tied to lights
const int relay3 = 8;
const int relay4 = 9;
const int relay5 = 10;
const int relay6 = 11;
const int relay7 = 12;
const int relay8 = 13;

// variables
byte light = HIGH;
boolean switchlight=false;

void setup() {
  // initialize built-in LED
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize the relay1,2,3,4,5,6,7,8 pins as an output:
  pinMode(relay1, OUTPUT); // initialize relay with solenoid valve
  pinMode(relay2, OUTPUT); // initialize relay for lights
  //pinMode(relay3, OUTPUT);
  //pinMode(relay4, OUTPUT);
  //pinMode(relay5, OUTPUT);
  //pinMode(relay6, OUTPUT);
  //pinMode(relay7, OUTPUT);
  //pinMode(relay8, OUTPUT);
  Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial (USB) port to connect
  }
  // turn lights and Arduino's builtin LED on for a sec
  setSystemDate();
  digitalWrite(relay2, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);  //keep lights on for 2 seconds

  if ((hour() >= 6) && (hour() < 20)) {
    digitalWrite(relay2,HIGH); // turn lights on
    digitalWrite(LED_BUILTIN,LOW); // switch off built in LED
  }
  else {
    digitalWrite(relay2,LOW); // switch lights off
    digitalWrite(LED_BUILTIN,HIGH); // switch on built in LED
    
  }
}

void loop() {

//want lights on from 6AM to 8PM

  if ((hour() >= 6) && (hour() < 20)) {
    if ((light=LOW)) {
      // Lights should be ON
      switchlight=true;
      light=HIGH;
      }
    }
  else {
    if ((light=HIGH)) { 
      // Lights should be OFF
      switchlight=true; 
      light=LOW;     
      }
   }

   if (switchlight) {
      digitalWrite(relay2,light); // switch lights
      digitalWrite(LED_BUILTIN,!light); // switch built in LED
      switchlight=false;
   }
   
  //misting thread 30 seconds on, 5 minutes off
  //Serial.println("turn on misters - relay pin 1");
  digitalWrite(relay1, HIGH); //turn on misting
  delay(30000); // spray for 30 seconds
  //Serial.println("turn off misters - relay pin 1");
  digitalWrite(relay1, LOW); // turn off misting
  delay(300000); // leave off for 5 minutes

 // /*   // display system time 
//  Serial.print(hour());
//  printDigits(minute());
//  printDigits(second());
//  Serial.println();
//  Serial.print(day());
//  printDigits(month());
//  printDigits(year());
//  Serial.println(); 
// */

}

void setSystemDate() {

int inChar = "";
String timeString = "";    // string to hold input
int hours, minutes, seconds, days, months, years;  // for the results

    // request date/time:
  Serial.println("What time is it?");
//  Serial.println("date +%H:%M:%S:%d:%m:%Y");
//from python script -> print (time.strftime("%H:%M:%S:%d:%m:%Y"))
// get the result of the date process (should be hours:minutes:seconds:day:month:year):
 while (inChar != '\n') {
   while ((Serial.available() > 0)) {
      inChar = Serial.read();
      timeString += (char)inChar;
    }
    }
  Serial.println(timeString);
      // find the colons:
    int firstColon = timeString.indexOf(":");
    int secondColon = timeString.indexOf(":",firstColon+1);
    int thirdColon = timeString.indexOf(":",secondColon+1);
    int fourthColon = timeString.indexOf(":",thirdColon+1);
    int fifthColon = timeString.lastIndexOf(":");
    // get the substrings for each date value hour, minute second:
    String hourString = timeString.substring(0, firstColon);
    String minString = timeString.substring(firstColon + 1, secondColon);
    String secString = timeString.substring(secondColon + 1);
    String dayString = timeString.substring(thirdColon + 1);
    String monthString = timeString.substring(fourthColon + 1);
    String yearString = timeString.substring(fifthColon + 1);

    // convert to ints
    hours = hourString.toInt();
    minutes = minString.toInt();
    seconds = secString.toInt();
    days = dayString.toInt();
    months = monthString.toInt();
    years = yearString.toInt();
    //setTime(hr,min,sec,day,mnth,yr);
    setTime(hours,minutes,seconds,days,months,years);
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

