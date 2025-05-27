#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "admin.h"
#include "client.h"
#include "storage.h"
#include "hash.h"
#include "list.h"
#include "vehicle.h"
#include "user.h"
#include "booking.h"

/*
 * File: main.c
 * ------------
 * Entry point for the car sharing system.
 * Initializes data structures, loads data from files, and provides
 * the main menu for selecting between admin and client interfaces.
 */

int main() {
    
    // Initialize data structures
    HashTable* vehicleTable = createHashTable();
    HashTable* userTable = createHashTable();
    List bookingList = createList();

    
    // Load data from files
    LoadVehiclesFromFile(vehicleTable, "vehicles.txt");
    LoadUsersFromFile(userTable, "users.txt");
    LoadBookingsFromFile(bookingList, "bookings.txt", vehicleTable, userTable);
    
    int choice;
    

    // Main program loop
   do {
        printf("Welcome to the Car Sharing System\n");
        printf("1. Admin Login\n");
        printf("2. Client Login\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // flush newline

        switch (choice) {
            case 1:
                adminMenu(vehicleTable, userTable, bookingList);
                break;
            case 2:
                clientMenu(vehicleTable, userTable, bookingList);
                break;
            case 0:
                printf("Saving data and exiting...\n");
                SaveVehiclesToFile(vehicleTable, "vehicles.txt");
                SaveUsersToFile(userTable, "users.txt");
                SaveBookingsToFile(bookingList, "bookings.txt");
                choice = 0;
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }while (choice != 0);

    // Free memory
    freeHashTable(vehicleTable);
    freeHashTable(userTable);
    freeList(bookingList);

    return 0;
}
