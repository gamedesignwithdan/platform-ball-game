#include "include/raylib.h"
#include <stdlib.h>
#include <math.h>

typedef struct
{
    int x;
    int y;
    float size;
    int velocity;
} Ball;

typedef struct
{
    int x;
    int y;
    int width;
    int height;
} Platform;

int ball_on_platform(Ball ball, Platform platforms[], int platform_count)
{
    for (int i = 0; i < platform_count; i++)
    {
        Rectangle platform_rec = {
            .x = platforms[i].x,
            .y = platforms[i].y,
            .width = platforms[i].width,
            .height = platforms[i].height};

        Rectangle ball_rec = {
            .x = ball.x - ball.size + 20,
            .y = ball.y - ball.size,
            .width = ball.size * 2 - 40,
            .height = ball.size * 2 + 1,
        };

        if (CheckCollisionRecs(ball_rec, platform_rec))
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    int window_width = 800;
    int window_height = 600;

    Ball ball = {
        .x = window_width / 2,
        .y = window_height / 2,
        .size = 40.0,
        .velocity = 4,
    };

    int gravity = 2;

    Platform platforms[3];

    platforms[0].x = 0;
    platforms[0].y = window_height - 10;
    platforms[0].width = window_width;
    platforms[0].height = 10;

    platforms[1].x = fabs(window_width * 0.1);
    platforms[1].y = fabs(window_height * 0.7);
    platforms[1].width = fabs(window_width * 0.2);
    platforms[1].height = fabs(window_height * 0.05);

    platforms[2].x = fabs(window_width * 0.3);
    platforms[2].y = fabs(window_height * 0.5);
    platforms[2].width = fabs(window_width * 0.3);
    platforms[2].height = fabs(window_height * 0.05);

    int platform_count = sizeof(platforms) / sizeof(Platform);

    InitWindow(window_width, window_height, "My Game");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ball.y += ball.velocity;
        ball.velocity += gravity;

        int current_platform = ball_on_platform(ball, platforms, platform_count);
        if (current_platform != -1)
        {
            if (ball.velocity > 0)
            {
                ball.velocity = 0;
                ball.y = platforms[current_platform].y - ball.size;
            }

            if (IsKeyPressed(KEY_SPACE))
            {
                ball.velocity = -30;
            }
        }

        if (IsKeyDown(KEY_LEFT))
        {
            ball.x -= 4;
        }

        if (IsKeyDown(KEY_RIGHT))
        {
            ball.x += 4;
        }

        ClearBackground(WHITE);

        for (int i = 0; i < platform_count; i++)
        {
            DrawRectangle(
                platforms[i].x,
                platforms[i].y,
                platforms[i].width,
                platforms[i].height,
                BLACK);
        }

        DrawCircle(ball.x, ball.y, ball.size, RED);

        EndDrawing();
    }
    return 0;
}
