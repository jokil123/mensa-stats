#pragma once
#include <Dotenv.h>

// #define SCAN_COUNT 30
#define SCAN_COUNT 10
#define SCAN_DURATION 30 * 1000
// #define SCAN_DURATION 5 * 60 * 1000

#define MIN_UPTIME 5 * 60 * 1000       // only reboot if running for at least 5 min
#define MAX_UPTIME 24 * 60 * 60 * 1000 // reboot every 24 hours