#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vehicle.h"
#include "hash.h"
#include "list.h"
#include "booking.h"

/*
 * File: vehicle.c
 * ----------------
 * Contains functions for creating, managing, and displaying vehicle records
 * used in the car sharing system. Vehicles are stored in a hash table and 
 * can be inserted, retrieved, listed, and filtered based on availability.
 */

// Internal structure of Vehicle
struct Vehicle {
    char* plate;
    float cost;
    int seats;
    char* type;
    char* fuel;
    char* brand;
    char* model;
    int year;
    char* location;
};

/*
 * Function: createVehicle
 * -----------------------
 * Allocates and initializes a new vehicle instance with the given parameters.
 *
 * plate: license plate of the vehicle
 * cost: hourly rental cost
 * seats: number of seats in the vehicle
 * type: vehicle type (e.g., car, van)
 * fuel: fuel type (e.g., petrol, diesel)
 * brand: brand of the vehicle
 * model: model of the vehicle
 * year: manufacturing year
 * location: location of the vehicle
 *
 * returns: pointer to the newly created Vehicle object
 */
Vehicle* createVehicle(const char* plate, float cost, int seats, const char* type,
                       const char* fuel, const char* brand, const char* model,
                       int year, const char* location) {
    Vehicle* v = malloc(sizeof(Vehicle));
    if (!v) return NULL;

    v->plate = strdup(plate);
    v->cost = cost;
    v->seats = seats;
    v->type = strdup(type);
    v->fuel = strdup(fuel);
    v->brand = strdup(brand);
    v->model = strdup(model);
    v->year = year;
    v->location = strdup(location);
    return v;
}

/*
 * Function: freeVehicle
 * ---------------------
 * Frees all memory associated with a Vehicle instance.
 *
 * v: pointer to the Vehicle to be freed
 */
void freeVehicle(Vehicle* v) {
    if (!v) return;
    free(v->plate);
    free(v->type);
    free(v->fuel);
    free(v->brand);
    free(v->model);
    free(v->location);
    free(v);
}

/*
 * Function: printVehicle
 * ----------------------
 * Displays all the information about a vehicle in a readable format.
 *
 * v: pointer to the Vehicle to be printed
 */
void printVehicle(const Vehicle* v) {
    printf("Plate: %s | Type: %s | Brand: %s | Model: %s | Cost: %.2f/h | Seats: %d | Fuel: %s | Year: %d | Location: %s\n",
           v->plate, v->type, v->brand, v->model, v->cost, v->seats, v->fuel, v->year, v->location);
}

/*
 * Function: getVehiclePlate
 * -------------------------
 * Returns the license plate of the vehicle.
 */
const char* getVehiclePlate(Vehicle* v) { return v->plate; }

/*
 * Function: getVehicleCost
 * ------------------------
 * Returns the hourly rental cost of the vehicle.
 */
float getVehicleCost(Vehicle* v) { return v->cost; }

/*
 * Function: insertVehicle
 * -----------------------
 * Inserts a Vehicle into a hash table using its plate as the key.
 *
 * table: pointer to the hash table
 * v: pointer to the Vehicle to insert
 */
void insertVehicle(HashTable* table, Vehicle* v) {
    insertHashTable(table, v->plate, v);
}

/*
 * Function: findVehicle
 * ---------------------
 * Searches for a vehicle by plate in the hash table.
 *
 * table: pointer to the hash table
 * plate: plate to search
 *
 * returns: pointer to the Vehicle if found, NULL otherwise
 */
Vehicle* findVehicle(HashTable* table, const char* plate) {
    return (Vehicle*)searchHashTable(table, plate);
}

/*
 * Function: addVehiclePrompt
 * --------------------------
 * Admin prompt to collect vehicle data from the user and insert it
 * into the hash table.
 */
void addVehiclePrompt(HashTable* table) {
    char plate[20], type[20], fuel[20], brand[30], model[30], location[30];
    float cost;
    int year, seats;

    printf("Enter plate: "); scanf("%s", plate);
    printf("Enter cost per hour: "); scanf("%f", &cost);
    printf("Enter type: "); scanf("%s", type);
    printf("Enter number of seats: "); scanf("%d", &seats);
    printf("Enter fuel type: "); scanf("%s", fuel);
    printf("Enter brand: "); scanf("%s", brand);
    printf("Enter model: "); scanf("%s", model);
    printf("Enter year: "); scanf("%d", &year);
    printf("Enter location: "); scanf("%s", location);
    getchar(); // Consume leftover newline

    Vehicle* v = createVehicle(plate, cost, seats, type, fuel, brand, model, year, location);
    insertVehicle(table, v);
    printf("Vehicle added successfully.\n");
}

/*
 * Function: removeVehiclePrompt
 * -----------------------------
 * Admin prompt to remove a vehicle from the hash table using its plate.
 */
void removeVehiclePrompt(HashTable* table) {
    char plate[20];
    printf("Enter plate of vehicle to remove: ");
    scanf("%s", plate); getchar();
    deleteHashTable(table, plate);
    printf("Vehicle removed (if existed).\n");
}

/*
 * Function: printAllVehicles
 * --------------------------
 * Iterates over the hash table and prints all stored vehicles.
 */
void printAllVehicles(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* node = table->table[i];
        while (node) {
            printVehicle((Vehicle*)node->value);
            node = node->next;
        }
    }
}

/*
 * Function: printAvailableVehiclesAt
 * ----------------------------------
 * Displays all vehicles available within a given time period.
 *
 * table: hash table of all vehicles
 * bookingList: list of existing bookings
 * start: start timestamp (in hours)
 * end: end timestamp (in hours)
 */
void printAvailableVehiclesAt(HashTable* table, List bookingList, long start, long end) {
    printf("\nAvailable vehicles from selected period:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* node = table->table[i];
        while (node) {
            Vehicle* v = (Vehicle*)node->value;
            if (isVehicleAvailable(bookingList, v->plate, start, end)) {
                printVehicle(v);
            }
            node = node->next;
        }
    }
}
