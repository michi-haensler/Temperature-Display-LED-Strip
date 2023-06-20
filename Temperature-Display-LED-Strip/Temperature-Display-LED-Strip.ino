// Librarys 
#include <Adafruit_NeoPixel.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Grundeinstellungen
#define LED_PIN 4        // Pin für den LED-Strip
#define NUM_LEDS 45      // Anzahl der LEDs im Strip
#define BME_ADDR 0x76    // I2C-Adresse des BME280-Sensors
#define BRIGHTNESS 255   // Helligkeit (0 - 255)
#define BRIGHTNESS_SENSOR_PIN A0  // Pin für den Helligkeitssensor
#define BLINK 30         // Gibt ab welcher Temperatur der LED Strip Blinkt
#define DELAY 200        // Pause bis zur nächsten Messung / Durchführung in ms

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_BME280 bme;
uint8_t brightness = BRIGHTNESS;  // Helligkeit (0-255)
bool blink = false;  // Blink-Flag

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Analoger Temperatursensor
const int TEMPERATURE_SENSOR_PIN = A1;
// Widerstand bei 25 °C (10 kΩ)
const float THERMISTOR_RESISTOR = 10000.0;
// Widerstandswert bei 25 °C für den Temperaturkoeffizienten
const float THERMISTOR_BETA = 3950.0;
// Nennwiderstand des Temperatursensors bei 25 °C
const float NOMINAL_RESISTANCE = 10000.0;
// Temperatur bei der der Nennwiderstand gemessen wurde (25 °C)
const float NOMINAL_TEMPERATURE = 25.0;

void setup() {
  strip.begin();
  strip.show();  // Alle LEDs ausschalten beim Start
  Serial.begin(9600);

  if (!bme.begin(BME_ADDR)) {
    Serial.println("Fehler beim Initialisieren des BME280-Sensors!");
    while (1);
  }

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setRotation(2);
}

void loop() {
  float bmeTemperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float analogTemperature = readAnalogTemperature();

  // Anzahl der leuchtenden LEDs basierend auf der Temperatur berechnen
  int numLEDs = map(analogTemperature, 15, 40, 0, NUM_LEDS);
  numLEDs = constrain(numLEDs, 0, NUM_LEDS);

  // Farbe basierend auf der Luftfeuchtigkeit festlegen
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;

  #define H_RED 60    // Gibt an wann der LED Strip Rot leuchtet, wenn z.B. die Luftfeuchtigkeit über 60% ist
  #define H_BLUE 20   // Gibt an wann der LED Strip Blau leuchtet, wenn z.B. die Luftfeuchtigkeit unter 20% ist

  if (humidity > H_RED) {
    red = 255;
    blue = 0;     // ROT
    green = 0;     
  } else if (humidity >= H_BLUE && humidity <= H_RED) {
    red = 0;
    blue = 0;     // GRÜN
    green = 255;  
  } else {
    red = 0;
    blue = 255;     // BLAU
    green = 0;
  }

  // Farbe basierend auf der Temperatur setzen
  #define T_RED 30 // Rot bei über oder gleich eingestelltem Wert
  #define T_YELLOW 27 // Gelb bei über oder gleich eingestelltem Wert
  
  if (analogTemperature >= T_RED) {
    red = 255;
    blue = 0;     // ROT
    green = 0;
  } else if (analogTemperature >= T_YELLOW && analogTemperature < T_RED) {
    red = 255;
    blue = 0;     // GELB
    green = 255;
  } else {
    red = 0;
    blue = 0;     // GRÜN
    green = 255;
  }

  // LEDs entsprechend der berechneten Anzahl und Farbe setzen
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < numLEDs) {
      strip.setPixelColor(i, strip.Color(red, green, blue));
    } else {
      strip.setPixelColor(i, 0);  // Ausschalten der restlichen LEDs
    }
  }

  // Helligkeitssteuerung
  int light_sensor_value = analogRead(BRIGHTNESS_SENSOR_PIN);
  brightness = map(light_sensor_value, 0, 500, 255, 0);
  strip.setBrightness(brightness);
  strip.show();

  // Blinken ab einer oben eingestellten Temperatur
   if (analogTemperature >= BLINK) {
    blink = !blink;  // Blink-Flag umschalten

    if (blink) {
      // LEDs einschalten
      for (int i = 0; i < numLEDs; i++) {
        strip.setPixelColor(i, strip.Color(red, green, blue));
      }
    } else {
      // LEDs ausschalten
      for (int i = 0; i < numLEDs; i++) {
        strip.setPixelColor(i, 0);
      }
    }

    strip.show();
  }

  // Temperatur und Luftfeuchtigkeit auf dem OLED-Display anzeigen
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Tem:");
  display.print(analogTemperature);
  display.print("C");
  display.print("Hum:");
  display.print(humidity);
  display.print("%");
  display.display();

  // Temperatur und Luftfeuchtigkeit ausgeben
  Serial.print("Temperatur (analog): ");   // Annaloger Temperatursensor
  Serial.print(analogTemperature);
  Serial.print(" °C, Temperatur (BME): "); // Digitaler Temperatursensor (dient zum Einstellen des Potenziomenters)
  Serial.print(bmeTemperature);
  Serial.print(" °C, Luftfeuchtigkeit: ");
  Serial.print(humidity);
  Serial.print(" %");
  Serial.print(", Helligkeit: ");
  Serial.print(light_sensor_value);
  Serial.println("");

  delay(DELAY);
}

float readAnalogTemperature() {

  int sensorValue = analogRead(TEMPERATURE_SENSOR_PIN);
  float resistance = THERMISTOR_RESISTOR / (1023.0 / sensorValue - 1.0);
  float steinhart = resistance / THERMISTOR_RESISTOR;
  steinhart = log(steinhart);
  steinhart /= THERMISTOR_BETA;
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);
  steinhart = 1.0 / steinhart;
  float temperature = steinhart - 273.15;
  return temperature;
}
