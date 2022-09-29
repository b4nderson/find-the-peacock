#include "types.h"

#ifndef DATABASE_H
#define DATABASE_H

Data getUsers();
Data getOrdenaredUsersByTime();
Status userExists(char nickname[]);
User getUser(char nickname[]);
Status createUser(User user);
Status updateUser(char nickname[], User data);

#endif