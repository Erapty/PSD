#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "booking.h"

/*
 * File: booking.c
 * ---------------
 * Handles booking operations for the car sharing system. This includes
 * creating bookings, printing booking details, filtering bookings by user,
 * and interacting with the user to make a booking.
 */

// Internal structure representing a booking
struct Booking {
    char username[50];
    char plate[20];
    int startHour;
    int endHour;
    int startDay;
    int endDay;
    float totalCost;
    int isDiscounted;
};

/*
 * Function: createBooking
 * -----------------------
 * Allocates and initializes a new Booking instance for a given user and vehicle.
 * It calculates duration, applies discount if applicable, and stores all details.
 *
 * username: the user making the booking
 * vehicle: the vehicle being booked
 * time: struct containing start/end day and hour
 *
 * returns: pointer to the newly created Booking
 */
Booking* createBooking(const char* username, Vehicle* vehicle, BookingTime time) {
    Booking* booking = malloc(sizeof(Booking));
    if (!booking) return NULL;

    strncpy(booking->username, username, 50);
    strncpy(booking->plate, getVehiclePlate(vehicle), 20);
    booking->startDay = time.startDay;
    booking->endDay = time.endDay;
    booking->startHour = time.startHour;
    booking->endHour = time.endHour;

    int duration = (time.endDay - time.startDay) * 24 + (time.endHour - time.startHour);
    booking->totalCost = duration * getVehicleCost(vehicle);
    booking->isDiscounted = duration > 20 ? 1 : 0;
    if (booking->isDiscounted)
        booking->totalCost *= 0.85f;  // 15% discount for long rentals

    return booking;
}

/*
 * Function: printBooking
 * ----------------------
 * Displays all relevant information about a booking, including time, cost,
 * and booking status (upcoming, ongoing, past).
 *
 * b: pointer to the Booking to print
 */
void printBooking(const Booking* b) {
    char start[64], end[64];
    timestampToString(b->startTimestamp, start, sizeof(start));
    timestampToString(b->endTimestamp, end, sizeof(end));

    // Get current timestamp in hours
    time_t nowSec = time(NULL);
    long now = nowSec / 3600;

    const char* status;
    if (now < b->startTimestamp) {
        status = "Upcoming";
    } else if (now >= b->startTimestamp && now < b->endTimestamp) {
        status = "Ongoing";
    } else {
        status = "Past";
    }

    printf("Booking for %s\n", b->username);
    printf("Vehicle: %s\n", b->plate);
    printf("From: %s\n", start);
    printf("To:   %s\n", end);
    printf("Cost: %.2f (%s)\n", b->totalCost, b->isDiscounted ? "discounted" : "standard");
    printf("Status: %s\n\n", status);
}

/*
 * Function: printAllBookings
 * --------------------------
 * Iterates through the booking list and prints all bookings.
 *
 * list: the list containing Booking instances
 */
void printAllBookings(List list) {
    int size = getSize(list);
    for (int i = 0; i < size; i++) {
        Booking* b = (Booking*)getItem(list, i);
        printBooking(b);
    }
}

/*
 * Function: printUserBookings
 * ---------------------------
 * Prints all bookings made by a specific user.
 *
 * list: the list containing Booking instances
 * username: the username to filter bookings by
 */
void printUserBookings(List list, const char* username) {
    int size = getSize(list);
    for (int i = 0; i < size; i++) {
        Booking* b = (Booking*)getItem(list, i);
        if (strcmp(b->username, username) == 0) {
            printBooking(b);
        }
    }
}

/*
 * Function: createBookingPrompt
 * -----------------------------
 * Prompts the client to input booking details and attempts to create
 * and insert a new booking.
 *
 * vehicleTable: hash table containing vehicles
 * bookingList: list where the new booking will be stored
 * username: the user making the booking
 */
void createBookingPrompt(HashTable* vehicleTable, List bookingList, const char* username) {
    char plate[20];
    int startDay, endDay, startHour, endHour;

    printf("Enter vehicle plate: "); scanf("%s", plate);
    printf("Start day (1-7): "); scanf("%d", &startDay);
    printf("End day (1-7): "); scanf("%d", &endDay);
    printf("Start hour (0-23): "); scanf("%d", &startHour);
    printf("End hour (0-23): "); scanf("%d", &endHour);
    getchar(); // Consume newline

    Vehicle* vehicle = findVehicle(vehicleTable, plate);
    if (!vehicle) {
        printf("Vehicle not found.\n");
        return;
    }

    BookingTime time = {startHour, endHour, startDay, endDay};
    Booking* b = createBooking(username, vehicle, time);
    insertList(bookingList, b);
    printf("Booking created successfully.\n");
}
