#pragma once

enum CollectorErr
{
    NO_ERR,
    POST_302_ERROR,
    POST_NON_200_ERROR,
    MAC_CHANGE_ERROR,
    GUEST_LOGIN_POST_ERROR,
    PING_FAILED,
    POST_CONNECTION_ERROR,
    POST_READ_TIMEOUT_ERROR,
    POST_GUEST_LOGGED_OUT_ERROR,
    POST_EXCEPTION,
    CONNECT_MAX_RETRY_EXCEEDED,
    DISCONNECT_MAX_RETRY_EXCEEDED,
};

const char *errStr(CollectorErr err);