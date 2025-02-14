#pragma once

enum PostError
{
    NO_ERROR,
    FATAL_ERROR,
    CONNECTION_ERROR,
};

PostError postOccupancy(char *api_url, char *device, char *token, int occupancy);