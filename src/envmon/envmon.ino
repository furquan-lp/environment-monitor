#include <WiFi.h>
#include <WebServer.h>
#include "sensors.h"
#include "envmon.h"

WebServer server(80);

// HTML & CSS
String HTML = String(interstitial[0]);

void setup() {
  init_DHT();
    Serial.begin(115200);
    Serial.println("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected successfully");
    Serial.print("Got IP: ");
    Serial.println(WiFi.localIP());

    handle_Strings();
    delay(100);
    server.on("/", handle_root);
    server.begin();
    Serial.println("HTTP server started");
    delay(100); 
}

void loop() {
    handle_Strings();
    delay(100);
    server.handleClient();
    delay(1000);
}

// Handle root url (/)
void handle_root() {
    server.send(200, "text/html", HTML);
}

// ** Also handles sensor data
void handle_Strings() {
    String str1 = interstitial[0];
    str1.concat(get_temp());
    str1.concat(interstitial[1]);
    str1.concat(get_humid());
    str1.concat(interstitial[2]);
    HTML = String(str1);
}
