#ifndef USER_H
#define USER_H

#include "hash.h"

// Opaque declaration of the User structure
typedef struct User User;

/* === Creation & Management === */

/*
 * Creates a new User object.
 *
 * username: unique identifier
 * firstName: user's first name
 * lastName: user's last name
 *
 * returns: pointer to the new User
 */
User* createUser(const char* username, const char* firstName, const char* lastName);

/*
 * Frees memory allocated for a User.
 */
void freeUser(User* user);

/* === Accessors (Getters) === */

/*
 * Returns the username of the user.
 */
const char* getUserUsername(const User* user);

/*
 * Returns the first name of the user.
 */
const char* getUserFirstName(const User* user);

/*
 * Returns the last name of the user.
 */
const char* getUserLastName(const User* user);

/* === Username Utility === */

/*
 * Generates a simple username in the format "first_last".
 * The returned string must be freed by the caller.
 */
char* generateUsername(const char* firstName, const char* lastName);

/* === Hash Table Operations === */

/*
 * Inserts a User into a hash table.
 */
void insertUser(HashTable* table, User* user);

/*
 * Searches for a User in the hash table by username.
 *
 * returns: pointer to the User if found, NULL otherwise
 */
User* findUser(HashTable* table, const char* username);

/* === Debug / Admin Output === */

/*
 * Prints information about a single user.
 */
void printUser(const User* user);

/*
 * Prints all users stored in the hash table.
 */
void printAllUsers(HashTable* table);

#endif
