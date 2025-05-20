#ifndef VEHICLE_H
#define VEHICLE_H

#include "hash.h"
#include "list.h"

// Opaque declaration of the Vehicle structure
typedef struct Vehicle Vehicle;

/*
 * Creates a new vehicle object with the given parameters.
 */
Vehicle* createVehicle(const char* plate, float cost, int seats, const char* type,
                       const char* fuel, const char* brand, const char* model,
                       int year, const char* location);

/*
 * Frees memory allocated for a Vehicle.
 */
void freeVehicle(Vehicle* v);

/*
 * Returns the license plate of the vehicle.
 */
const char* getVehiclePlate(Vehicle* v);

/*
 * Returns the hourly cost of the vehicle.
 */
float getVehicleCost(Vehicle* v);

/*
 * Inserts a vehicle into the hash table.
 */
void insertVehicle(HashTable* table, Vehicle* v);

/*
 * Searches for a vehicle in the hash table by its plate.
 */
Vehicle* findVehicle(HashTable* table, const char* plate);

/*
 * Prompts the admin to input vehicle data and adds it to the system.
 */
void addVehiclePrompt(HashTable* table);

/*
 * Prompts the admin to remove a vehicle from the system.
 */
void removeVehiclePrompt(HashTable* table);

/*
 * Prints the data of a single vehicle.
 */
void printVehicle(const Vehicle* v);

/*
 * Prints all vehicles stored in the system.
 */
void printAllVehicles(HashTable* table);

/*
 * Prints all vehicles available during a specified time range.
 */
void printAvailableVehiclesAt(HashTable* table, List bookingList, long start, long end);

#endif
