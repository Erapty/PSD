#include "list.h"
#include <stdlib.h>

#define FILE_NAME "users.dat"

typedef struct User
{
    char Username[30];
    char Password[30];
} *User;

// Reads the users data file and adds all the users in a list
// TODO: If we end up doing binary search trees, replace the list with one of those
List ImportUsersFromFile()
{
    List UsersList = CreateList();
    FILE *UsersFile = fopen(FILE_NAME, "rb");

    User *NewUser = malloc(sizeof(User));
    if (UsersFile != NULL)
    {
        while (fread(&NewUser, sizeof(User), 1, UsersFile) == 1)
        {
            InsertValue(UsersList, NewUser);
        }
    }
    return UsersList;
}

// Writes every user back into the data file.
// Note that this overwrites the original file and frees the Users List as this is meant to be called at the end of the program's lifetime
void ExportUsersToFile(List UsersList)
{
    FILE *UsersFile = fopen(FILE_NAME, "wb");
    for (int i = 0; i < GetSize(UsersList); i++)
    {
        User *User = GetItem(UsersList, 0);
        DeleteValue(UsersFile, 0);
        fwrite(User, sizeof(User), 1, UsersFile);
    }
    free(UsersList);
    return;
}
