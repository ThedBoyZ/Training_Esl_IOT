#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>

//---------Network Credentials
const char* ssid = "SSID";
const char* password = "Password";
const char* serverName = "http://maker.ifttt.com/trigger/ESP32_test/with/key/Enter you API key";

unsigned long lastTime = 0;
unsigned long timerDelay = 15000;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  // Random seed is a number used to initialize a pseudorandom number generator
  randomSeed(hallRead());
}  

void Loop()
    //Send an HTTP POST request after every 15 seconds
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status

  if(WiFi.status()== WL_CONNECTED){

  WiFiClient client;

  HTTPClient http;

  // Your Domain name with URL path or IP address with path

  http.begin(client, serverName);
  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  // Data to send with HTTP POST
  String httpRequestData = "value1=" + String(random(25)) + "&value2=" + String(random(25))+ "&value3=" + String(random(25));
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(httpRequestData);

  /*
  
  // If you need an HTTP request with a content type: application/json, use the following:
  
  http.addHeader("Content-Type", "application/json");
  
  // JSON data to send with HTTP POST
  
  String httpRequestData = "{\"value1\":\"" + String(random(40)) + "\",\"value2\":\"" + String(random(40)) + "\",\"value3\":\"" + String(random(40)) + "\"}";
  
  // Send HTTP POST request
  
  int httpResponseCode = http.POST(httpRequestData);
  
  */
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
  Serial.println("successfully conected to host");
  // Free resources
  http.end();
    }
   else
    {
    Serial.println("WiFi Disconnected");
    }
  lastTime = millis();
  }
}
