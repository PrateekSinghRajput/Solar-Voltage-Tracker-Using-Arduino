#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

const int lm35_pin = A6;
const int voltageSensor = A0;
float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;


float RLDR;
float Vout;
float Lux;


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("  Soler Energy  ");
  lcd.setCursor(0, 1);
  lcd.print("  Measurement   ");
  delay(2000);
  lcd.clear();
}

void loop() {
  int temp_adc_val;
  float temp_val;
  temp_adc_val = analogRead(lm35_pin);
  temp_val = (temp_adc_val * 2.88);
  temp_val = (temp_val / 10);
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp_val);
  Serial.print("Temperature = ");
  Serial.print(temp_val);
  Serial.print(" Degree Celsius\n");


  value = analogRead(voltageSensor);
  vOUT = (value * 5.0) / 1024.0;
  vIN = vOUT / (R2 / (R1 + R2));

  lcd.setCursor(0, 1);
  lcd.print("Solar Volt:");
  lcd.setCursor(12, 1);
  lcd.print(vIN);

  int sensorValue = analogRead(A5);
  Vout = (sensorValue * 0.0048828125);
  RLDR = (10000.0 * (5 - Vout)) / Vout;
  Lux = (RLDR / 500);
  lcd.setCursor(10, 0);
  lcd.print("L:");
  lcd.print(Lux);
  delay(1000);
}