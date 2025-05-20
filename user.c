#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "user.h"
#include "hash.h"

/*
 * File: user.c
 * ------------
 * Manages user-related operations in the car sharing system.
 * Handles creation, lookup, insertion, and display of user records.
 */

// Internal structure representing a user
struct User {
    char* username;
    char* firstName;
    char* lastName;
};

/*
 * Function: createUser
 * --------------------
 * Allocates and initializes a new User instance with the given data.
 *
 * username: unique identifier for the user
 * firstName: user's first name
 * lastName: user's last name
 *
 * returns: pointer to the new User
 */
User* createUser(const char* username, const char* firstName, const char* lastName) {
    User* user = malloc(sizeof(User));
    if (!user) return NULL;

    user->username = strdup(username);
    user->firstName = strdup(firstName);
    user->lastName = strdup(lastName);
    return user;
}

/*
 * Function: freeUser
 * ------------------
 * Frees all memory allocated for a User instance.
 *
 * user: pointer to the User to be freed
 */
void freeUser(User* user) {
    if (!user) return;
    free(user->username);
    free(user->firstName);
    free(user->lastName);
    free(user);
}

/*
 * Function: generateUsername
 * --------------------------
 * Generates a simple username by concatenating first and last name
 * with an underscore. Memory must be freed by the caller.
 *
 * firstName: user's first name
 * lastName: user's last name
 *
 * returns: dynamically allocated string representing the username
 */
char* generateUsername(const char* firstName, const char* lastName) {
    char* username = malloc(100);
    snprintf(username, 100, "%s_%s", firstName, lastName);
    return username;
}

/*
 * Function: insertUser
 * --------------------
 * Inserts a User into the user hash table using their username as the key.
 *
 * table: hash table where the user will be stored
 * user: pointer to the User to insert
 */
void insertUser(HashTable* table, User* user) {
    insertHashTable(table, user->username, user);
}

/*
 * Function: findUser
 * ------------------
 * Retrieves a User from the hash table by their username.
 *
 * table: hash table to search in
 * username: the username to look up
 *
 * returns: pointer to the User if found, NULL otherwise
 */
User* findUser(HashTable* table, const char* username) {
    return (User*)searchHashTable(table, username);
}

/*
 * Function: printUser
 * -------------------
 * Prints the basic information of a single user.
 *
 * user: pointer to the User to display
 */
void printUser(const User* user) {
    printf("Username: %s | Name: %s %s\n", user->username, user->firstName, user->lastName);
}

/*
 * Function: printAllUsers
 * -----------------------
 * Iterates through the user hash table and prints all registered users.
 *
 * table: hash table containing user data
 */
void printAllUsers(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* node = table->table[i];
        while (node) {
            printUser((User*)node->value);
            node = node->next;
        }
    }
}
