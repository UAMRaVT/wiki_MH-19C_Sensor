#include <Arduino.h>
#include <MHZ.h>
#include <SoftwareSerial.h>

// Define UART pins for MH-Z19C
#define MH_Z19_RX 4  // GPIO4 (D2) zelený káblik na D2
#define MH_Z19_TX 5  // GPIO5 (D1) modrý káblik na D1
#define PWM_PIN -1   // No PWM reading for UART mode

// Initialize SoftwareSerial and MHZ sensor instance
SoftwareSerial co2Serial(MH_Z19_RX, MH_Z19_TX);
MHZ co2Sensor(&co2Serial, PWM_PIN, MHZ::MHZ19C);  // Specify MH-Z19C model in the constructor

void setup() {
  Serial.begin(9600);
  co2Serial.begin(9600);

  Serial.println("Initializing MH-Z19C...");
  
  // Delay for preheating
  unsigned long preheatStart = millis();
  while (millis() - preheatStart < 160000) {
    Serial.print("."); 
    delay(5000);
  }
  Serial.println("\nSensor is ready.");
}

void loop() {
  // Reading CO₂ level through UART
  int co2Level = co2Sensor.readCO2UART();
  int temperature = co2Sensor.getLastTemperature();

  // Display results
  Serial.print("CO₂ Level: ");
  Serial.print(co2Level >= 0 ? String(co2Level) + " ppm" : "Error reading CO₂");

  Serial.print(" | Temperature: ");
  Serial.println(temperature > 0 ? String(temperature) + " °C" : "n/a");

  delay(120000);  // Measure every 2 minutes
}
