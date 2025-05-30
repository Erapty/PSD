#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "client.h"
#include "vehicle.h"
#include "user.h"
#include "booking.h"
#include "timeutils.h"

/*
 * File: client.c
 * --------------
 * Implements the client interface of the car sharing system.
 * Handles user login/creation and provides options for viewing vehicles,
 * creating bookings, and viewing personal booking history.
 */

/*
 * Function: clientMenu
 * --------------------
 * Displays the client menu and processes user input to view available
 * vehicles, make bookings, and view personal bookings. Automatically
 * registers a new user if not found.
 *
 * vehicleTable: hash table containing all vehicles
 * userTable: hash table containing all users
 * bookingList: list of all bookings
 */
void clientMenu(HashTable* vehicleTable, HashTable* userTable, List bookingList) {
    char firstName[50], lastName[50];

    // Client login
    printf("\n\t=== CLIENT LOGIN ===\n");
    printf("Enter your first name: ");
    fgets(firstName, sizeof(firstName), stdin);
    strtok(firstName, "\n");  // Remove newline

    printf("Enter your last name: ");
    fgets(lastName, sizeof(lastName), stdin);
    strtok(lastName, "\n");

    // Generate username and check existence
    char* username = generateUsername(firstName, lastName);
    User* user = findUser(userTable, username);
    if (!user) {
        printf("New user. Creating your account...\n");
        user = createUser(username, firstName, lastName);
        insertUser(userTable, user);
    } else {
        printf("Welcome back, %s %s!\n", getUserFirstName(user), getUserLastName(user));
    }

    int choice;
    do {
        printf("\n\t=== CLIENT MENU ===\n");
        printf("\t1. View available vehicles\n");
        printf("\t2. Make a booking\n");
        printf("\t3. View your bookings\n");
        printf("\t0. Log out\n");
        printf("\tEnter your choice: ");
        scanf("%d", &choice); getchar();  // Flush newline

        switch (choice) {
            case 1: {
                printf("\n=== AVAILABLE VEHICLES RIGHT NOW ===\n\n");
                long now = time(NULL);
                printAvailableVehiclesAt(vehicleTable, bookingList, now, now + 3600);
                printf("\n");
                break;
            }
            case 2:
                printf("\n\t=== MAKE A BOOKING ===\n\n");
                createBookingPrompt(vehicleTable, bookingList, username);
                printf("\n");
                break;
            case 3:
                printf("\n\t=== YOUR BOOKINGS ===\n\n");
                printUserBookings(bookingList, username);
                printf("\n");
                break;
            case 0:
                printf("\tLogging out...\n");
                break;
            default:
                printf("\tInvalid choice. Please try again.\n");
        }

    } while (choice != 0);

    free(username);
}
