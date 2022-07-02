//By: SAKSHAM KAUSHIK

#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "NSUT-Campus"
#define WIFI_PASSWORD ""

// Insert Firebase project API Key
#define API_KEY "AIzaSyDvmvxlFIB-cmHO5LSvvRAIhUkcO8AScJ4"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "test10-e8f72-default-rtdb.firebaseio.com" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int intValue1;
int intValue2;
int intValue3;
bool signupOK = false;
int sliderValue1 = 0;
const int freq = 5000;
const int ledChannel1 = 0;
const int ledChannel2 = 2;
const int ledChannel3 = 4;
const int resolution = 8;

void setup() {
  Serial.begin(115200);
ledcSetup(ledChannel1, freq, resolution);
ledcAttachPin(23, ledChannel1);
ledcSetup(ledChannel1, freq, resolution);
ledcAttachPin(22, ledChannel2);
ledcSetup(ledChannel1, freq, resolution);
ledcAttachPin(21, ledChannel3);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready()) {

    int red = intValue1;
    int blue = intValue3;
    int green = intValue2;
do{       
    red = intValue1;
if (Firebase.RTDB.get(&fbdo, "/folder/test1")) {
 if (fbdo.dataType() == "int") {
        intValue1 = fbdo.intData();
        ledcWrite(ledChannel1, intValue1);
        //Serial.println(intValue1);
      }
       
}
}while(red!=intValue1);

do{
   green = intValue2;
if (Firebase.RTDB.get(&fbdo, "/folder/test2")) {
 if (fbdo.dataType() == "int") {
        intValue2 = fbdo.intData();
        ledcWrite(ledChannel2, intValue2);
        //Serial.println(intValue2);
      }
       
}}while(green!=intValue2);

do{
  blue = intValue3;
if (Firebase.RTDB.get(&fbdo, "/folder/test3")) {
 if (fbdo.dataType() == "int") {
        intValue3 = fbdo.intData();
        ledcWrite(ledChannel3, intValue3);
       // Serial.println(intValue3);
      }
       
}}while(blue!=intValue3);

   
    }
  }
