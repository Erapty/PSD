#ifndef STORAGE_H
#define STORAGE_H

#include "hash.h"
#include "list.h"

/*
 * Loads vehicle data from a file and inserts each vehicle into the hash table.
 *
 * table: hash table where the vehicles will be stored
 * filename: path to the input file
 */
void LoadVehiclesFromFile(HashTable* table, const char* filename);

/*
 * Loads user data from a file and inserts each user into the hash table.
 *
 * table: hash table where the users will be stored
 * filename: path to the input file
 */
void LoadUsersFromFile(HashTable* table, const char* filename);

/*
 * Loads booking data from a file and inserts each booking into the list.
 *
 * list: list where bookings will be stored
 * filename: path to the input file
 * vehicleTable: hash table used to retrieve vehicle references
 * userTable: hash table used to retrieve user references (optional)
 */
void LoadBookingsFromFile(List list, const char* filename, HashTable* vehicleTable, HashTable* userTable);

/*
 * Saves all vehicles in the hash table to a file.
 *
 * table: hash table containing the vehicles
 * filename: path to the output file
 */
void SaveVehiclesToFile(HashTable* table, const char* filename);

/*
 * Saves all users in the hash table to a file.
 *
 * table: hash table containing the users
 * filename: path to the output file
 */
void SaveUsersToFile(HashTable* table, const char* filename);

/*
 * Saves all bookings in the list to a file.
 *
 * list: list containing bookings
 * filename: path to the output file
 */
void SaveBookingsToFile(List list, const char* filename);

#endif
