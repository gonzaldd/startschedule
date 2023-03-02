#include "WiFi.h"
#include "schedule.h"
#include "config.h"

//WIFI credentials from config.h
const char* ssid =  WIFI_SSID;
const char* password = WIFI_PASS;

//Time server
const char* ntpServer = "time.google.com";
const char* ntpServer2 = "pool.ntp.org";

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println('.');
    delay(3000);
  }

  if (IS_DEV) Serial.println(WiFi.localIP());
}

tm getTime() {
  struct tm timeInfo;

  if (!getLocalTime(&timeInfo)) {
    Serial.println("Could not obtain time info");
    return timeInfo;
  }

  if (IS_DEV) {
    Serial.println("\n---------TIME----------");
    Serial.println(asctime(&timeInfo));
  }

  return timeInfo;
}

void setup() {
  pinMode(PIN_TO_ENGINE, OUTPUT);
  Serial.begin(115200);

  initWiFi();
  delay(5000);
  configTime(-3 * 3600, 3600, ntpServer, ntpServer2);
}

void loop() {
  // Get the current time
  tm now = getTime();
  bool isOn = false;
  int i = 0;

  // Check if the current time falls within any of the ignition schedules
  do {
    int now_hour = now.tm_hour;
    int now_min = now.tm_min;

    if (IS_DEV) {
      char buffer[40];

      sprintf(buffer, "Timer %d", i);
      Serial.println(buffer);
      sprintf(buffer, "Time init: %d:%d", IGNITION_SCHEDULE[i].hour_init, IGNITION_SCHEDULE[i].min_init);
      Serial.println(buffer);
      sprintf(buffer, "Time end: %d:%d", IGNITION_SCHEDULE[i].hour_end, IGNITION_SCHEDULE[i].min_end);
      Serial.println(buffer);
      Serial.println("---------");
    }

    // Check if current time is within the current ignition schedule
    if ((now_hour >= IGNITION_SCHEDULE[i].hour_init && now_min >= IGNITION_SCHEDULE[i].min_init) &&
        (now_hour <= IGNITION_SCHEDULE[i].hour_end && now_min < IGNITION_SCHEDULE[i].min_end)
       ) {

      // Turn on the LED if it's currently off
      if (digitalRead(PIN_TO_ENGINE) == LOW) digitalWrite(PIN_TO_ENGINE, HIGH);
      isOn = true;
      
    } else {
      // Turn off the LED if it's currently on
      if (digitalRead(PIN_TO_ENGINE) == HIGH) digitalWrite(PIN_TO_ENGINE, LOW);      
    }

    i++;
  } while (i < 3 && !isOn);

  // Wait for 5 seconds before checking the ignition schedule again
  delay(5000);
}
