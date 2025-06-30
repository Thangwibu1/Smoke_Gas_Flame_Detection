#include <Arduino.h>
#include <WiFi.h>
#include <Math.h>
// Blynk library for ESP32

#define BLYNK_TEMPLATE_ID "TMPL6kaLmF0Ic"
#define BLYNK_TEMPLATE_NAME "Test"
#define BLYNK_AUTH_TOKEN "tpGbf7IkKqeGMBbI2zRqmVmcaiFCqH8x"

#include <TimeLib.h>
#include <BlynkSimpleEsp32.h>


char ssid[] = "3000 TEA - NGOGIATU"; // Replace with your WiFi SSID
char pass[] = "0827110100";

int LEDAlert = 2;
int LEDWarning = 4;
int Sensor = 32;
int Flame = 33;
int relayPump = 26;
const int gasDefault = analogRead(Sensor);
BlynkTimer timer;

void sendSensor() {
  int sensorValue = analogRead(Sensor);
  int flameValue = analogRead(Flame);

  Blynk.virtualWrite(V1, sensorValue);
  Blynk.virtualWrite(V2, flameValue);

  if (Math.abs(sensorValue - gasDefault) > 100) { // Adjust threshold as needed
    digitalWrite(LEDWarning, HIGH);
    Blynk.logEvent("gas_leak","Gas leak detected!");
    Blynk.virtualWrite(V3, HIGH); // Check if gas leak detected
  } else {
    digitalWrite(LEDWarning, LOW);
  }
  if (flameValue > 1000) { // Adjust threshold for flame detection
    digitalWrite(LEDAlert, HIGH);
    Blynk.logEvent("flame_detected","Flame detected!");
    digitalWrite(relayPump, LOW); // Activate pump or alert system
    Blynk.virtualWrite(V2, HIGH); // Check if flame detected
    delay(5000); // Delay to prevent multiple triggers
  } else {
    digitalWrite(relayPump, HIGH); // Deactivate pump or alert system
    digitalWrite(LEDAlert, LOW);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LEDAlert, OUTPUT);
  pinMode(LEDWarning, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, sendSensor); // Set interval to 1 second
}

void loop() {
  Blynk.run();
  timer.run(); // Run the timer to check sensor values
}

