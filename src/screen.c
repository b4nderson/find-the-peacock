#include <stdbool.h>

#include <stdio.h>
#include "raylib.h"
#include "util.h"
#include "types.h"

void initialView(Texture2D logo, Rectangle textBox, bool mouseOnText, char *nickname, int letterCount, int framesCounter)
{

    ClearBackground(RAYWHITE);

    DrawText("Find the Peacock", 100, 140, 70, RED);
    DrawTexture(logo, 750, 120, RAYWHITE);

    DrawText("COLOQUE O MOUSE SOBRE A CAIXA DE ENTRADA!", 270, 360, 20, GRAY);

    DrawRectangleRec(textBox, LIGHTGRAY);

    if (mouseOnText)
    {
        DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
    }
    else
    {
        DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
    }

    DrawText(nickname, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
    DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 430, 480, 20, DARKGRAY);
}

void scoreAndRankingView(bool win, int score, int attempts, Data data)
{
    ClearBackground(WHITE);

    DrawText(win ? "Você ganhou!" : "Você perdeu!", 350, 45, 50, win ? GREEN : RED);

    DrawText("Pontuação: ", 390, 120, 30, win ? GREEN : RED);
    DrawText(TextFormat("%d", score), 565, 120, 30, win ? GREEN : RED);

    if (attempts < 3)
    {
        DrawText("'ENTER' PARA TENTAR NOVAMENTE!", 320, 180, 20, GRAY);
    }
    else
    {
        DrawText("SUAS CHANCES ACABARAM! FECHE O JOGO!", 310, 180, 20, GRAY);
    }

    DrawText("Ranking: ", 120, 220, 50, win ? GREEN : RED);
    DrawText(TextFormat("Tentativas: %d", attempts), 770, 230, 20, win ? GREEN : RED);

    DrawRectangle(120, 300, 10, 420, win ? GREEN : RED);
    DrawRectangle(120, 300, 780, 10, win ? GREEN : RED);
    DrawRectangle(900, 300, 10, 420, win ? GREEN : RED);
    DrawRectangle(120, 720, 790, 10, win ? GREEN : RED);

    for (int index = 0; index < (data.length < 10 ? data.length : 10); index++)
    {
        DrawText(TextFormat("%d) %s", index + 1, data.users[index].nickname), 150, 320 + index * 40, 20, BLUE);
        DrawText(TextFormat("%d", data.users[index].score), 800, 320 + index * 40, 20, BLUE);

        DrawRectangle(150, 340 + index * 40, 700, 2, BLACK);
    }
}

bool gameView(Textures textures, Maze maze, Vector2 *character, Rectangle clock, int frame, float framewidth)
{

    for (int i = 0; i < 335; i++)
    {
        DrawTexture(textures.cavewall, maze.wall[i].x, maze.wall[i].y, RAYWHITE);
        DrawTexture(textures.clockicon, clock.x, clock.y, RAYWHITE);

        if (i < 265)
        {
            DrawTexture(textures.cavefloor, maze.blank[i].x, maze.blank[i].y, RAYWHITE);
        }

        if (CheckCollisionCircleRec(*character, 10, maze.wall[i]))
        {
            if (character->y < maze.wall[i].y || character->y > maze.wall[i].y + maze.wall[i].width)
            {
                if (character->y > maze.wall[i].y)
                {
                    character->y += 2.0f;
                }
                else if (character->y < maze.wall[i].y)
                {
                    character->y -= 2.0f;
                }
            }
            else if (character->x < maze.wall[i].x || character->x > maze.wall[i].x + maze.wall[i].width)
            {
                if (character->x > maze.wall[i].x)
                {
                    character->x += 2.0f;
                }
                else if (character->x < maze.wall[i].x)
                {
                    character->x -= 2.0f;
                }
            }
        }
    }

    for (int i = 0; i < 335; i++)
    {
        if (sqrt(pow((maze.blank[i].x - character->x), 2) + pow(maze.blank[i].y - character->y, 2)) >= 100)
        {
            DrawRectangle(maze.blank[i].x, maze.blank[i].y, maze.blank[i].width, maze.blank[i].height, BLACK);
        }
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        character->x += 2.0f;

        DrawTextureRec(textures.redright, (Rectangle){(framewidth * frame), 0, framewidth, (float)textures.reddown.height}, (Vector2){character->x - 10, character->y - 17}, RAYWHITE);
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        character->x -= 2.0f;

        DrawTextureRec(textures.redleft, (Rectangle){(framewidth * frame), 0, framewidth, (float)textures.reddown.height}, (Vector2){character->x - 10, character->y - 17}, RAYWHITE);
    }
    else if (IsKeyDown(KEY_UP))
    {
        character->y -= 2.0f;

        DrawTextureRec(textures.redup, (Rectangle){(framewidth * frame), 0, framewidth, (float)textures.reddown.height}, (Vector2){character->x - 10, character->y - 17}, RAYWHITE);
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        character->y += 2.0f;

        DrawTextureRec(textures.reddown, (Rectangle){(framewidth * frame), 0, framewidth, (float)textures.reddown.height}, (Vector2){character->x - 10, character->y - 17}, RAYWHITE);
    }
    else
    {
        DrawTextureRec(textures.redidle, (Rectangle){0, 0, (float)textures.redidle.width, (float)textures.redidle.height}, (Vector2){character->x - 10, character->y - 17}, RAYWHITE);
    }

    return CheckCollisionCircleRec(*character, 10, clock);
}

void clockView(int timer)
{
    DrawText(TextFormat("%02d:%02d", timer / 60, timer % 60), 470, 40, 40, BLACK);
}
