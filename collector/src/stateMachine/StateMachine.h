#pragma once

void advanceStateMachine();

enum State
{
    INIT,
    CONNECTING,
    SCANNING,
    POSTING,
    TERMINATED,
};

struct Context
{
    State state;
    float devices;
    int retryCount;
    unsigned long lastSucessTime;
};