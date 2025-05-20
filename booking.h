#ifndef BOOKING_H
#define BOOKING_H

#include "list.h"
#include "vehicle.h"

// Opaque declaration of the Booking structure
typedef struct Booking Booking;

/*
 * Creates a new booking for a user with the specified vehicle and time range.
 *
 * username: the username of the person booking
 * vehicle: pointer to the selected Vehicle
 * startTimestamp: starting time of booking (in hours since epoch)
 * durationHours: duration of the booking in hours
 *
 * returns: pointer to the new Booking
 */
Booking* createBooking(const char* username, Vehicle* vehicle, long startTimestamp, long durationHours);

/*
 * Prints details of a single booking.
 */
void printBooking(const Booking* b);

/*
 * Prints all bookings stored in the given list.
 */
void printAllBookings(List list);

/*
 * Prints all bookings made by a specific user.
 *
 * username: the username to filter bookings by
 */
void printUserBookings(List list, const char* username);

/*
 * Checks whether a vehicle is available within a specific time range.
 *
 * list: list of all bookings
 * plate: plate of the vehicle to check
 * start: start time (in hours)
 * end: end time (in hours)
 *
 * returns: 1 if available, 0 if booked
 */
int isVehicleAvailable(List list, const char* plate, long start, long end);

/*
 * Prompts the user to create a booking by entering the necessary details.
 */
void createBookingPrompt(HashTable* vehicleTable, List bookingList, const char* username);

#endif
