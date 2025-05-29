#include "StateMachine.h"
#include "states/States.h"
#include <Arduino.h>
#include <Config.h>

Context *ctx = new Context{INIT, 0};

void advanceStateMachine()
{
    stateWatchdog(ctx);

    switch (ctx->state)
    {
    case INIT:
        stateInit(ctx);
        break;
    case CONNECTING:
        stateConnecting(ctx);
        break;
    case SCANNING:
        stateScanning(ctx);
        break;
    case POSTING:
        statePosting(ctx);
        break;
    case TERMINATED:
        stateTerminated(ctx);
        break;
    }
}
