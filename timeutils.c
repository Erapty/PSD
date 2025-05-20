#include <time.h>
#include <string.h>
#include "timeutils.h"

/*
 * File: timeutils.c
 * -----------------
 * Provides utility functions for converting between human-readable
 * date-time strings and UNIX timestamps (in hours).
 * These functions are used for handling booking time periods.
 */

/*
 * Function: convertToTimestamp
 * ----------------------------
 * Converts a date-time string in the format "YYYY-MM-DD HH"
 * into a UNIX timestamp expressed in hours since epoch.
 *
 * datetimeStr: input string in the specified format
 *
 * returns: timestamp in hours (long integer)
 */
long convertToTimestamp(const char* datetimeStr) {
    struct tm timeStruct = {0};
    strptime(datetimeStr, "%Y-%m-%d %H", &timeStruct);
    time_t rawTime = mktime(&timeStruct);
    return rawTime / 3600;  // return as hour-based timestamp
}

/*
 * Function: timestampToString
 * ---------------------------
 * Converts a timestamp expressed in hours since epoch into a human-readable
 * date-time string, using the format "YYYY-MM-DD HH:MM".
 *
 * timestamp: input timestamp in hours
 * buffer: output buffer to write the string into
 * size: size of the buffer
 */
void timestampToString(long timestamp, char* buffer, size_t size) {
    time_t rawTime = timestamp * 3600;
    struct tm* timeStruct = localtime(&rawTime);
    strftime(buffer, size, "%Y-%m-%d %H:%M", timeStruct);
}
