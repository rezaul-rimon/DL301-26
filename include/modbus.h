#pragma once

#include <Arduino.h>
#include <HardwareSerial.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

#define CONFIG_FILE "/config.json"

// ============================================================
// Shared globals
// ============================================================
extern HardwareSerial RS485;
extern JsonDocument  config;

// ============================================================
// Low-level helpers
// ============================================================
uint16_t modbusCRC(uint8_t *data, uint16_t length);
uint16_t parseAddress(const char *address);
uint32_t getSerialConfig(const char *parity, int dataBits, int stopBits);

// ============================================================
// RS485 direction
// ============================================================
void rs485TxMode();
void rs485RxMode();

// ============================================================
// Config
// ============================================================
bool loadConfig();

// ============================================================
// UART reconfiguration per sensor
// ============================================================
void configureRS485(JsonObject modbus);

// ============================================================
// Modbus read
// ============================================================
bool readRegisters(uint8_t slaveId,
                   uint8_t functionCode,
                   uint16_t address,
                   uint16_t quantity,
                   uint16_t *registers,
                   uint16_t timeout);

// ============================================================
// Decode raw registers -> float based on data_type / word_order / byte_swap
// ============================================================
bool decodeRegisters(const uint16_t *src,
                     uint16_t width,
                     const char *dataType,
                     const char *wordOrder,
                     bool byteSwap,
                     float &result);

// ============================================================
// Read a single channel (single-read mode)
// ============================================================
bool readChannel(JsonObject channel, JsonObject modbus, float &value);

// ============================================================
// High-level: read + print + publish one sensor
// (handles both single-read and batch-read modes)
// ============================================================
void readSensorAndPublish(JsonObject sensor);

// ============================================================
// High-level: read + publish all sensors
// ============================================================
void readAllModbusSensorsAndPublish();