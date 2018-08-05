#ifdef ESP8266
extern "C" {
#include "user_interface.h"
}
#endif

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include <komaino-config.h>

ADC_MODE(ADC_VCC);

WiFiClientSecure client;

const char* host = "www.d-line.net";
String url = "/api/test";

void setup() {
  komaino.wifiSta(ssid, pass);
  komaino.print(komaino.wifiIP());
  String data = "text=Hello ESP8266!&bat=" + ESP.getVcc();
  komaino.print(httpsPost(url, data));
}

void loop() {

}

String httpsPost(String url, String data) {
  if (client.connect(host, 443)) {
    client.println("POST " + url + " HTTP/1.1");
    client.println("Host: " + (String)host);
    client.println("User-Agent: ESP8266/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded;");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);
    delay(10);
    String response = client.readString();
    int bodypos =  response.indexOf("\r\n\r\n") + 4;
    return response.substring(bodypos);
  }
  else {
    return "ERROR";
  }
}
