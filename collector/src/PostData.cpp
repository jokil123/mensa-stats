#include <PostData.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <VarExpand.h>
#include "wifi/WifiUtil.h"
#include "Error.h"

// throws POST_EXCEPTION, POST_GUEST_LOGGED_OUT_ERROR, POST_302_ERROR, POST_NON_200_ERROR, POST_CONNECTION_ERROR, POST_READ_TIMEOUT_ERROR
CollectorErr postOccupancy(const char *api_url, const char *device, const char *token, float occupancy)
{
    HTTPClient http;

    char urlBuf[256];
    snprintf(urlBuf, sizeof(urlBuf), "%s%s", api_url, "/api/occupancy");

    http.begin(urlBuf);

    http.addHeader("Content-Type", "application/json");

    char buffer[256];

    snprintf(buffer, sizeof(buffer), "{\"device\": \"%s\", \"token\": \"%s\", \"occupancy\": %f}", device, token, occupancy);

    int httpResponseCode;

    try
    {
        collectHeaders(http);
        httpResponseCode = http.POST(buffer); // Send the actual POST request
        printHeaders(http);
    }
    catch (const std::exception &e)
    {
        Serial.printf("Post exception %s\n", e.what());
        http.end();
        return CollectorErr::POST_EXCEPTION;
    }

    if (httpResponseCode == 200)
    {
        Serial.println("Post Ok");
    }
    else if (httpResponseCode == 302)
    {
        http.end();

        if (http.header("Location") == "https://access.wlan.rwth-aachen.de/")
        {
            Serial.println("Logged out from guest WIFI");

            return CollectorErr::POST_GUEST_LOGGED_OUT_ERROR;
        }

        Serial.println("HTTP 302 Found");
        return CollectorErr::POST_302_ERROR;
    }
    else if (httpResponseCode > 0)
    {
        Serial.printf("Non 200 Response: %d (%s)\n", httpResponseCode, http.errorToString(httpResponseCode).c_str());
        http.end();
        return CollectorErr::POST_NON_200_ERROR;
    }
    else if (httpResponseCode < 0)
    {
        http.end();
        Serial.printf("Negative response code: %d (%s)\n", httpResponseCode, http.errorToString(httpResponseCode).c_str());
        Serial.printf("Request info: %s\n", urlBuf);
        return CollectorErr::POST_CONNECTION_ERROR;
    }
    else
    {
        Serial.printf("Error on sending POST: %d (%s)\n", httpResponseCode, http.errorToString(httpResponseCode).c_str());
        return CollectorErr::POST_READ_TIMEOUT_ERROR;
    }

    http.end();
    return CollectorErr::NO_ERR;
}
