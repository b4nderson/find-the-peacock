#include "raylib.h"

#ifndef TYPES_H
#define TYPES_H

#define DATABASE_PATH "src/database.bin"

#define TIMER 180

#define MAX_STRING_LENGTH 30
#define MAX_INPUT_CHARS 9

typedef struct
{
    int score;
    char nickname[MAX_INPUT_CHARS + 1];
} User;

typedef struct
{
    int length;
    User *users;
} Data;

typedef struct
{
    bool success;
    char message[MAX_STRING_LENGTH];
} Status;

typedef struct
{
    Rectangle wall[600];
    Rectangle blank[600];

    int wallLength;
    int blankLength;
} Maze;

typedef struct
{
    Texture2D reddown;
    Texture2D redup;
    Texture2D redright;
    Texture2D redleft;
    Texture2D redidle;
    Texture2D clockicon;
    Texture2D cavefloor;
    Texture2D cavewall;
    Texture2D peacock;
} Textures;

typedef struct
{
    Sound fanfare;
    Sound ominous;
} Sounds;

#endif