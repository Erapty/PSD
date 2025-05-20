#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        printf("Welcome back, %s %s!\n", firstName, lastName);
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
                // Request availability range
                char datetime[32];
                int duration;
                printf("Enter desired start date (YYYY-MM-DD HH): ");
                fgets(datetime, sizeof(datetime), stdin);
                datetime[strcspn(datetime, "\n")] = 0;
                printf("Enter duration in hours: ");
                scanf("%d", &duration); getchar();

                long start = convertToTimestamp(datetime);
                long end = start + duration;
                printAvailableVehiclesAt(vehicleTable, bookingList, start, end);
                break;
            }
            case 2:
                createBookingPrompt(vehicleTable, bookingList, username);
                break;
            case 3:
                printUserBookings(bookingList, username);
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
