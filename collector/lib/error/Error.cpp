#include "Error.h"
#include <Arduino.h>

const char *errStr(CollectorErr err)
{
    switch (err)
    {
    case NO_ERR:
        return "No error, everything is fine :)";
        break;
    case POST_302_ERROR:
        return "A 302 status code was returned by the POST request, this usually indicates you've been logged out of the guest network";
        break;
    case POST_NON_200_ERROR:
        return "A non 200 status code was retuned by the POST request";
        break;
    case MAC_CHANGE_ERROR:
        return "An error occured while changing the mac adress";
        break;
    case GUEST_LOGIN_POST_ERROR:
        return "Got the wrong status code when sending login POST";
        break;
    case PING_FAILED:
        return "The ping did not succeed";
        break;
    case POST_CONNECTION_ERROR:
        return "A negative response code was returned, this is due to a fault on the device";
        break;
    case POST_READ_TIMEOUT_ERROR:
        return "There was an error on sending the POST request";
        break;
    case POST_GUEST_LOGGED_OUT_ERROR:
        return "Device was logged out of RWTH Guest";
        break;
    case POST_EXCEPTION:
        return "An unknown exception occured while posting";
        break;
    case CONNECT_MAX_RETRY_EXCEEDED:
        return "The maximum connection attempts have been exceeded";
        break;
    case DISCONNECT_MAX_RETRY_EXCEEDED:
        return "The maximum disconnection attempts have been exceeded";
        break;
    default:
        return "Unknown Error";
        break;
    }
}