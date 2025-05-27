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
    printf("\n=== CLIENT LOGIN ===\n");
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
        printf("\n=== CLIENT MENU ===\n");
        printf("1. View available vehicles\n");
        printf("2. Make a booking\n");
        printf("3. View your bookings\n");
        printf("0. Log out\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); getchar();  // Flush newline

        switch (choice) {
            case 1: {
                printf("\n=== AVAILABLE VEHICLES RIGHT NOW ===\n\n");
                long now = time(NULL) / 3600;
                printAvailableVehiclesAt(vehicleTable, bookingList, now, now + 1);
                printf("\n");
                break;
            }
            case 2:
                printf("\n=== MAKE A BOOKING ===\n\n");
                createBookingPrompt(vehicleTable, bookingList, username);
                printf("\n");
                break;
            case 3:
                printf("\n=== YOUR BOOKINGS ===\n\n");
                printUserBookings(bookingList, username);
                printf("\n");
                break;
            case 0:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    free(username);
}
