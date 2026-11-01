/*
 * ============================================================================
 * Project: Smart Smoke and Fire Detection Alarm System
 * Author: Ritesh Kulakarni
 * Platform: Arduino Uno R3 (ATmega328P)
 * Description: Real-time environmental monitoring system using MQ-3 gas sensor,
 *              DHT11 temperature & humidity sensor, 16x2 LCD display, and
 *              piezo buzzer alarm to detect fire and smoke hazards.
 * ============================================================================
 */

#include <LiquidCrystal.h>
#include <DHT.h>

// ----------------------------------------------------------------------------
// Pin Configurations
// ----------------------------------------------------------------------------
#define DHTPIN 2            // Digital pin connected to DHT11 data pin
#define DHTTYPE DHT11       // Sensor model DHT 11

const int buzzerPin = 8;    // Digital pin connected to Piezo Buzzer (+)
const int mq3Pin = A0;      // Analog pin connected to MQ-3 Gas Sensor (AO)

// 16x2 LCD in 4-bit mode: LiquidCrystal(rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// ----------------------------------------------------------------------------
// Safety Thresholds
// ----------------------------------------------------------------------------
const int GAS_THRESHOLD = 200;       // MQ-3 analog threshold (smoke/combustible gas)
const float TEMP_THRESHOLD = 35.0;   // Temperature threshold in Celsius (°C)
const float HUMIDITY_THRESHOLD = 80.0;// Relative humidity threshold (%)

// ----------------------------------------------------------------------------
// Setup Routine
// ----------------------------------------------------------------------------
void setup() {
  // Initialize buzzer as output
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  // Initialize 16x2 LCD
  lcd.begin(16, 2);

  // Initialize DHT11 sensor
  dht.begin();

  // Welcome / initialization splash screen
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Health");
  lcd.setCursor(0, 1);
  lcd.print("& Safety Init...");
  delay(2000);
  lcd.clear();
}

// ----------------------------------------------------------------------------
// Main Loop Routine
// ----------------------------------------------------------------------------
void loop() {
  // Read sensor values
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int mq3Value = analogRead(mq3Pin);

  // Sensor reading validation check
  if (isnan(temp) || isnan(hum)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error");
    lcd.setCursor(0, 1);
    lcd.print("Check Wiring!");
    delay(2000);
    return;
  }

  // Display real-time readings on LCD
  // Line 1: Temperature & Humidity
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp, 1);
  lcd.print("C ");
  lcd.print("H:");
  lcd.print(hum, 0);
  lcd.print("%");

  // Line 2: Analog Gas Concentration
  lcd.setCursor(0, 1);
  lcd.print("Gas:");
  lcd.print(mq3Value);

  // Evaluate Hazard Conditions
  if (mq3Value > GAS_THRESHOLD || temp > TEMP_THRESHOLD || hum > HUMIDITY_THRESHOLD) {
    // --------------------------------------------------------
    // ALERT STATE: Hazard detected
    // --------------------------------------------------------
    digitalWrite(buzzerPin, HIGH);  // Activate audible buzzer

    lcd.clear();
    lcd.setCursor(0, 0);

    // Prioritized warning display
    if (temp > TEMP_THRESHOLD) {
      lcd.print("Fire Detected!");
    } else if (mq3Value > GAS_THRESHOLD) {
      lcd.print("Smoke Detected");
    } else if (hum > HUMIDITY_THRESHOLD) {
      lcd.print("High Humidity!");
    }

    // Secondary line with exact trigger measurements
    lcd.setCursor(0, 1);
    lcd.print("T:");
    lcd.print(temp, 1);
    lcd.print(" H:");
    lcd.print(hum, 0);

    // Keep alert visible and sound buzzer
    delay(3000);
  } else {
    // --------------------------------------------------------
    // NORMAL STATE: Safe environmental conditions
    // --------------------------------------------------------
    digitalWrite(buzzerPin, LOW);   // Deactivate buzzer
    delay(1000);                    // Sampling interval
  }
}
