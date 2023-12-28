#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
const char* ssid = "Bahattin";
const char* password = "64364134Ba";
const char* server = "api.thingspeak.com";
const String apiKey = "677CFEPLNIWGF02Q"; // Thingspeak API anahtarınızı buraya ekleyin
WiFiClient client;
void setup() {
    Serial.begin(9600);
    delay(100);

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
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() 
{
      if (Serial.available() > 0) 
      {
    String data = Serial.readStringUntil('\n');
    Serial.println(data);
      int mq7Value = data.substring(data.indexOf("MQ7 Değer: ") + 11, data.indexOf("\t MQ135 Değer: ")).toInt();
  int mq135Value = data.substring(data.indexOf("MQ135 Değer: ") + 13).toInt();

  // Ayrıştırılmış değerleri yazdırma
    sendToThingspeak(mq7Value, mq135Value);
      }

  delay(1000);
}





void sendToThingspeak(int mq7, int mq135) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        String url = "http://api.thingspeak.com/update?api_key=" + apiKey;
        url += "&field1=" + String(mq7);
        url += "&field2=" + String(mq135);

        Serial.print("Connecting to Thingspeak URL: ");
        Serial.println(url);

         http.begin(client, url); // HTTP isteği başlat

        int httpResponseCode = http.GET(); // GET isteği gönder

        if (httpResponseCode > 0) {
            String response = http.getString(); // Sunucudan gelen yanıtı al
            Serial.println("Response code: " + String(httpResponseCode));
            Serial.println("Response: " + response);
        } else {
            Serial.print("Error on sending data. Error code: ");
            Serial.println(httpResponseCode);
        }

        http.end(); // HTTP bağlantısını kapat
    } else {
        Serial.println("WiFi bağlantısı yok.");
    }
}