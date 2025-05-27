#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"
#include "vehicle.h"
#include "user.h"
#include "booking.h"
#include "hash.h"
#include "list.h"

/*
 * File: storage.c
 * ---------------
 * Manages file I/O for vehicles, users, and bookings.
 * Provides functions to load and save data from/to plain text files.
 */

/*
 * Loads vehicle data from a file and inserts each entry into the hash table.
 *
 * table: hash table where vehicles are stored
 * filename: path to the vehicle file
 */
 void LoadVehiclesFromFile(HashTable* table, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char plate[50], type[50], fuel[50], brand[50], model[50], location[50];
        float cost;
        int year, seats;

        if (sscanf(line, "%s %f %s %d %s %s %s %d %s",
                   plate, &cost, type, &seats,
                   fuel, brand, model, &year, location) == 9) {
            Vehicle* v = createVehicle(plate, cost, seats, type, fuel, brand, model, year, location);
            insertVehicle(table, v);
        }
    }

    fclose(file);
}




/*
 * Loads user data from a file and inserts each entry into the hash table.
 *
 * table: hash table where users are stored
 * filename: path to the user file
 */
void LoadUsersFromFile(HashTable* table, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;

    char username[30], firstName[30], lastName[30];
    while (fscanf(file, "%s %s %s", username, firstName, lastName) == 3) {
        User* u = createUser(username, firstName, lastName);
        insertUser(table, u);
    }

    fclose(file);
}

/*
 * Loads booking data from a file and inserts each booking into the list.
 * Uses vehicle references to reconstruct each booking correctly.
 *
 * list: list where bookings are stored
 * filename: path to the booking file
 * vehicleTable: hash table used to retrieve vehicles by plate
 * userTable: hash table used to validate users (optional)
 */
void LoadBookingsFromFile(List list, const char* filename, HashTable* vehicleTable, HashTable* userTable) {
    FILE* file = fopen(filename, "r");
    if (!file) return;

    char username[50], plate[20];
    long start, end;
    float cost;
    int discounted;

    while (fscanf(file, "%s %s %ld %ld %f %d",
                  username, plate, &start, &end, &cost, &discounted) == 6) {
        Vehicle* v = findVehicle(vehicleTable, plate);
        if (v) {
            Booking* b = createBooking(username, v, start, end - start);
            insertList(list, b);
        }
    }

    fclose(file);
}


/*
 * Callback function for saving vehicles to file.
 */
 void vehicleSaver(const char* key, void* value, void* filePtr) {
    Vehicle* v = (Vehicle*)value;
    FILE* file = (FILE*)filePtr;

    fprintf(file, "%s %.2f %s %d %s %s %s %d %s\n",
            getVehiclePlate(v), getVehicleCost(v), getVehicleType(v),
            getVehicleSeats(v), getVehicleFuel(v), getVehicleBrand(v),
            getVehicleModel(v), getVehicleYear(v), getVehicleLocation(v));
}


/*
 * Saves all vehicles stored in the hash table to a text file.
 *
 * table: hash table containing the vehicles
 * filename: path to the output file
 */
void SaveVehiclesToFile(HashTable* table, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return;
    forEachHash(table, vehicleSaver, file);
    fclose(file);
}



/*
 * Callback function for saving users to file.
 */
 void userSaver(const char* key, void* value, void* filePtr) {
    User* u = (User*)value;
    FILE* file = (FILE*)filePtr;
    fprintf(file, "%s %s %s\n", getUserUsername(u), getUserFirstName(u), getUserLastName(u));
}

/*
 * Saves all users stored in the hash table to a text file.
 *
 * table: hash table containing the users
 * filename: path to the output file
 */
void SaveUsersToFile(HashTable* table, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return;
    forEachHash(table, userSaver, file);
    fclose(file);
}

/*
 * Saves all bookings stored in the list to a text file.
 *
 * list: list of Booking pointers
 * filename: path to the output file
 */
void SaveBookingsToFile(List list, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return;

    for (int i = 0; i < getSize(list); i++) {
        Booking* b = (Booking*)getItem(list, i);
        fprintf(file, "%s %s %ld %ld %.2f %d\n",
                getBookingUsername(b), getBookingPlate(b),
                getBookingStartTimestamp(b), getBookingEndTimestamp(b),
                getBookingTotalCost(b), getBookingIsDiscounted(b));
    }
    fclose(file);
}
