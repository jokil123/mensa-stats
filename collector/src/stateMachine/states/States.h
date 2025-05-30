#pragma once

#include <stateMachine/StateMachine.h>

void stateScanning(Context *ctx);
void statePosting(Context *ctx);
void stateInit(Context *ctx);
void stateConnecting(Context *ctx);
void stateTerminated(Context *ctx);
void stateWatchdog(Context *ctx);