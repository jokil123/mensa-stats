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

enum StateMachineError
{
    WIFI_CONNECTION_ERROR,
    POST_ERROR,
    UNEXPECTED_ERROR,
};

struct Context
{
    State state;
    float devices;
};