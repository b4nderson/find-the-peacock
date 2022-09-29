#include <stdbool.h>
#include <string.h>

#include "raylib.h"
#include "database.h"
#include "screen.h"
#include "util.h"
#include "types.h"

int main()
{
    const int screenWidth = 1035;
    const int screenHeight = 750;

    InitWindow(screenWidth, screenHeight, "Find the peacock");
    InitAudioDevice();

    const Textures textures = {
        LoadTexture("./assets/images/RedDown.png"),
        LoadTexture("./assets/images/RedUp.png"),
        LoadTexture("./assets/images/RedRight.png"),
        LoadTexture("./assets/images/RedLeft.png"),
        LoadTexture("./assets/images/RedIdle.png"),
        LoadTexture("./assets/images/clock.png"),
        LoadTexture("./assets/images/cavefloor.png"),
        LoadTexture("./assets/images/cavewall.png"),
        LoadTexture("assets/images/peacock.png")};

    const Sounds sounds = {
        LoadSound("./assets/sounds/ominous.wav"),
        LoadSound("./assets/sounds/fanfare.wav")};

    SetSoundVolume(sounds.fanfare, 0.2f);
    SetSoundVolume(sounds.ominous, 0.2f);

    SetTargetFPS(60);

    char nickname[MAX_INPUT_CHARS + 1] = "\0";

    bool mouseOnText = false;

    int letterCount = 0;
    int letterFramesCounter = 0;

    Rectangle textBox = {screenWidth / 2.0f - 100, 400, 225, 50};

    Maze maze = createMaze();
    Vector2 character = {maze.blank[0].x + 10, maze.blank[0].y + 20};

    int clockPosition = GetRandomValue(1, maze.blankLength);

    Rectangle clock = {
        maze.blank[clockPosition].x + 5,
        maze.blank[clockPosition].y + 5,
        20,
        20};

    bool win = false;
    bool startedGame = false;

    int attempts = 0;
    int frame = 0;

    int timer = TIMER;

    float framewidth = (float)(textures.reddown.width / 3);

    int maxframe = (textures.reddown.width / framewidth);

    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(GRAY);

        if (!startedGame)
        {

            mouseOnText = CheckCollisionPointRec(GetMousePosition(), textBox);

            if (mouseOnText)
            {
                SetMouseCursor(MOUSE_CURSOR_IBEAM);

                int key = GetCharPressed();

                while (key > 0)
                {
                    if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                    {
                        nickname[letterCount] = (char)key;
                        nickname[letterCount + 1] = '\0';

                        letterCount++;
                    }

                    key = GetCharPressed();
                }

                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    letterCount--;

                    if (letterCount < 0)
                    {
                        letterCount = 0;
                    }

                    nickname[letterCount] = '\0';
                }

                letterFramesCounter++;
            }
            else
            {
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);

                letterFramesCounter = 0;
            }

            if (letterCount == MAX_INPUT_CHARS)
            {
                User user;

                user.score = 0;

                strcpy(user.nickname, nickname);

                createUser(user);

                startedGame = true;

                attempts++;
            }

            PlaySoundMulti(sounds.fanfare);
            initialView(textures.peacock, textBox, mouseOnText, nickname, letterCount, letterFramesCounter);
        }
        else
        {
            if (!win && timer > 0)
            {
                timer = TIMER * attempts;
                timer -= GetTime();

                frame = frame % maxframe;

                StopSound(sounds.fanfare);
                PlaySoundMulti(sounds.ominous);

                clockView(timer);
                win = gameView(textures, maze, &character, clock, frame, framewidth);
            }
            else
            {
                StopSound(sounds.ominous);
                PlaySoundMulti(sounds.fanfare);

                User user = getUser(nickname);

                if (user.score < timer * 100)
                {
                    user.score = timer * 100;

                    strcpy(user.nickname, nickname);
                    updateUser(nickname, user);
                }

                Data data = getOrdenaredUsersByTime();

                scoreAndRankingView(win, timer * 100, attempts, data);

                if (IsKeyDown(KEY_ENTER))
                {
                    if (attempts < 3)
                    {
                        win = false;
                        startedGame = false;

                        timer = TIMER;

                        frame = 0;

                        character.x = maze.blank[0].x + 10;
                        character.y = maze.blank[0].y + 20;
                    }
                }
            }
        }

        EndDrawing();
    }

    StopSoundMulti();

    UnloadSound(sounds.fanfare);
    UnloadSound(sounds.ominous);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}