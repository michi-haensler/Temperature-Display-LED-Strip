#include <Adafruit_NeoPixel.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define LED_PIN 4        // Pin für den LED-Strip
#define NUM_LEDS 45      // Anzahl der LEDs im Strip
#define BME_ADDR 0x76    // I2C-Adresse des BME280-Sensors
#define BRIGHTNESS 255   // Helligkeit (0 - 255)
#define BRIGHTNESS_SENSOR_PIN A0  // Pin für den Helligkeitssensor
#define BLINK 28         // Gibt ab welcher Temperatur der LED Strip Blinkt
#define DELAY 200   // Pause bis zur nächsten Messung / Durchführung in ms

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_BME280 bme;
uint8_t brightness = BRIGHTNESS;  // Helligkeit (0-255)
bool blink = false;  // Blink-Flag

void setup() {
  strip.begin();
  strip.show();  // Alle LEDs ausschalten beim Start
  Serial.begin(9600);

  if (!bme.begin(BME_ADDR)) {
    Serial.println("Fehler beim Initialisieren des BME280-Sensors!");
    while (1);
  }
}

void loop() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();

  // Anzahl der leuchtenden LEDs basierend auf der Temperatur berechnen
  int numLEDs = map(temperature, 15, 40, 0, NUM_LEDS);
  numLEDs = constrain(numLEDs, 0, NUM_LEDS);

  // Farbe basierend auf der Luftfeuchtigkeit festlegen
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;
  if (humidity > 60) {
    red = 255;     // Rot bei Luftfeuchtigkeit über 60%
  } else if (humidity >= 20 && humidity <= 60) {
    green = 255;   // Grün bei Luftfeuchtigkeit zwischen 20% und 60%
  } else {
    blue = 255;    // Blau bei Luftfeuchtigkeit unter 20%
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
  if (temperature >= BLINK) {
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

  // Temperatur und Luftfeuchtigkeit ausgeben
  Serial.print("Temperatur: ");
  Serial.print(temperature);
  Serial.print(" °C, Luftfeuchtigkeit: ");
  Serial.print(humidity);
  Serial.print(" %");
  Serial.print(", Helligkeit: ");
  Serial.print(light_sensor_value);
  Serial.println("");

  delay(DELAY);
}