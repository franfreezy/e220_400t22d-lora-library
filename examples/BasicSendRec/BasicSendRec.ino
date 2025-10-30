#include <e220LoRa.h>

HardwareSerial LoRaSerial(2); //uses rx2,tx2 on esp32
E220LoRa lora(LoRaSerial, 14, 12, 35); // M0, M1, AUX pins

void setup() {
  Serial.begin(115200);
  lora.begin(9600);
  Serial.println("E220LoRa Example sketch");
}

void loop() {
  if (lora.available()) {
    String msg = lora.readMessage();
    Serial.print("Received: ");
    Serial.println(msg);
  }

  static unsigned long last = 0;
  if (millis() - last > 3000) {
    last = millis();
    lora.sendMessage("Hello from E220!");
    Serial.println("Sent message.");
  }
}
