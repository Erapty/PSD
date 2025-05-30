#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vehicle.h"
#include "hash.h"
#include "booking.h"

/*
 * File: vehicle.c
 * ---------------
 * Implements the Vehicle data structure and related operations,
 * including creation, insertion into hash tables, printing,
 * and availability checks.
 */

// Internal structure of a Vehicle
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

char* my_strdup(const char* src) {
    if (!src) return NULL;
    size_t len = strlen(src) + 1;
    char* dst = malloc(len);
    if (dst) {
        memcpy(dst, src, len);
    }
    return dst;
}

/*
 * Creates a new Vehicle instance with the provided information.
 *
 * returns: pointer to the new Vehicle
 */
Vehicle* createVehicle(const char* plate, float cost, int seats, const char* type,
    const char* fuel, const char* brand, const char* model,
    int year, const char* location) {
    Vehicle* v = malloc(sizeof(struct Vehicle));
    if (!v) return NULL;

    v->plate = strdup(plate);
    v->type = strdup(type);
    v->fuel = strdup(fuel);
    v->brand = strdup(brand);
    v->model = strdup(model);
    v->location = strdup(location);

    v->cost = cost;
    v->seats = seats;
    v->year = year;

    return v;
}

/*
 * Frees all memory allocated for a Vehicle instance.
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

/* === GETTERS === */

const char* getVehiclePlate(const Vehicle* v) { return v->plate; }
float getVehicleCost(const Vehicle* v) { return v->cost; }
int getVehicleSeats(const Vehicle* v) { return v->seats; }
const char* getVehicleType(const Vehicle* v) { return v->type; }
const char* getVehicleFuel(const Vehicle* v) { return v->fuel; }
const char* getVehicleBrand(const Vehicle* v) { return v->brand; }
const char* getVehicleModel(const Vehicle* v) { return v->model; }
int getVehicleYear(const Vehicle* v) { return v->year; }
const char* getVehicleLocation(const Vehicle* v) { return v->location; }

/*
 * Inserts a Vehicle into a hash table using the plate as key.
 */
void insertVehicle(HashTable* table, Vehicle* v) {
    insertHashTable(table, v->plate, v);
}

/*
 * Finds a Vehicle in the hash table by its plate.
 *
 * returns: pointer to the Vehicle if found, NULL otherwise
 */
Vehicle* findVehicle(HashTable* table, const char* plate) {
    return (Vehicle*)searchHashTable(table, plate);
}

/*
 * Prompts admin to enter vehicle details and adds it to the hash table.
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
    getchar(); // Consume newline

    Vehicle* v = createVehicle(plate, cost, seats, type, fuel, brand, model, year, location);
    insertVehicle(table, v);
    printf("Vehicle added successfully.\n");
}

/*
 * Prompts admin to remove a vehicle from the hash table using its plate.
 */
void removeVehiclePrompt(HashTable* table) {
    char plate[20];
    printf("Enter plate of vehicle to remove: ");
    scanf("%s", plate); getchar();
    deleteHashTable(table, plate);
    printf("Vehicle removed (if existed).\n");
}

/*
 * Prints all details of a single Vehicle.
 */
void printVehicle(const Vehicle* v) {
    printf("Plate: %s | Type: %s | Brand: %s | Model: %s | Cost: %.2f/h | Seats: %d | Fuel: %s | Year: %d | Location: %s\n",
           v->plate, v->type, v->brand, v->model, v->cost, v->seats, v->fuel, v->year, v->location);
}

/*
 * Callback used by forEachHash to print each vehicle in the table.
 */
void vehiclePrinter(const char* key, void* value, void* unused) {
    Vehicle* v = (Vehicle*)value;
    printVehicle(v);
}

/*
 * Iterates through the vehicle table and prints all vehicles.
 */
void printAllVehicles(HashTable* table) {
    forEachHash(table, vehiclePrinter, NULL);
}

/*
 * Callback used to print only available vehicles for a given time interval.
 */
struct AvailabilityData {
    List bookingList;
    long start;
    long end;
};

/*
 * Printer function for available vehicles.
 */
void availableVehiclePrinter(const char* key, void* value, void* userData) {
    Vehicle* v = (Vehicle*)value;
    struct AvailabilityData* data = (struct AvailabilityData*)userData;

    if (isVehicleAvailable(data->bookingList, v->plate, data->start, data->end)) {
        printVehicle(v);
    }
}

/*
 * Prints all vehicles that are available between the given start and end timestamps.
 */
void printAvailableVehiclesAt(HashTable* table, List bookingList, long start, long end) {
    printf("\nAvailable vehicles from selected period:\n");
    struct AvailabilityData data = { bookingList, start, end };
    forEachHash(table, availableVehiclePrinter, &data);
}
