#include "StateMachine.h"
#include <Arduino.h>
#include <PostData.h>
#include <dotenv.h>
#include <wifi/WifiConnect.h>
#include <ble/BLE.h>
#include "states/Connecting.h"
#include "states/Sanning.h"
#include "states/Init.h"
#include "states/Posting.h"

Context ctx = {INIT, 0};

void advanceStateMachine()
{
    switch (ctx.state)
    {
    case INIT:
        stateInit(&ctx);
        break;
    case CONNECTING:
        stateConnecting(&ctx);
        break;
    case SCANNING:
        stateScanning(&ctx);
        ctx.state = CONNECTING;
        break;
    case POSTING:
        statePosting(&ctx);
        break;
    case TERMINATED:
        break;
    }
}
