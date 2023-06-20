# LED-Strip-Temperatur- und Feuchtigkeitsanzeige

Dieses Arduino-Projekt ermöglicht es, einen LED-Strip basierend auf der gemessenen Temperatur und Luftfeuchtigkeit zu verändern. Der LED-Strip fungiert also als Thermometer. Zusätzlich zeigt ein OLED-Display die aktuellen Werte an.

## Komponenten

- Arduino (z.B. Arduino Uno)
- Adafruit BME280 Sensor
- Analoger Temperatursensor
- Helligkeitssensor
- Adafruit Neopixel LED-Strip
- OLED-Display (SSD1306)
- Potentiometer

## Bibliotheken

Stellen Sie sicher, dass Sie die folgenden Bibliotheken installiert haben:

- Adafruit_NeoPixel
- Adafruit_Sensor
- Adafruit_BME280
- Adafruit_GFX
- Adafruit_SSD1306

## Schaltung

Schließen Sie die Komponenten wie folgt an den Arduino an:

- BME280-Sensor:
  - VIN an 3.3V
  - GND an GND
  - SDA an A4
  - SCL an A5
- Analoger Temperatursensor:
  - Einen Pol an A1
  - Den anderen an GND
- Potenziometer:
  - Plus Pol an 3.3V
  - Den anderen an A1
- Helligkeitssensor:
  - Eines der Beine an A0
  - Das andere Bein an 5V
- Neopixel LED-Strip:
  - DIN an Pin D4 (mit einem min. 440 Ω Widerstand)
  - 5V an 5V
  - GND an GND

## Anpassungen

- Überprüfen Sie die Werte der Grundeinstellungen im Code und passen Sie sie gegebenenfalls an Ihre Konfiguration an (z.B. Pin-Nummern, Anzahl der LEDs, I2C-Adresse des BME280-Sensors).
- Kalibrieren Sie den analogen Temperatursensor, indem Sie die gemessene Temperatur mit der Temperatur des digitalen Sensors vergleichen und den Poteziometer entsprechend anpassen.

## Verwendung

- Laden Sie den Code auf Ihren Arduino hoch.
- Schließen Sie den Arduino an Ihren Computer an.
- Öffnen Sie die serielle Monitorausgabe, um die Temperatur- und Feuchtigkeitswerte sowie die Helligkeitsdaten anzuzeigen.
- Die LED-Leiste wird basierend auf den gemessenen Werten gesteuert. Die Anzahl der leuchtenden LEDs wird entsprechend der Temperatur eingestellt, und die Farbe wird basierend auf der Luftfeuchtigkeit festgelegt.
- Die Helligkeit der LED-Leiste wird durch den Helligkeitssensor gesteuert.
- Die gemessene analoge Temperatur wird auf dem OLED-Display angezeigt.
