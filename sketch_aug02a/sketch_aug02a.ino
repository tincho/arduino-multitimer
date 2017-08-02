#include <dht.h>
#define dht_dpin A1 // using analog pin 1
dht DHT;

#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define RELAY1  3

void setup(){
  pinMode(RELAY1, OUTPUT);
  digitalWrite(RELAY1,HIGH);

  Serial.begin(9600);
  delay(300);//Let system settle

  lcd.begin(16, 2);
  
  Serial.println("Humidity and temperature\n\n");
  delay(700);//Wait rest of 1000ms recommended delay before
  //accessing sensor

  // init relay off
  
}//end "setup()"

void loop(){

  //digitalWrite(RELAY1, HIGH);

  //This is the "heart" of the program.
  DHT.read11(dht_dpin);
  Serial.print("Current humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature); 
  Serial.println("C  ");
  Serial.println(digitalRead(RELAY1));

  lcd.setCursor(0,0);
  lcd.print("T: ");
  lcd.print(DHT.temperature);
  lcd.print(" C ");
  lcd.setCursor(0,1); 
  lcd.print("H: "); 
  lcd.print(DHT.humidity);

  // turn on on high Humidity
  if (DHT.humidity > 60 && digitalRead(RELAY1) == HIGH) {
    digitalWrite(RELAY1, LOW);
  }
  // turn off
  if(DHT.humidity <= 60 && digitalRead(RELAY1) == LOW) {
    digitalWrite(RELAY1, HIGH);
  }

  delay(1400);//Don't try to access too frequently... in theory

}

