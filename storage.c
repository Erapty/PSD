#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"
#include "vehicle.h"
#include "user.h"
#include "booking.h"

/*
 * File: storage.c
 * ---------------
 * Handles persistent storage for vehicles, users, and bookings.
 * Provides functions to load and save data to and from text files.
 */

/*
 * Function: LoadVehiclesFromFile
 * ------------------------------
 * Loads vehicle data from a text file and inserts each record into the hash table.
 *
 * table: hash table where vehicles are stored
 * filename: name of the file to read from
 */
void LoadVehiclesFromFile(HashTable* table, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;

    char plate[20], type[20], fuel[20], brand[30], model[30], location[30];
    float cost;
    int year, seats;

    while (fscanf(file, "%s %f %s %d %s %s %s %d %s",
                  plate, &cost, type, &seats, fuel, brand, model, &year, location) == 9) {
        Vehicle* v = createVehicle(plate, cost, seats, type, fuel, brand, model, year, location);
        insertVehicle(table, v);
    }
    fclose(file);
}

/*
 * Function: LoadUsersFromFile
 * ---------------------------
 * Loads user data from a text file and inserts each user into the hash table.
 *
 * table: hash table where users are stored
 * filename: name of the file to read from
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
 * Function: LoadBookingsFromFile
 * ------------------------------
 * Loads booking records from a file and inserts them into the booking list.
 * Each booking is reconstructed using the vehicle reference.
 *
 * list: list where bookings are stored
 * filename: name of the file to read from
 * vehicleTable: table used to retrieve vehicles by plate
 * userTable: unused, may be removed
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
 * Function: SaveVehiclesToFile
 * ----------------------------
 * Saves all vehicles from the hash table to a text file.
 *
 * table: hash table containing vehicles
 * filename: name of the file to write to
 */
void SaveVehiclesToFile(HashTable* table, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return;

    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* node = table->table[i];
        while (node) {
            Vehicle* v = (Vehicle*)node->value;
            fprintf(file, "%s %.2f %s %d %s %s %s %d %s\n",
                    v->plate, v->cost, v->type, v->seats,
                    v->fuel, v->brand, v->model, v->year, v->location);
            node = node->next;
        }
    }
    fclose(file);
}

/*
 * Function: SaveUsersToFile
 * -------------------------
 * Saves all users from the hash table to a text file.
 *
 * table: hash table containing users
 * filename: name of the file to write to
 */
void SaveUsersToFile(HashTable* table, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return;

    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* node = table->table[i];
        while (node) {
            User* u = (User*)node->value;
            fprintf(file, "%s %s %s\n", u->username, u->firstName, u->lastName);
            node = node->next;
        }
    }
    fclose(file);
}

/*
 * Function: SaveBookingsToFile
 * ----------------------------
 * Saves all bookings from the list to a text file.
 *
 * list: list of bookings
 * filename: name of the file to write to
 */
void SaveBookingsToFile(List list, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return;

    for (int i = 0; i < getSize(list); i++) {
        Booking* b = (Booking*)getItem(list, i);
        fprintf(file, "%s %s %ld %ld %.2f %d\n",
                b->username, b->plate, b->startTimestamp, b->endTimestamp,
                b->totalCost, b->isDiscounted);
    }
    fclose(file);
}
