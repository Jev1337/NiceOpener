#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266WebServer.h>
#include "RF433send.h"
#include <Arduino_JSON.h>
#define PIN_RFOUT 3

RfSend *tx_whatever;
 
const char* ssid = "RT-AC1200_30_2G";//type your ssid
const char* password = "Jevro1337";//type your password
 
ESP8266WebServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
 pinMode(PIN_RFOUT, OUTPUT);
  tx_whatever = rfsend_builder(
        RfSendEncoding::TRIBIT,
        PIN_RFOUT,
        RFSEND_DEFAULT_CONVENTION,  // Do we want to invert 0 and 1 bits? No.
        1,       // Number of sendings
        nullptr, // No callback to keep/stop sending (if you want to send
                 // SO LONG AS a button is pressed, the function reading the
                 // button state is to be put here).
        18856, // initseq
        1436, // lo_prefix
        1532, // hi_prefix
        0, // first_lo_ign
        496, // lo_short
        980, // lo_long
        0, // hi_short (0 => take lo_short)
        0, // hi_long  (0 => take lo_long)
        1448, // lo_last
        18856, // sep
        52  // nb_bits
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
   
  // Define server routes
  server.on("/", HTTP_GET, handleRoot);

  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
    
}

void handleRoot() {
  std::unique_ptr<BearSSL::WiFiClientSecure>clientHTTPS(new BearSSL::WiFiClientSecure);

    // Ignore SSL certificate validation
    clientHTTPS->setInsecure();
    
    //create an HTTPClient instance
    HTTPClient https;

      if (https.begin(*clientHTTPS , "YOUR_API_URL")) {  // Use an API, or check readme for an alternative. Example response: {"code": "0x01 0x02 0x03 0x04 0x05 0x06 0x07"}
      // start connection and send HTTP header
      int httpCode = https.GET();
      // httpCode will be negative on error
      if (httpCode > 0) {
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);
          JSONVar Data = JSON.parse(payload);
          
          String decoded = Data["code"];
          byte data[7];
          byte dataalt1[7];
          byte dataalt2[7];
          byte dataalt3[7];
          int i = 0;
          int j = 0;
          int k= 0;
          int l = 0;
          char *ptr = strtok(strdup(decoded.c_str()), " ");
          while (ptr != NULL) {
             data[i++] = strtol(ptr, NULL, 16);
              dataalt1[j++] = strtol(ptr, NULL, 16);
             dataalt2[k++] = strtol(ptr, NULL, 16);
             dataalt3[l++] = strtol(ptr, NULL, 16);
             ptr = strtok(NULL, " ");
          }

          dataalt1[1] -= 0x30;
          dataalt2[1] -= 0x20;
          dataalt3[1] -= 0x50;
  
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

          //now we need to send the data and dataalt to the transmitter
          tx_whatever->send(sizeof(data), data);
          tx_whatever->send(sizeof(dataalt1), dataalt1);
          tx_whatever->send(sizeof(dataalt2), dataalt2);
          tx_whatever->send(sizeof(dataalt3), dataalt3);
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
    server.send(200, "text/html", "<!DOCTYPE HTML><html><body><h1 style='font-size: 10vw;margin-top:50%;text-align: center;display; block;'>Sent!<br><a href='javascript:window.location.reload(true)'>Request Again</a></h1></body></html>"); // Send a "Hello, World!" response
}
 
void loop() {
  server.handleClient(); // Handle incoming client requests
}
