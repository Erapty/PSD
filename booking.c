#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "booking.h"
#include "timeutils.h"

/*
 * File: booking.c
 * ----------------
 * Implements the Booking data structure and related operations.
 * This includes creating bookings, printing, checking availability,
 * and prompting user input for bookings.
 */

// Internal structure for a booking
struct Booking {
    char username[50];
    char plate[20];
    long startTimestamp;
    long endTimestamp;
    float totalCost;
    int isDiscounted;
};

/*
 * Creates a new booking with the specified parameters.
 */
Booking* createBooking(const char* username, Vehicle* vehicle, long startTimestamp, long durationSeconds) {
    Booking* booking = malloc(sizeof(Booking));
    if (!booking) return NULL;

    strncpy(booking->username, username, 50);
    strncpy(booking->plate, getVehiclePlate(vehicle), 20);
    booking->startTimestamp = startTimestamp;
    booking->endTimestamp = startTimestamp + durationSeconds;

    float costPerHour = getVehicleCost(vehicle);
    float durationHours = durationSeconds / 3600.0f;

    booking->totalCost = durationHours * costPerHour;
    booking->isDiscounted = durationHours > 20 ? 1 : 0;
    if (booking->isDiscounted)
        booking->totalCost *= 0.85f;

    return booking;
}

/*
 * Prints the details of a booking, including calculated status.
 */
void printBooking(const Booking* b) {
    char start[64], end[64];
    timestampToString(b->startTimestamp, start, sizeof(start));
    timestampToString(b->endTimestamp, end, sizeof(end));

    time_t now = time(NULL);

    const char* status;
    if (now < b->startTimestamp) {
        status = "Upcoming";
    } else if (now >= b->startTimestamp && now < b->endTimestamp) {
        status = "Ongoing";
    } else {
        status = "Past";
    }

    float cost = b->totalCost;

    printf("Booking for %s\n", b->username);
    printf("Vehicle: %s\n", b->plate);
    printf("From: %s\n", start);
    printf("To:   %s\n", end);
    printf("Cost: %.2f (%s)\n", cost, b->isDiscounted ? "discounted" : "standard");
    printf("Status: %s\n\n", status);
}

/*
 * Prints all bookings stored in the given list.
 */
void printAllBookings(List list) {
    int size = getSize(list);
    for (int i = 0; i < size; i++) {
        Booking* b = (Booking*)getItem(list, i);
        printBooking(b);
    }
}

/*
 * Prints all bookings made by a specific user.
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
 * Prompts user input to create a booking and stores it in the booking list.
 */
 void createBookingPrompt(HashTable* vehicleTable, List bookingList, const char* username) {
    char plate[20];
    char datetime[64];
    int duration;

    printf("Enter vehicle plate: ");
    scanf("%s", plate);
    getchar();

    printf("Start date (YYYY-MM-DD HH): ");
    fgets(datetime, sizeof(datetime), stdin);
    datetime[strcspn(datetime, "\n")] = 0;

    printf("Duration (hours): ");
    scanf("%d", &duration);
    getchar();

    long start = convertToTimestamp(datetime);
    long durationSeconds = duration * 3600;
    long end = start + durationSeconds;

    Vehicle* v = findVehicle(vehicleTable, plate);
    if (!v) {
        printf("Vehicle not found.\n");
        return;
    }

    if (!isVehicleAvailable(bookingList, plate, start, end)) {
        printf("This vehicle is not available in the selected period. Try another.\n");
        return;
    }

    float costPerHour = getVehicleCost(v);
    float totalCost = duration * costPerHour;
    int discounted = 0;
    if (duration > 20) {
        totalCost *= 0.85f;
        discounted = 1;
    }

    char endStr[64];
    timestampToString(end, endStr, sizeof(endStr));

    printf("\n=== BOOKING SUMMARY ===\n");
    printf("Vehicle: %s\n", getVehiclePlate(v));
    printf("Duration: %d hours\n", duration);
    printf("End date/time: %s\n", endStr);
    printf("Total cost: %.2f %s\n", totalCost, discounted ? "(discount applied)" : "(standard rate)");

    printf("\nDo you want to confirm the booking? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);
    getchar();

    if (confirm == 'y' || confirm == 'Y') {
        // 🔧 FIX: passa i secondi, non le ore!
        Booking* b = createBooking(username, v, start, durationSeconds);
        insertList(bookingList, b);
        printf("\nBooking created successfully!\n");
    } else {
        printf("\nBooking cancelled.\n");
    }
}


/*
 * Check if a vehicle is available between start and end time
 */
 bool isVehicleAvailable(List bookings, const char* plate, long start, long end) {
    int size = getSize(bookings);
    for (int i = 0; i < size; i++) {
        Booking* b = (Booking*)getItem(bookings, i);
        if (strcmp(getBookingPlate(b), plate) == 0) {
            long bStart = getBookingStartTimestamp(b);
            long bEnd = getBookingEndTimestamp(b);
            if (!(end <= bStart || start >= bEnd)) {
                return false;
            }
        }
    }
    return true;
}


/* === GETTER IMPLEMENTATIONS === */

const char* getBookingUsername(const Booking* b) { return b->username; }
const char* getBookingPlate(const Booking* b) { return b->plate; }
long getBookingStartTimestamp(const Booking* b) { return b->startTimestamp; }
long getBookingEndTimestamp(const Booking* b) { return b->endTimestamp; }
float getBookingTotalCost(const Booking* b) { return b->totalCost; }
int getBookingIsDiscounted(const Booking* b) { return b->isDiscounted; }


/* === SETTER IMPLEMENTATIONS === */

void setBookingCost(Booking* b, float cost) {
    b->totalCost = cost;
}

void setBookingDiscounted(Booking* b, int discounted) {
    b->isDiscounted = discounted;
}
