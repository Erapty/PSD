#include <stdio.h>
#include <stdlib.h>
#include "admin.h"
#include "vehicle.h"
#include "user.h"
#include "booking.h"

/*
 * File: admin.c
 * -------------
 * Provides the admin interface for managing vehicles, users, and bookings.
 * This file contains the adminMenu function that serves as the entry point 
 * for all administrator operations.
 */

/*
 * Function: adminMenu
 * -------------------
 * Displays the admin menu and handles user input to manage the system.
 * Allows the admin to add or remove vehicles, view all vehicles, users,
 * and bookings.
 *
 * vehicleTable: hash table containing all vehicles
 * userTable: hash table containing all users
 * bookingList: list of all bookings
 */
 void adminMenu(HashTable* vehicleTable, HashTable* userTable, List bookingList) {
    int choice;
    do {
        printf("\n\t=== ADMIN MENU ===\n\n");
        printf("\t1. Add a new vehicle\n");
        printf("\t2. Remove a vehicle\n");
        printf("\t3. View all vehicles\n");
        printf("\t4. View all users\n");
        printf("\t5. View all bookings\n");
        printf("\t0. Exit admin mode\n\n");
        printf("\tEnter your choice: ");
        scanf("%d", &choice); getchar();

        switch (choice) {
            case 1:
                printf("\n\t--- ADD VEHICLE ---\n\n");
                addVehiclePrompt(vehicleTable);
                printf("\n");
                break;

            case 2:
                printf("\n\t--- REMOVE VEHICLE ---\n\n");
                removeVehiclePrompt(vehicleTable);
                printf("\n");
                break;

            case 3:
                printf("\n\t--- ALL VEHICLES ---\n\n");
                if (vehicleTable) {
                    printAllVehicles(vehicleTable);
                } else {
                    printf("\tNo vehicles found.\n");
                }
                printf("\n");
                break;

            case 4:
                printf("\n\t--- ALL USERS ---\n\n");
                if (userTable) {
                    printAllUsers(userTable);
                } else {
                    printf("\tNo users found.\n");
                }
                printf("\n");
                break;

            case 5:
                printf("\n\t--- ALL BOOKINGS ---\n\n");
                if (getSize(bookingList) > 0) {
                    printAllBookings(bookingList);
                } else {
                    printf("No bookings found.\n");
                }
                printf("\n");
                break;

            case 0:
                printf("\n\tExiting admin mode...\n\n");
                break;

            default:
                printf("\n\tInvalid choice. Please try again.\n\n");
        }

    } while (choice != 0);
}