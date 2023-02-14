#include "../include/raylib.h"
#include "../include/rlgl.h"
#include "gameobject/Bar.h"
#include "gameobject/AI.h"
#include "gameobject/Ball.h"
#include <iostream>

int HEIGHT = 768;
int WIDTH = 1366;

int main(void){
    InitWindow(WIDTH,HEIGHT,"Game");
    SetTargetFPS(60);
    Bar bar;
    AI enemy;
    Ball ball;
    bar.init();
    enemy.init(bar);
    ball.init(bar, enemy);
    
    
    while(!WindowShouldClose()){
        if(IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
        }
        bar.update(bar,ball);
        enemy.update(bar, ball);
        ball.update(bar, enemy);
        
        BeginDrawing();
            ClearBackground(BLACK);
            for(int i = 0; i < 10; i++){
                DrawRectangle(WIDTH/2 - 10, -200 + 180*i, 20, 60 + 30, {255,255,255,22});
                DrawRectangle(WIDTH/2 - 60, -200 + 180*i+ 300*sin(GetTime()), 20, 60 + 30, {255,255,255,17});
                DrawRectangle(WIDTH/2 - 110, -200 + 180*i+ 300*sin(GetTime()), 20, 60 + 30, {255,255,255,12});
                DrawRectangle(WIDTH/2 - 160, -200 + 180*i+ 300*sin(GetTime()), 20, 60 + 30, {255,255,255,7});
                DrawRectangle(WIDTH/2 + 40, -200 + 180*i- 300*sin(GetTime()), 20, 60 + 30, {255,255,255,17});
                DrawRectangle(WIDTH/2 + 90, -200 + 180*i- 300*sin(GetTime()), 20, 60 + 30, {255,255,255,12});
                DrawRectangle(WIDTH/2 + 140, -200 + 180*i- 300*sin(GetTime()), 20, 60 + 30, {255,255,255,7});
            }
            DrawRectangleGradientV(0,0,WIDTH,HEIGHT, BLACK,{0,(unsigned char)(122 + 122*sin(GetTime())),255,22});
            DrawRectangle(WIDTH/2 + sin(GetTime())*WIDTH/2, 0, 5, HEIGHT, {255,255,255,21});
            if(ball.AIScore >ball.playerScore){
                DrawRectangleGradientH(WIDTH/2, 0, WIDTH,HEIGHT, {0,0,0,0}, {0,255,0,125});
            }
            if(ball.AIScore < ball.playerScore){
                DrawRectangleGradientH(0, 0, WIDTH/2,HEIGHT, {0,255,0,55},{0,0,0,0});
            }
            
            bar.render();
            enemy.render();
            ball.render();
            
            DrawFPS(20,20);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}