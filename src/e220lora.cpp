#include "e220LoRa.h"

E220LoRa::E220LoRa(HardwareSerial &serial, int pinM0, int pinM1, int pinAUX) {
  loraSerial = &serial;
  _m0 = pinM0;
  _m1 = pinM1;
  _aux = pinAUX;
}

void E220LoRa::begin(uint32_t baudRate) {
  pinMode(_m0, OUTPUT);
  pinMode(_m1, OUTPUT);
  pinMode(_aux, INPUT);
  loraSerial->begin(baudRate);
  setModeNormal();
}

void E220LoRa::setMode(bool m0, bool m1) {
  digitalWrite(_m0, m0);
  digitalWrite(_m1, m1);
  delay(40);
}

void E220LoRa::setModeNormal() {
  setMode(LOW, LOW);
}

void E220LoRa::setModeConfig() {
  setMode(HIGH, HIGH);
}

bool E220LoRa::waitAUX(uint16_t timeout) {
  unsigned long start = millis();
  while (!digitalRead(_aux)) {
    if (millis() - start > timeout) return false;
    delay(5);
  }
  return true;
}

bool E220LoRa::available() {
  return loraSerial->available();
}

String E220LoRa::readMessage() {
  return loraSerial->readStringUntil('\n');
}

void E220LoRa::sendMessage(const String &msg) {
  waitAUX();
  loraSerial->println(msg);
}
