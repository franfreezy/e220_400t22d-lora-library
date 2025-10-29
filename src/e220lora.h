#ifndef e220_LORA_H
#define e220_LORA_H

#include <Arduino.h>
#include <HardwareSerial.h>

class E220LoRa {
public:
  E220LoRa(HardwareSerial &serial, int pinM0, int pinM1, int pinAUX);
  void begin(uint32_t baudRate = 9600);
  void setModeNormal();
  void setModeConfig();
  bool available();
  String readMessage();
  void sendMessage(const String &msg);
  bool waitAUX(uint16_t timeout = 1000);

private:
  HardwareSerial *loraSerial;
  int _m0, _m1, _aux;
  void setMode(bool m0, bool m1);
};

#endif
