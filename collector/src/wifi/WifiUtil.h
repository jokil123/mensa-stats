#include <HTTPClient.h>

bool tryBlockUntilDisconnected(int maxAttempts = -1);

bool tryBlockUntilConnection(int maxAttempts = -1);

void printWifiInfo();

void printWifiNetworks();

bool testConnection(const char *domain = "www.google.com");

void collectHeaders(HTTPClient &http);

void printHeaders(HTTPClient &http, bool hideEmpty = true);