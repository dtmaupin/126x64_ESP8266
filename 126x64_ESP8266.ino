/* How to use the DHT-22 sensor with Arduino uno
   Temperature and humidity sensor
*/

//Libraries
#include <DHT.h>;

//Constants
#define DHTPIN 10     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
//Constants sensor 2
#define DHT2PIN 9     // what pin we're connected to
DHT dht2(DHT2PIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
float tempF; //Stores Temp in F value
float hum2; //Stores humidity 2 value
float temp2; //Stores temp2 value
float temp2F; //Stores temp2 F value

#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include "DHT.h"
int timeSinceLastRead = "0";
LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int show;

void setup()
{
  int error;

  Serial.begin(115200);
  dht.begin();
  Serial.println("LCD...");

  while (! Serial);

  Serial.println("Dose: check for LCD");

  // See http://playground.arduino.cc/Main/I2cScanner
  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);

  if (error == 0) {
    Serial.println(": LCD found.");

  } else {
    Serial.println(": LCD not found.");
  } // if

  lcd.begin(20, 4); // initialize the lcd
  show = 0;
} // setup()

void loop()
{
  if (show == 0) {
    if (timeSinceLastRead == 0 || timeSinceLastRead > 5000) {
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    tempF= dht.readTemperature(true);
    hum2 = dht2.readHumidity();
    temp2 = dht2.readTemperature();
    temp2F = dht2.readTemperature(true);
    lcd.noCursor();
    lcd.setBacklight(255);
    lcd.home(); lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidity: ");
    lcd.print(hum);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("Temp C: ");
    lcd.print(temp);
    lcd.print("'");
    lcd.setCursor(0, 2);
    lcd.print("Temp F: ");
    lcd.print(tempF);
    lcd.print("'");
    lcd.setCursor(0, 3);
    // Compute heat index in Fahrenheit (the default)
    float hif = dht.computeHeatIndex(tempF, hum);
    float hif2 = dht.computeHeatIndex(temp2F, hum);
    lcd.print("Heat Index F: ");
    lcd.print(hif);
    lcd.print("'");
 // End of sensor 1 output
    delay(5000); //Delay 1 second
//  Start of sensor 2 output
    lcd.home(); lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidity #2: ");
    lcd.print(hum2);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("Temp #2 C: ");
    lcd.print(temp2);
    lcd.print("'");
    lcd.setCursor(0, 2);
    lcd.print("Temp #2 F: ");
    lcd.print(temp2F);
    lcd.print("'");
    lcd.setCursor(0, 3);
    lcd.print("Heat Index F: ");
    lcd.print(hif2);
    lcd.print("'");
    //End of Sensor 2 Section
    
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.print(" Celsius, Temp: ");
    Serial.print(tempF);
    Serial.print(" Deg F, Heat Index:");
    Serial.print(hif);
    Serial.println(" Def F");
    Serial.print("Humidity2: ");
    Serial.print(hum2);
    Serial.print(" %, Temp2: ");
    Serial.print(temp2);
    Serial.print(" Celsius, Temp2: ");
    Serial.print(temp2F);
    Serial.print(" Deg F, Heat Index2:");
    Serial.print(hif2);
    Serial.println(" Def F");
    //lcd.setBacklight(255);
    timeSinceLastRead = 1;
    }
    else {
      delay(100); //delay 100 ms
      timeSinceLastRead += 100;
    }
    }
  }

