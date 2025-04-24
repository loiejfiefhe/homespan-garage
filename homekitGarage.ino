#include "HomeSpan.h"
#include "DEV_GARAGE.h"

const int closedSensorPin = 21; // The status pin connected to the garage
const int openSensorPin = 36; // The status pin connected to the garage
const int relayPin = 35; // The relay pin that actually controls the garage

void setup()
{
    Serial.begin(115200);

    homeSpan.enableWebLog(100,"pool.ntp.org","UTC+10",""); //  enableWebLog(uint16_t maxEntries, const char *timeServerURL, const char *timeZone, const char *logURL)`
    homeSpan.setWifiCredentials("", "");  // Set your Wi-Fi credentials
    homeSpan.setPairingCode("92747402");                                  // pairing pin
    homeSpan.setControlPin(0);
    homeSpan.setStatusPin(15);
    homeSpan.setStatusAutoOff(10);

    homeSpan.enableOTA(); // Enable OTA updates

    homeSpan.begin(Category::GarageDoorOpeners, "front garage");
    new SpanAccessory();
        new Service::AccessoryInformation();
            new Characteristic::Identify();
            new Characteristic::Name("front garage");
            new Characteristic::Manufacturer("f.mcgr.gr/g/HSgarage");
            new Characteristic::Model("homespan-garage");
            new Characteristic::FirmwareRevision("1.0.0");
            new Characteristic::CurrentDoorState();
            new Characteristic::TargetDoorState();
            new Characteristic::ObstructionDetected();

        new DEV_GARAGE(closedSensorPin, openSensorPin, relayPin);
}

void loop()
{
    homeSpan.poll();
}
