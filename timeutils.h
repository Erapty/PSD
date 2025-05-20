#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <stddef.h>

/*
 * Converts a date-time string in the format "YYYY-MM-DD HH" to a UNIX timestamp.
 * The timestamp is returned in hours (i.e., seconds since epoch divided by 3600).
 *
 * datetimeStr: input string representing the date and time
 *
 * returns: UNIX timestamp in hours
 */
long convertToTimestamp(const char* datetimeStr);

/*
 * Converts a UNIX timestamp in hours back to a formatted string.
 * The output format is "YYYY-MM-DD HH:MM".
 *
 * timestamp: input timestamp in hours
 * buffer: destination buffer for the formatted string
 * size: size of the buffer
 */
void timestampToString(long timestamp, char* buffer, size_t size);

#endif
