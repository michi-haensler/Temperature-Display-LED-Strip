# LED-Strip-Temperatur- und Feuchtigkeitsanzeige
Dieses Arduino-Projekt ermöglicht es, einen LED-Strip basierend auf der gemessenen Temperatur und Luftfeuchtigkeit zu verändern. Der LED-Strip fungiert also als Thermometer. Zusätzlich zeigt ein OLED-Display die aktuellen Werte an.

## Komponenten

- Arduino (z.B. Arduino Uno)
- BME280 Sensor
- Analoger Temperatursensor
- Helligkeitssensor
- Neopixel LED-Strip
- OLED-Display (SSD1306)
- Potentiometer

## Bibliotheken

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
  - SDA an SDA
  - SCL an SCL
- Analoger Temperatursensor:
  - Einen Pol an A1
  - Den anderen an GND
- Potenziometer:
  - Plus Pol an 3.3V
  - Den anderen an A1
- Helligkeitssensor:
  - Einen der Pole an A0
  - Den anderen an 5V
- Neopixel LED-Strip:
  - DIN an Pin D4 (mit einem min. 440 Ω Widerstand)
  - 5V an 5V
  - GND an GND
- OLED-Display (SSD1306):
  - VCC an 5V
  - GND an GND
  - SDA an SDA
  - SCL an SCL

## Anpassungen

- Überprüfen Sie die Werte der Grundeinstellungen im Code und passen Sie sie gegebenenfalls an Ihre Konfiguration an (z.B. Pin-Nummern, Anzahl der LEDs, I2C-Adresse des BME280-Sensors).
- Kalibrieren Sie den analogen Temperatursensor, indem Sie die gemessene Temperatur mit der Temperatur des digitalen Sensors vergleichen und den Poteziometer entsprechend anpassen.

## Verwendung
- Installieren sie die Arduino IDE
- Downloaden sie den Code und öffnen sie ihn in der IDE
- Schließen Sie den Arduino an Ihren Computer an.
- Laden Sie den Code auf Ihren Arduino hoch.
- Öffnen Sie die serielle Monitorausgabe, um die Temperatur- und Feuchtigkeitswerte sowie die Helligkeitsdaten anzuzeigen.
- Die LED-Leiste wird basierend auf den gemessenen Werten gesteuert. Die Anzahl der leuchtenden LEDs wird entsprechend der Temperatur eingestellt, und die Farbe wird basierend auf der Luftfeuchtigkeit und Temperatur festgelegt.
- Die Helligkeit der LED-Leiste wird durch den Helligkeitssensor gesteuert.
- Die gemessene analoge Temperatur wird auf dem OLED-Display angezeigt.

## Funktionen

- Thermometer
  - Je nach Temperatur verändert sich die anzahl der LEDs die eingeschalten sind (je wärmer, desto mehr leuchten und umgekehrt)
  - Je nach einstellung in der Map Funktion kann der max und der min Wert gezeigt werden (im gegeben Code: 15° C. = min & 40° C. = max) das heißt, dass der LED Strip z.B. maximal 40° C. anzeigen kann
- Farbwechsel:
  - der LED Strip wechselt je nach Temperatur und Luchftfeuchtigkeit seine Farbe (alle Werte können nach Bedarf geändert werden)
    - Blau: Wenn die Temperatur gleich oder unter 10° C. oder die Luftfeuchtigkeit gleich oder unter 20% ist
    - Grün: Wenn die Temperatur über 10° C. und unter 27° C. oder die Luftfeuchtigkeit über 20% und unter 60% ist
    - Gelb: Wenn die Temperatur gleich oder über 27° C. und unter 30° C. ist
    - Rot: Wenn die Temperatur gleich oder über 30° C. ist oder die Luftfeuchtigkeit gleich oder über 60% ist
- Blinken

  - Je nach eingestelltem Wert (ab 30° im gegebenen Code) fängt der LED Strip an zu blinken um auf sich aufmerksam zu machen
  - Die Blinkfrequenz wird durch die `DELAY` Variable festgelegt

- Bildschirm
  - Auf dem Display werden die Luftfeuchtigkeit des BME280 und die Temperatur des Analogen Sensors angezeigt
  - Die `display.setRotation(0)` Funktion dreht das Display
    - 0 = Default
    - 2 = um 180° gedreht
- Helligkeit
  - Je nach Umgebungslicht ändert sich auch Automatisch die Helligkeit des LED Strips
    - der Helligkeitsensor nimmt in meinem Fall Helligkeit wie folgt wahr:
      - Je kleiner der Wert desto heller ist die Umgebung
      - Je größer der Wer desto dunkler ist die Umgebung
    - in den meisten Fällen ist das aber genau umgekehrt
    - um das anzupassen gibt es diese Methode `map(light_sensor_value, 0, 500, 255, 0)`
      - 0 bezieht sich auf das 255 (Wenn der Sensor 0 zurück gibt wird die maximale Helligkeit eingestellt)
      - 500 bezieht sich auf das 0 (Wenn der Sensor 0 zurück gibt wird die minimale Helligkeit eingeschtellt)
- Serial Monitor
  - Alle Werte werden im Serial Monitor ausgegeben
    - Analoger Temperatursensor (in °C.)
    - Digitaler Temperatursensor (in °C.)
    - Luftfeuchtigkeit (in %)
    - Helligkeit (Analoge Rohdaten)

### Wichtig:
  - Alle Temperatur Grenzen können mit den jeweiligen Variablen vor den Codeblöcken verändert werden    

