#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define TRIGGERPIN D1
#define ECHOPIN    D2
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "Z_fC2GbsucPz35ufcqEkZyVcDskzDHrQ";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Umar Ahamed";//your wifi name
char pass[] = "umar271271"; //your wifi password
int ledG = D5; // green led 
int ledR = D7; //red led 
WidgetLCD lcd(V1);

void setup() 
{
  pinMode(D5, OUTPUT);
  pinMode(D7, OUTPUT);
  // Debug console
  Serial.begin(9600);
pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(0, 0, "Distance in cm"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  // Please use timed events when LCD printintg in void loop to avoid sending too many commands
  // It will cause a FLOOD Error, and connection will be dropped
}

void loop()
{
  lcd.clear();
  lcd.print(0, 0, "Distance in cm"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  long duration, distance;
  digitalWrite(TRIGGERPIN, LOW);  
  delayMicroseconds(3); 
  
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12); 
  
  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println("Cm");
  lcd.print(7, 1, distance);
  Blynk.run();
  delay(1000);
  
  if ((2 <= distance  ) && (distance <= 6)){                                   
     Blynk.notify("Alert : Your car is parked just now");
     
      }
   if ((10 < distance) && (distance < 18 )){                                   
     Blynk.notify("Alert : Your car is  just leaved");
     Blynk.email("Security Alert", "Please Confirm that Your vehicle left from the <strong> parking lot</strong>.<br> If not immediately contact the city office");
      }
  if (distance <= 8){
    digitalWrite(D5 , LOW);
  }else{
    digitalWrite(D5, HIGH);
  }
  if (distance > 8){
    digitalWrite(D7 , LOW);
  }else{
    digitalWrite(D7, HIGH);
  }

}
