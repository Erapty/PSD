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
        printf("\n=== ADMIN MENU ===\n\n");
        printf("1. Add a new vehicle\n");
        printf("2. Remove a vehicle\n");
        printf("3. View all vehicles\n");
        printf("4. View all users\n");
        printf("5. View all bookings\n");
        printf("0. Exit admin mode\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); getchar();

        switch (choice) {
            case 1:
                printf("\n--- ADD VEHICLE ---\n\n");
                addVehiclePrompt(vehicleTable);
                printf("\n");
                break;

            case 2:
                printf("\n--- REMOVE VEHICLE ---\n\n");
                removeVehiclePrompt(vehicleTable);
                printf("\n");
                break;

            case 3:
                printf("\n--- ALL VEHICLES ---\n\n");
                if (vehicleTable) {
                    printAllVehicles(vehicleTable);
                } else {
                    printf("No vehicles found.\n");
                }
                printf("\n");
                break;

            case 4:
                printf("\n--- ALL USERS ---\n\n");
                if (userTable) {
                    printAllUsers(userTable);
                } else {
                    printf("No users found.\n");
                }
                printf("\n");
                break;

            case 5:
                printf("\n--- ALL BOOKINGS ---\n\n");
                if (getSize(bookingList) > 0) {
                    printAllBookings(bookingList);
                } else {
                    printf("No bookings found.\n");
                }
                printf("\n");
                break;

            case 0:
                printf("\nExiting admin mode...\n\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n\n");
        }

    } while (choice != 0);
}