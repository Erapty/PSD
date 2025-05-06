#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "vehicle.h"
#include "booking.h"
#include "storage.h"
#include "client.h"
#include "admin.h"

// Function to display the main menu
void displayMainMenu() {
    printf("\n--- Main Menu ---\n");
    printf("1. Admin Login\n");
    printf("2. Client Login\n");
    printf("3. Exit\n");
    printf("Please select an option: ");
}

// Function to display the login menu for admin
int adminLogin() {
    char password[20];
    printf("Enter admin password: ");
    scanf("%s", password);
    return strcmp(password, "1234") == 0;
}

// Function to display the login menu for client
void clientLogin(char* username) {
    printf("Enter your username: ");
    scanf("%s", username);
}

int main() {
    List vehicles, bookings;
    createList(&vehicles);
    createList(&bookings);

    loadVehicles(&vehicles);
    loadBookings(&bookings);

    int option;
    char username[50];

    while (1) {
        displayMainMenu();
        scanf("%d", &option);

        switch (option) {
            case 1:
                if (adminLogin()) {
                    adminMenu(&vehicles, &bookings);
                } else {
                    printf("Invalid admin password!\n");
                }
                break;

            case 2:
                clientLogin(username);
                clientMenu(username, &vehicles, &bookings);
                break;

            case 3:
                saveVehicles(&vehicles);
                saveBookings(&bookings);
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid option! Please try again.\n");
        }
    }

    return 0;
}
