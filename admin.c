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
        printf("\n=== ADMIN MENU ===\n");
        printf("1. Add vehicle\n");
        printf("2. Remove vehicle\n");
        printf("3. View all vehicles\n");
        printf("4. View all users\n");
        printf("5. View all bookings\n");
        printf("0. Log out\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); getchar(); // Consume newline

        switch (choice) {
            case 1: 
                addVehiclePrompt(vehicleTable); 
                break;
            case 2: 
                removeVehiclePrompt(vehicleTable); 
                break;
            case 3: 
                printAllVehicles(vehicleTable); 
                break;
            case 4: 
                printAllUsers(userTable); 
                break;
            case 5: 
                printAllBookings(bookingList); 
                break;
            case 0: 
                printf("Logging out...\n"); 
                break;
            default: 
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);
}
