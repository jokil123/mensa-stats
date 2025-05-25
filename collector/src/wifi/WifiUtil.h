#include <HTTPClient.h>
#include "Error.h"

CollectorErr tryBlockUntilDisconnected(int maxAttempts = -1);

CollectorErr tryBlockUntilConnection(int maxAttempts = -1);

void printWifiInfo();

void printWifiNetworks();

CollectorErr testConnection(const char *domain = "www.google.com");

void collectHeaders(HTTPClient &http);

void printHeaders(HTTPClient &http, bool hideEmpty = true);