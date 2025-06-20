#include <Arduino.h>
#include <WiFi.h>

#define BLYNK_TEMPLATE_ID "TMPL6kaLmF0Ic"
#define BLYNK_TEMPLATE_NAME "Test"
#define BLYNK_AUTH_TOKEN "tpGbf7IkKqeGMBbI2zRqmVmcaiFCqH8x"

#include <TimeLib.h>
#include <BlynkSimpleEsp32.h>


char ssid[] = "3000 TEA - NGOGIATU"; // Replace with your WiFi SSID
char pass[] = "0827110100";

int LED = 2;
int Sensor = 32;
int Flame = 33;
BlynkTimer timer;

void sendSensor() {
  int sensorValue = analogRead(Sensor);
  int flameValue = analogRead(Flame);
  
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  Serial.print("Flame Value: ");
  Serial.println(flameValue);
  Blynk.virtualWrite(V1, sensorValue);
  Blynk.virtualWrite(V2, flameValue);
  if (sensorValue > 2000 || flameValue < 1000) {
    digitalWrite(LED, HIGH);
    Serial.println("Warning: Sensor or Flame Detected!");
    Blynk.virtualWrite(V0, HIGH);
    digitalWrite(LED, HIGH);
    Blynk.logEvent("Warning: Sensor or Flame Detected!");
  } else {
    digitalWrite(LED, LOW);
    Serial.println("No Warning: Sensor and Flame Normal.");
    Blynk.virtualWrite(V0, LOW);
    Blynk.logEvent("No Warning: Sensor and Flame Normal.");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, sendSensor); // Set interval to 1 second
}

void loop() {
  Blynk.run();
  timer.run(); // Run the timer to check sensor values
}

