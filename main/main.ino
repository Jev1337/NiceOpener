#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266WebServer.h>
#include "RF433send.h"
#include <ArduinoJson.h>
#define PIN_RFOUT 3

RfSend* tx_whatever;

const char* ssid = "";      //type your ssid
const char* password = "";  //type your password

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(PIN_RFOUT, OUTPUT);
  tx_whatever = rfsend_builder(
    RfSendEncoding::TRIBIT,
    PIN_RFOUT,
    RFSEND_DEFAULT_CONVENTION,  // Do we want to invert 0 and 1 bits? No.
    1,                          // Number of sendings
    nullptr,                    // No callback to keep/stop sending (if you want to send
                                // SO LONG AS a button is pressed, the function reading the
                                // button state is to be put here).
    18856,                      // initseq
    1436,                       // lo_prefix
    1532,                       // hi_prefix
    0,                          // first_lo_ign
    496,                        // lo_short
    980,                        // lo_long
    0,                          // hi_short (0 => take lo_short)
    0,                          // hi_long  (0 => take lo_long)
    1448,                       // lo_last
    18856,                      // sep
    52                          // nb_bits
  );

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  server.on("/", HTTP_GET, handleRoot);

  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void handleRoot() {
  if (server.hasArg("code1") || server.hasArg("code2")) {
    String payload = server.arg("code1");
    Serial.println(payload);
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    String decoded = doc["code"];
    byte data[7];
    byte dataalt1[7];
    byte dataalt2[7];
    byte dataalt3[7];
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    char* ptr = strtok(strdup(decoded.c_str()), " ");
    while (ptr != NULL) {
      data[i++] = strtol(ptr, NULL, 16);
      dataalt1[j++] = strtol(ptr, NULL, 16);
      dataalt2[k++] = strtol(ptr, NULL, 16);
      dataalt3[l++] = strtol(ptr, NULL, 16);
      ptr = strtok(NULL, " ");
    }
    if (server.hasArg("code1")) {
      dataalt1[1] -= 0x30;
      dataalt2[1] -= 0x20;
      dataalt3[1] -= 0x50;
    }
    if (server.hasArg("code2")) {
      dataalt1[1] += 0x30;
      dataalt2[1] += 0x20;
      dataalt3[1] -= 0x32;
    }

    Serial.println("===============DATA-SENT=============");
    for (int i = 0; i < sizeof(data); i++) {
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    for (int i = 0; i < sizeof(dataalt1); i++) {
      Serial.print(dataalt1[i], HEX);
      Serial.print(" ");
    }

    Serial.println();
    for (int i = 0; i < sizeof(dataalt2); i++) {
      Serial.print(dataalt2[i], HEX);
      Serial.print(" ");
    }

    Serial.println();
    for (int i = 0; i < sizeof(dataalt3); i++) {
      Serial.print(dataalt3[i], HEX);
      Serial.print(" ");
    }

    Serial.println();
    Serial.println("===============DATA-SENT=============");

    tx_whatever->send(sizeof(data), data);
    tx_whatever->send(sizeof(dataalt1), dataalt1);
    tx_whatever->send(sizeof(dataalt2), dataalt2);
    tx_whatever->send(sizeof(dataalt3), dataalt3);

    server.send(200, "text/plain", "recv");
  } else {
    server.send(400, "text/plain", "err");
  }
}


void loop() {
  server.handleClient();  // Handle incoming client requests
}
