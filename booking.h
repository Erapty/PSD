#ifndef BOOKING_H
#define BOOKING_H

#include "list.h"
#include "vehicle.h"
#include "hash.h"

// Opaque declaration of the Booking structure
typedef struct Booking Booking;

/*
 * Creates a new booking instance.
 *
 * username: the user making the booking
 * vehicle: the vehicle being booked
 * startTimestamp: starting time in hours since UNIX epoch
 * durationHours: duration of the booking in hours
 *
 * returns: pointer to the created Booking
 */
Booking* createBooking(const char* username, Vehicle* vehicle, long startTimestamp, long durationHours);

/*
 * Prints the details of a single booking.
 */
void printBooking(const Booking* b);

/*
 * Prints all bookings contained in the given list.
 */
void printAllBookings(List list);

/*
 * Prints all bookings made by a specific user.
 *
 * username: username of the client
 */
void printUserBookings(List list, const char* username);

/*
 * Checks whether a vehicle is available in a given time interval.
 *
 * list: list of all bookings
 * plate: vehicle plate to check
 * start: starting timestamp (in hours)
 * end: ending timestamp (in hours)
 *
 * returns: 1 if available, 0 if occupied
 */
int isVehicleAvailable(List list, const char* plate, long start, long end);

/*
 * Prompts user input to create and store a booking in the system.
 */
void createBookingPrompt(HashTable* vehicleTable, List bookingList, const char* username);

/* === GETTER FUNCTIONS ===
 * Used to access private fields while maintaining encapsulation.
 */

// Returns the username associated with the booking
const char* getBookingUsername(const Booking* b);

// Returns the booked vehicle's plate
const char* getBookingPlate(const Booking* b);

// Returns the start timestamp of the booking
long getBookingStartTimestamp(const Booking* b);

// Returns the end timestamp of the booking
long getBookingEndTimestamp(const Booking* b);

// Returns the total cost of the booking
float getBookingTotalCost(const Booking* b);

// Returns whether the booking received a discount
int getBookingIsDiscounted(const Booking* b);

#endif
