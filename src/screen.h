#include <stdbool.h>

#include "raylib.h"
#include "types.h"

#ifndef SCREEN_H
#define SCREEN_H

void initialView(Texture2D logo, Rectangle textbox, bool mouseOnText, char *nickname, int letterCount, int framesCounter);
void clockView(int timer);
bool gameView(Textures textures, Maze maze, Vector2 *character, Rectangle clock, int frame, float framewidth);
void scoreAndRankingView(bool win, int score, int attempts, Data data);

#endif