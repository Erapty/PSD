#ifndef CLIENT_H
#define CLIENT_H

#include "hash.h"
#include "list.h"

/*
 * Displays the client interface menu.
 * Allows a user to log in (or register), view available vehicles,
 * create bookings, and view their booking history.
 *
 * vehicleTable: hash table containing all vehicles
 * userTable: hash table containing all users
 * bookingList: list of all bookings
 */
void clientMenu(HashTable* vehicleTable, HashTable* userTable, List bookingList);

#endif
