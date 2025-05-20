#ifndef ADMIN_H
#define ADMIN_H

#include "hash.h"
#include "list.h"

/*
 * Displays the admin interface menu and handles admin operations,
 * including managing vehicles, users, and bookings.
 *
 * vehicleTable: hash table containing all vehicles
 * userTable: hash table containing all users
 * bookingList: list of all bookings
 */
void adminMenu(HashTable* vehicleTable, HashTable* userTable, List bookingList);

#endif
