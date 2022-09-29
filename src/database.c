#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "util.h"
#include "types.h"

FILE *getConnection(char *operation)
{
    FILE *file = fopen(DATABASE_PATH, operation);

    if (!file)
    {
        printf("> Houve um problema ao conectar na base de dados!\n");
        exit(1);
    }

    return file;
}

void closeConnection(FILE *database)
{
    fclose(database);
}

Data getUsers()
{
    FILE *database = getConnection("rb");

    fseek(database, 0L, SEEK_END);

    int size = ftell(database) / sizeof(User);

    fseek(database, 0L, SEEK_SET);

    User *users = (User *)malloc(sizeof(User) * size);

    fread(users, sizeof(User), size, database);

    closeConnection(database);

    Data data = {size, users};

    return data;
}

Data getOrdenaredUsersByTime()
{
    Data data = getUsers();

    qsort(data.users, data.length, sizeof(User), descompare);

    return data;
}

Status userExists(char nickname[])
{
    FILE *database = getConnection("rb");

    User user;

    Status status = {false, "User does not exists!"};

    while (!feof(database))
    {
        fread(&user, sizeof(User), 1, database);

        if (strcmp(user.nickname, nickname) == 0)
        {
            status.success = true;
            strcpy(status.message, "User already exists!");

            break;
        }
    }

    closeConnection(database);

    return status;
}

User getUser(char nickname[])
{
    FILE *database = getConnection("rb");

    User user;

    while (!feof(database))
    {
        fread(&user, sizeof(User), 1, database);

        if (strcmp(user.nickname, nickname) == 0)
        {
            closeConnection(database);

            return user;
        }
    }
}

Status createUser(User user)
{
    Status userStatus = userExists(user.nickname);

    Status status = {false, "User already exists!"};

    if (userStatus.success)
    {
        return status;
    }

    FILE *database = getConnection("ab");

    printf("%s", user.nickname);

    fwrite(&user, sizeof(User), 1, database);

    closeConnection(database);

    status.success = true;
    strcpy(status.message, "User created successfuly!");

    return status;
}

Status updateUser(char nickname[], User data)
{
    FILE *database = getConnection("r+b");

    User user;

    Status status = {false, "User does not exists!"};

    while (!feof(database))
    {
        fread(&user, sizeof(User), 1, database);

        if (strcmp(user.nickname, nickname) == 0)
        {
            status.success = true;
            strcpy(status.message, "User updated successfuly!");

            fseek(database, -sizeof(User), SEEK_CUR);
            fwrite(&data, sizeof(User), 1, database);

            break;
        }
    }

    closeConnection(database);

    return status;
}