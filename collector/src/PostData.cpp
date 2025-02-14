#include <PostData.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <VarExpand.h>

int postOccupancy(char *api_url, char *device, char *token, int occupancy)
{
    HTTPClient http;

    char urlBuf[256];
    snprintf(urlBuf, sizeof(urlBuf), "%s%s", api_url, "/api/occupancy");

    http.begin(urlBuf);

    http.addHeader("Content-Type", "Content-Type: application/json");

    char buffer[256];

    snprintf(buffer, sizeof(buffer), "{\"device\": \"%s\", \"token\": \"%s\", \"occupancy\": %d}", device, token, occupancy);

    // Serial.println(buffer);

    int httpResponseCode = http.POST(buffer); // Send the actual POST request

    if (httpResponseCode == 200)
    {
        // Serial.println("Post Ok");
    }
    else if (httpResponseCode > 0)
    {
        Serial.print("Non 200 Response: ");
        Serial.println(httpResponseCode); // Print return code
    }
    else
    {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }

    http.end();

    return httpResponseCode;
}
