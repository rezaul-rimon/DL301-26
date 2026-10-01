#pragma once

#include <Arduino.h>
#include <Preferences.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include <esp_task_wdt.h>

// ==================== Configuration ====================
#define HW_VERSION "DL301-26.0.1"
#define FW_VERSION "DL301-26.0.1"
#define OTA_DATE "260920"
//-------------------------------------------------------//

#define OTA 1  // Set to 1 for OTA mode, 0 for normal mode
#define WORK_PACKAGE "DL301"
#define DEVICE_TYPE "02"
#define DEVICE_CODE_UPLOAD_DATE "260929"
#define DEVICE_SERIAL_ID "0001"

#define UNIQUE_DEVICE_ID WORK_PACKAGE DEVICE_TYPE DEVICE_CODE_UPLOAD_DATE DEVICE_SERIAL_ID
//=========================================================================================//

// Global variable declarations (extern)
extern bool deviceArmed;

// Duplicate from gsm.h for global access
extern QueueHandle_t mqttPublishQueue;

extern String DEVICE_ID;
extern String MAC_FALLBACK_ID;

// Serial and SIM-A7670 pin config
#define SerialMon Serial
#define SerialAT Serial1
#define MODEM_TX 17
#define MODEM_RX 16
#define MODEM_PWR 15
#define ACLINE_PIN 34

#define ON HIGH
#define OFF LOW

// Timing Configuration (const variables are okay in header)
const unsigned long HEARTBEAT_INTERVAL = 5 * 60 * 1000UL;  // 5 minute
extern unsigned long lastHeartbeatTime;

const unsigned long DATA_INTERVAL = 5 * 60 * 1000UL;  // 5 minute
extern unsigned long lastDataTime;

const unsigned long MAIN_TASK_PRIORITY = 2;
const unsigned long GSM_ERROR_RETRY_DELAY = 10000UL;

extern unsigned long lastGsmErrorTime;
extern unsigned long buttonHoldStart;
extern bool buttonHolding;

// System State
extern volatile bool mqttConnected;
extern volatile bool gprsConnected;
extern volatile bool deviceOnline;
extern volatile bool otaInProgress;
extern volatile bool tasksSuspended;
extern bool modemWasInitialized;

// ==================== Global Variables ====================
// MQTT Topics (now dynamic, built at runtime with DEVICE_ID)
extern String MQTT_PUB;
extern String MQTT_SUB;

// Call this once, after DEVICE_ID has been assigned
void setupMQTTTopics();

struct MQTTMessage {
    char topic[96];
    char payload[1024];
    uint8_t retries;    // ← add this line
};

// Helper function prototype
String getMACDeviceID();

#define DEBUG_MODE true
#define DEBUG_PRINT(x)  if (DEBUG_MODE) { Serial.print(x); }
#define DEBUG_PRINTF(x) if (DEBUG_MODE) { Serial.printf(x); }
#define DEBUG_PRINTLN(x) if (DEBUG_MODE) { Serial.println(x); }