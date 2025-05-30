#include <time.h>
#include <string.h>
#include <stdio.h>
#include "timeutils.h"

/*
 * File: timeutils.c
 * -----------------
 * Provides utility functions for converting between
 * date-time strings and UNIX timestamps (in seconds).
 * These functions are used for handling booking time periods.
 */

/*
 * Function: convertToTimestamp
 * ----------------------------
 * Converts a date-time string in the format "YYYY-MM-DD HH"
 * into a UNIX timestamp expressed in seconds since epoch.
 *
 * datetimeStr: input string in the specified format
 *
 * returns: timestamp in seconds (long integer)
 */
long convertToTimestamp(const char* datetimeStr) {
    struct tm timeStruct = {0};
    int year, month, day, hour;

    // Parse the string manually using sscanf (portable across systems)
    if (sscanf(datetimeStr, "%d-%d-%d %d", &year, &month, &day, &hour) != 4) {
        return -1; // Invalid format
    }

    timeStruct.tm_year = year - 1900;
    timeStruct.tm_mon = month - 1;
    timeStruct.tm_mday = day;
    timeStruct.tm_hour = hour;
    timeStruct.tm_min = 0;
    timeStruct.tm_sec = 0;
    timeStruct.tm_isdst = -1;

    return mktime(&timeStruct);
}

/*
 * Function: timestampToString
 * ---------------------------
 * Converts a timestamp expressed in seconds since epoch into
 * date-time string, using the format "YYYY-MM-DD HH:MM".
 *
 * timestamp: input timestamp in seconds
 * buffer: output buffer to write the string into
 * size: size of the buffer
 */
void timestampToString(long timestamp, char* buffer, size_t size) {
    time_t rawTime = timestamp;
    struct tm* timeStruct = localtime(&rawTime);
    strftime(buffer, size, "%Y-%m-%d %H:%M", timeStruct);
}
