#include "raylib.h"
#include "iostream"
#include <vector>
#include <array>
using namespace std;

int player_score = 0;
int cpu_score = 0;

class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void draw() {
        DrawCircle(x, y, radius, RED);
    }


    void Update() {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1;

        }
        if (x + radius >= GetScreenWidth())
        {
            cpu_score++;
            ResetBall();
        }
            
        if( x - radius <= 0)
        {
            player_score++;
            ResetBall();
        }

     
    }

    void ResetBall()
    {
        x = GetScreenHeight() / 2;
        y = GetScreenWidth() / 2;
         
        int speed_choices[2] = { -1,1 };
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
   

};

    class Paddle 
    {
    protected:
        void LimitMovement() {

        }
    public:
        float x, y;
        float width, height;
        int speed;

        void draw() {
            DrawRectangle(x, y, width, height, RED);
        }


        void update()
        {
            if (IsKeyDown(KEY_UP))
            {
                y = y - speed;
            }
            if (IsKeyDown(KEY_DOWN))
            {
                y = y + speed;
            }

            if (y <= 0)
            {
                y = 0;

            }
            if (y + height >= GetScreenHeight())
            {
                y = GetScreenHeight() - height;
            }

            LimitMovement();

        }

    };

    class CpuPaddle: public Paddle 
    {
    public:
        void update(int ball_y)
        {
            if (y + height / 2 > ball_y)
            {
                y = y - speed;
            }
            if (y + height / 2 <= ball_y)
            {
                y = y + speed;
            }

            LimitMovement();
        }
    };

    Ball ball;

    Paddle player;
    CpuPaddle cpu;



    int main()
    {
        // random statements 
        const int screen_width = 1280;
        const int screen_height = 800;
        InitWindow(screen_width, screen_height, "uhh jotain");
        SetTargetFPS(60);
        //ball 
        ball.radius = 20;
        ball.x = screen_width / 2;
        ball.y = screen_height / 2;
        ball.speed_x = 7;
        ball.speed_y = 7;
        //paddle 

        player.width = 25;
        player.height = 120;
        player.x = screen_width - player.width - 10;
        player.y = screen_height / 2 - player.width / 2;
        player.speed = 6;

        cpu.height = 120;
        cpu.width = 25;
        cpu.x = 10;
        cpu.y = screen_height / 2 - cpu.height / 2;
        cpu.speed = 6;


        //peli loop
        while (!WindowShouldClose())
        {






            // piirtäminen 
            BeginDrawing();

            //update
            ball.Update();

            ClearBackground(RAYWHITE);


            player.update();
            cpu.update(ball.y);


            //collisoin 
            if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height }))
            {
                ball.speed_x *= -1;
            }
            if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height }))
            {
                ball.speed_x *= -1;
            }




            //draw
            ball.draw();
            cpu.draw();


            player.draw();

            DrawText(TextFormat("%i",cpu_score), screen_width / 4 - 20, 20, 80, BLUE);
            DrawText(TextFormat("%i", player_score), 3*screen_width / 4 - 20, 20, 80, BLUE);

            EndDrawing();



           

        }
        CloseWindow();

        return 0;
    }
