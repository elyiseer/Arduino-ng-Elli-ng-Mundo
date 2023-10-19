#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "EnterYourWifiSSID";
const char* password = "EnterWifiPassword";

ESP8266WebServer server(80);
const int ledPin1 = 4;  // Pin for the first LED (GPIO 2)
const int ledPin2 = 0;  // Pin for the second LED (GPIO 0)
const int ledPin3 = 2 ;  // Pin for the third LED (GPIO 4)

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Print the local IP address to the Serial Monitor
  Serial.println("Local IP: " + WiFi.localIP().toString());

  // Define server routes
  server.on("/get_data", HTTP_GET, handleGetData);

  // Start server
  server.begin();

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop() {
  // Handle client requests
  server.handleClient();

}

void handleGetData() {
  // Get the query parameter from the request
  String query1 = server.arg("led1State");
  String query2 = server.arg("led2State");
  String query3 = server.arg("led3State");

  // Process the query (replace with your logic)
  String response1;
  String response2;
  String response3;

  if (query1 == "1") {
    digitalWrite(ledPin1, HIGH);
    response1 = "LED1 turned ON";
  }
  else {
    digitalWrite(ledPin1, LOW);
    response1 = "LED1 turned OFF";
  }
  
  if (query2 == "1") {
    digitalWrite(ledPin2, HIGH);
    response2 = "LED2 turned ON";
  }
  else {
    digitalWrite(ledPin2, LOW);
    response2 = "LED2 turned OFF";
  }
  
  if (query3 == "1") {
    digitalWrite(ledPin3, HIGH);
    response3 = "LED3 turned ON";
  } else {
    digitalWrite(ledPin3, LOW);
    response3 = "LED3 turned OFF";
  }

  // Send the response to the client
  String response = response1 + "\n" + response2 + "\n" + response3;
  server.send(200, "text/plain", response);

}
