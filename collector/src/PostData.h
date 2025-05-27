#pragma once
#include <HTTPClient.h>
#include "Error.h"

CollectorErr postOccupancy(const char *api_url, const char *device, const char *token, float occupancy);
