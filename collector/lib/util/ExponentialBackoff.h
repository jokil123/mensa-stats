#pragma once

void exponentialBackoff(int retries);

bool tryBackoff(int *retries, int state);