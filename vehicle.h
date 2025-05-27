#ifndef VEHICLE_H
#define VEHICLE_H

#include "hash.h"
#include "list.h"

// Opaque declaration of the Vehicle structure
typedef struct Vehicle Vehicle; 

/*
 * Creates a new Vehicle instance with all necessary fields.
 *
 * plate: vehicle license plate
 * cost: hourly rental cost
 * seats: number of seats
 * type: type of vehicle (e.g., car, van)
 * fuel: fuel type (e.g., petrol, diesel)
 * brand: manufacturer brand
 * model: specific model name
 * year: year of manufacture
 * location: city or place where the vehicle is located
 *
 * returns: pointer to the new Vehicle
 */
Vehicle* createVehicle(const char* plate, float cost, int seats, const char* type,
                       const char* fuel, const char* brand, const char* model,
                       int year, const char* location);

/*
 * Frees all memory associated with a Vehicle object.
 */
void freeVehicle(Vehicle* v);

/* === Accessors (Getters) === */

const char* getVehiclePlate(const Vehicle* v);
float getVehicleCost(const Vehicle* v);
int getVehicleSeats(const Vehicle* v);
const char* getVehicleType(const Vehicle* v);
const char* getVehicleFuel(const Vehicle* v);
const char* getVehicleBrand(const Vehicle* v);
const char* getVehicleModel(const Vehicle* v);
int getVehicleYear(const Vehicle* v);
const char* getVehicleLocation(const Vehicle* v);

/* === Hash Table Operations === */

/*
 * Inserts a Vehicle into the hash table.
 */
void insertVehicle(HashTable* table, Vehicle* v);

/*
 * Searches for a Vehicle in the hash table by plate.
 *
 * returns: pointer to the Vehicle if found, NULL otherwise
 */
Vehicle* findVehicle(HashTable* table, const char* plate);

/* === Admin Prompts === */

/*
 * Prompts admin to input vehicle details and inserts it into the table.
 */
void addVehiclePrompt(HashTable* table);

/*
 * Prompts admin to remove a vehicle from the table using its plate.
 */
void removeVehiclePrompt(HashTable* table);

/* === Display Functions === */

/*
 * Prints all details of a single vehicle.
 */
void printVehicle(const Vehicle* v);

/*
 * Prints all vehicles stored in the hash table.
 */
void printAllVehicles(HashTable* table);

/*
 * Prints only vehicles that are available during a given time range.
 */
void printAvailableVehiclesAt(HashTable* table, List bookingList, long start, long end);

#endif
