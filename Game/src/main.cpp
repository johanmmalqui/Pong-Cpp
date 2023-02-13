//Raylib Files
#include "../include/raylib.h"
#include "../include/rlgl.h"
#include "gameobject/Bar.h"
#include "gameobject/AI.h"
#include "gameobject/Ball.h"
#include <iostream>

int HEIGHT = 500;
int WIDTH = 600;

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
        bar.update();
        enemy.update(bar, ball);
        ball.update(bar, enemy);
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangle(WIDTH/2 + sin(GetTime())*WIDTH/2, 0, 5, HEIGHT, {255,255,255,21});
            
            bar.render();
            enemy.render();
            ball.render();
            for(int i = 0; i < 10; i++){
                
                DrawRectangle(WIDTH/2 - 10, 180*i+ 30*sin(GetTime()*5), 20, 60 + 30*sin(GetTime()*5), RAYWHITE);
            }
            
            DrawFPS(20,20);
            
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}