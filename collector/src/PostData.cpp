#include <PostData.h>
#include <Arduino.h>
#include <HTTPClient.h>

void postOccupancy(char *endpoint, char *auth, int occupancy)
{
    HTTPClient http;

    http.begin(endpoint);
    http.addHeader("Content-Type", "Content-Type: application/json");

    int httpResponseCode = http.POST(String(occupancy)); // Send the actual POST request

    if (httpResponseCode > 0)
    {
        String response = http.getString(); // Get the response to the request
        Serial.println(httpResponseCode);   // Print return code
        Serial.println(response);           // Print request answer
    }
    else
    {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}
