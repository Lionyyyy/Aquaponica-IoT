/*
  ---------------------------------
  IMPORTANT: CONFIGURATION REQUIRED
  ---------------------------------
  
  Before running this code, make sure to check the "secrets.h" file
  for important configuration details such as WiFi credentials and 
  Firebase settings.

  The "secrets.h" file should include:
  - Your WiFi SSID and Password
  - Your Firebase Realtime Database URL
  - (OPTIONAL) Firebase Authentication Token

  Ensure that "secrets.h" is properly configured and includes the correct
  information for your project. Failure to do so may result in connection
  errors or incorrect behavior of your application.
*/

#include "secrets.h"
#include <Firebase.h>

/* Use the following instance for Test Mode (No Authentication) */
Firebase fb(REFERENCE_URL);

/* Use the following instance for Locked Mode (With Authentication) */
// Firebase fb(REFERENCE_URL, AUTH_TOKEN);

void setup() {
    Serial.begin(115200);
    
    // Board-specific initialization
    #if !defined(ARDUINO_UNOWIFIR4)
        WiFi.mode(WIFI_STA);
    #else
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, LOW);
    #endif
    
    WiFi.disconnect();
    delay(1000);

    /* Connect to WiFi */
    Serial.println();
    Serial.println();
    Serial.print("Connecting to: ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print("-");
        delay(1000);
    }

    Serial.println();
    Serial.println("WiFi Connected");
    Serial.println();

    // Turn on built-in LED for UNO R4 WiFi
    #if defined(ARDUINO_UNOWIFIR4)
        digitalWrite(LED_BUILTIN, HIGH);
    #endif

    /* ===== SETTING DATA IN FIREBASE ===== */
    
    Serial.println("Setting data in Firebase...");
    
    /*
      Set String, Int, Float, or Bool in Firebase
      
      Parameters:
        - path: The path in Firebase where the data will be stored
        - data: The value to set (String, Int, Float, or Bool)

      Returns:
        - HTTP response code as an integer
          - 200: Success
          - 400: Bad Request
          - 401: Unauthorized
          - 403: Forbidden
          - 404: Not Found
          - Other codes indicate various errors
    */
    
    int responseCode;
    
    responseCode = fb.setFloat("Aquaponica/suhu", 30.0);
    Serial.print("Set Float - Response Code: ");
    Serial.println(responseCode);
    
    responseCode = fb.setFloat("Aquaponica/kelembapan", 90.0);
    Serial.print("Set Float - Response Code: ");
    Serial.println(responseCode);

    Serial.println();

    /* ===== PUSHING DATA TO FIREBASE ===== */
    
    Serial.println("Pushing data to Firebase...");
    
    /*
      Push String, Int, Float, or Bool to Firebase
      
      Push creates a unique key for each entry, unlike set which overwrites.
      
      Parameters:
        - path: The path in Firebase where the data will be stored
        - data: The value to push (String, Int, Float, or Bool)

      Returns:
        - HTTP response code as an integer (200 = success)
    */
    

    /* ===== GETTING DATA FROM FIREBASE ===== */
    
    Serial.println("Getting data from Firebase...");
    
    /*
      Get String, Int, Float, or Bool from Firebase
      
      Parameters:
        - path: The path in Firebase from which the data will be retrieved
        - result: Reference variable to store the retrieved value

      Returns:
        - HTTP status code as an integer (200 = success)
        - The retrieved value is stored in the result parameter
        - If failed, result contains default values: "" (String), 0 (Int/Float), false (Bool)
    */
    
    float retrievedFloat;
    responseCode = fb.getFloat("Aquaponica/suhu", retrievedFloat);
    Serial.print("Get Float - Response Code: ");
    Serial.println(responseCode);
    Serial.print("Retrieved Float: ");
    Serial.println(retrievedFloat);
    
    responseCode = fb.getFloat("Aquaponica/kelembapan", retrievedFloat);
    Serial.print("Get Float - Response Code: ");
    Serial.println(responseCode);
    Serial.print("Retrieved Float: ");
    Serial.println(retrievedFloat);

    Serial.println();

    /* ===== REMOVING DATA FROM FIREBASE ===== */
    
    Serial.println("Removing data from Firebase...");
    
    /*
      Remove Data from Firebase
      
      Parameters:
        - path: The path in Firebase from which the data will be removed

      Returns:
        - HTTP response code as an integer (200 = success)
    */
 
    Serial.println();
    Serial.println("Example completed!");
}

void loop() {
    // Nothing to do here
}