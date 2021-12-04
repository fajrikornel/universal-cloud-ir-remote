#if defined(ESP8266)
#define __ESP8266_MQTT__
#endif

#ifdef __ESP8266_MQTT__
#include <CloudIoTCore.h>
#include "esp8266_mqtt.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

#define EXCLUDE_EXOTIC_PROTOCOLS

#include <Arduino.h>
#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>

#undef DEBUG
#undef INFO

#if defined(APPLICATION_PIN)
#define DEBUG_BUTTON_PIN    APPLICATION_PIN // if low, print timing for each received data set
#else
#define DEBUG_BUTTON_PIN   6
#endif

#define LED_RECEIVE 2

void setup()
{
  pinMode(LED_RECEIVE, OUTPUT);
  digitalWrite(LED_RECEIVE, LOW);
  delay(1000);
  Serial.begin(115200);
  delay(1000);
  setupCloudIoT(); // Creates globals for MQTT
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(1000);

#if defined(_IR_MEASURE_TIMING) && defined(_IR_TIMING_TEST_PIN)
  pinMode(_IR_TIMING_TEST_PIN, OUTPUT);
#endif
  pinMode(DEBUG_BUTTON_PIN, INPUT_PULLUP);

  Serial.println(F("Enabling IR..."));
  delay(500);
  IrSender.begin(IR_SEND_PIN, DISABLE_LED_FEEDBACK);
  delay(500);
  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);

  digitalWrite(LED_BUILTIN, LOW);
}

static unsigned long lastRecord = 0;
static bool recording = false;
char buf_send[16] = {
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
};

static bool schedule_status[] = {false, false, false};
static unsigned long last_schedule[] = {0, 0, 0};
static unsigned long timeout_schedule[] = {0, 0, 0};
IRData schedule_code[3];

#include "functions.h"

void loop()
{
  if (!mqtt->loop())
  {
    delay(2000);
    mqtt->mqttConnect(false);
  }

  delay(10); // <- fixes some issues with WiFi stability
  
  record_loop();
  schedule_loop(0);
  schedule_loop(1);
  schedule_loop(2);
}
#endif