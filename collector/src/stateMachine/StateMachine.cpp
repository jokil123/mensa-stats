#include "StateMachine.h"
#include "states/States.h"
#include <Util.h>

Context *ctx = new Context{INIT, 0};

void advanceStateMachine()
{
    printTimeSinceStart();

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
        break;
    }
}
