#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include "DHT.h"
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int DOUTpin1 = 8;
int limit1;
int value1;

const int DOUTpin2 = 9;
int limit2;
int value2;

#define buzzer 13

#define RLED 11
#define GLED 10

String readstringdata = "";

#define serial

void setup()
{
  Serial.begin(9600); // sets the baud rate

  dht.begin();

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  lcd.begin(16, 2);

  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  digitalWrite(RLED, LOW);
  digitalWrite(GLED, LOW);

  lcd.setCursor(0, 0);
  lcd.print("FoodSpoilageSyst");
  delay(2000);

  lcd.clear();
  delay(200);
}

void loop()
{
  readstringdata = "";

  /*..........GAS (MQ6)..........*/
  value1 = analogRead(A0);
  limit1 = digitalRead(DOUTpin1);

#ifdef serial
  Serial.print("MQ6 value: ");
  Serial.print(value1); // prints the alcohol value
  Serial.print("  Limit: ");
  Serial.println(limit1); /*prints the limit reached as either LOW or HIGH (above or underneath) */
#endif

  delay(200);

  /*..........GAS (MQ2)..........*/
  value2 = analogRead(A1);
  limit2 = digitalRead(DOUTpin2);

#ifdef serial
  Serial.print("MQ2 value: ");
  Serial.print(value2); // prints the alcohol value
  Serial.print("  Limit: ");
  Serial.println(limit2); /*prints the limit reached as either LOW or HIGH (above or underneath) */
#endif

  delay(200);

  lcd.setCursor(0, 1);
  lcd.print("MQ6:");
  lcd.print(value1);
  lcd.print(" MQ2:");
  lcd.print(value2);
  lcd.print("  ");

  delay(200);

  if ((limit1 == 0) || (limit2 == 0))
  {
    digitalWrite(GLED, LOW);
    digitalWrite(RLED, HIGH);

    digitalWrite(buzzer, HIGH);
    delay(500);
  }
  else
  {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, HIGH);

    digitalWrite(buzzer, LOW);
    delay(200);
  }

  /*..........DHT11 TEMPERATURE AND HUMIDITY SENSOR..........*/
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f))
  {
#ifdef serial
    Serial.println("Failed to read from DHT sensor!");
#endif
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

#ifdef serial
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
#endif

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(t, 0);
  lcd.print("dC  ");
  lcd.print(" H:");
  lcd.print(h, 0);
  lcd.print("%");
  lcd.print("  ");

  delay(200);

  readstringdata += String(h);
  readstringdata += String(",");
  readstringdata += String(t);
  readstringdata += String(",");
  readstringdata += String(value1); // mq6
  readstringdata += String(",");
  readstringdata += String(value2); // mq2
  readstringdata += String('#');
  Serial.println(readstringdata);
  delay(500);

#ifdef serial
  Serial.println("******************************************************");
  Serial.println("         ");
#endif

  readstringdata = "";
  delay(5000);
}