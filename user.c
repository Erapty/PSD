#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "user.h"
#include "hash.h"

/*
 * File: user.c
 * ------------
 * Implements the User data structure and related operations.
 * Includes creation, accessors (getters), and interaction with a hash table.
 */

// Internal structure of a User
struct User {
    char* username;
    char* firstName;
    char* lastName;
};

/*
 * Allocates and initializes a new User with the given data.
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
 * Frees the memory allocated for a User instance.
 */
void freeUser(User* user) {
    if (!user) return;
    free(user->username);
    free(user->firstName);
    free(user->lastName);
    free(user);
}

/* === GETTER FUNCTIONS === */

/*
 * Returns the user's username.
 */
const char* getUserUsername(const User* user) {
    return user->username;
}

/*
 * Returns the user's first name.
 */
const char* getUserFirstName(const User* user) {
    return user->firstName;
}

/*
 * Returns the user's last name.
 */
const char* getUserLastName(const User* user) {
    return user->lastName;
}

/*
 * Generates a username by combining first name and last name with an underscore.
 * Memory must be freed by the caller.
 *
 * returns: dynamically allocated username string
 */
char* generateUsername(const char* firstName, const char* lastName) {
    char* username = malloc(100);
    snprintf(username, 100, "%s_%s", firstName, lastName);
    return username;
}

/*
 * Inserts a User into the given hash table using the username as key.
 */
void insertUser(HashTable* table, User* user) {
    insertHashTable(table, user->username, user);
}

/*
 * Finds a user in the hash table by username.
 *
 * returns: pointer to User if found, NULL otherwise
 */
User* findUser(HashTable* table, const char* username) {
    return (User*)searchHashTable(table, username);
}

void userPrinter(const char* key, void* value, void* unused) {
    User* u = (User*)value;
    printUser(u);
}

/*
 * Prints the details of a single user.
 */
void printUser(const User* user) {
    printf("Username: %s | Name: %s %s\n", user->username, user->firstName, user->lastName);
}

/*
 * Prints all users stored in the hash table.
 */
void printAllUsers(HashTable* table) {
    forEachHash(table, userPrinter, NULL);
}
