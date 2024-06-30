#include <SoftwareSerial.h>

int RainSensor = 11;
int Sms = 0;
SoftwareSerial sim800l(9, 10);

void setup() {
  Serial.begin(9600);
  sim800l.begin(9600);

  pinMode(RainSensor, INPUT);
}

void loop() {
  if (digitalRead(RainSensor) == LOW && Sms == 0) {
    Serial.println("There is Rain");
    sim800l.println("AT+CMGF=1");  // Configuring TEXT mode
    updateSerial();
    sim800l.println("AT+CMGS=\"+254748613509\"");  //change ZZ with country code and xxxxxxxxxxx with phone number to sms
    updateSerial();
    sim800l.println("ALERT: RAIN DETECTED");  //text content
    sim800l.write(26);
    delay(2000);
    Sms = 1;
  } else {
    Serial.println("No Rain");
    delay(1000);
    Sms = 0;
  }
}
void updateSerial() {
  delay(500);
  while (Serial.available()) {
    sim800l.write(Serial.read());  //Forward what Serial received to Software Serial Port
  }
  while (sim800l.available()) {
    Serial.write(sim800l.read());  //Forward what Software Serial received to Serial Port
  }
}
