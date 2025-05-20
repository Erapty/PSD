#ifndef USER_H
#define USER_H

#include "hash.h"

// Opaque declaration of the User structure
typedef struct User User;

/*
 * Creates a new User instance with the provided username, first name, and last name.
 *
 * username: unique identifier for the user
 * firstName: user's first name
 * lastName: user's last name
 *
 * returns: pointer to the new User
 */
User* createUser(const char* username, const char* firstName, const char* lastName);

/*
 * Frees memory allocated for a User instance.
 *
 * user: pointer to the User to free
 */
void freeUser(User* user);

/*
 * Generates a username from a user's first and last name.
 * Format: first_last. Memory must be freed by the caller.
 *
 * firstName: user's first name
 * lastName: user's last name
 *
 * returns: dynamically allocated string containing the username
 */
char* generateUsername(const char* firstName, const char* lastName);

/*
 * Inserts a User into the hash table using the username as the key.
 *
 * table: hash table where the user will be inserted
 * user: pointer to the User to insert
 */
void insertUser(HashTable* table, User* user);

/*
 * Searches for a user in the hash table by username.
 *
 * table: hash table to search in
 * username: the username to find
 *
 * returns: pointer to the User if found, NULL otherwise
 */
User* findUser(HashTable* table, const char* username);

/*
 * Prints the details of a single user.
 *
 * user: pointer to the User to print
 */
void printUser(const User* user);

/*
 * Prints all users stored in the hash table.
 *
 * table: hash table containing users
 */
void printAllUsers(HashTable* table);

#endif
