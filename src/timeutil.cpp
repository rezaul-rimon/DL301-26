#include "timeutil.h"

String getTimestamp14() {
    // ============================================================
    // PLACEHOLDER — uses uptime since boot
    // Replace this whole block once you have an RTC or NTP
    // ============================================================
    uint32_t secs = millis() / 1000;

    // Distribute seconds into fake date fields just to look plausible
    // (only temporary until real time source is added)
    uint32_t days  = secs / 86400;
    uint32_t hours = (secs / 3600) % 24;
    uint32_t mins  = (secs / 60) % 60;
    uint32_t s     = secs % 60;

    char buf[16];
    snprintf(buf, sizeof(buf), "0000%02lu%02lu%02lu%02lu",
             (unsigned long)(days % 100),
             (unsigned long)hours,
             (unsigned long)mins,
             (unsigned long)s);
    return String(buf);

    // ============================================================
    // WHEN YOU ADD AN RTC (DS3231 / PCF8523 etc.):
    // ============================================================
    // DateTime now = rtc.now();
    // char buf[16];
    // snprintf(buf, sizeof(buf), "%02d%02d%02d%02d%02d%02d",
    //          now.year() % 100, now.month(), now.day(),
    //          now.hour(), now.minute(), now.second());
    // return String(buf);
}

bool getAOS() {
    // ============================================================
    // REPLACE this with your real AOS source
    // ============================================================
    // Examples:
    //   return deviceArmed;
    //   return gpsFixValid;
    //   return (digitalRead(ACLINE_PIN) == HIGH);
    return false;   // placeholder
}