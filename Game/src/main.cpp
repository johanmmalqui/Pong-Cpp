//Raylib Files
#include "../include/raylib.h"
#include "../include/rlgl.h"
#include "gameobject/Bar.h"
#include "gameobject/AI.h"
#include "gameobject/Ball.h"
#include <iostream>

int BARSIZE = 75;
int ENEMYBARSIZE = 255;
int HEIGHT = 1000;
int WIDTH = 1200;


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
            bar.render();
            enemy.render();
            ball.render();
            DrawLine(0,HEIGHT/2, WIDTH, HEIGHT/2, BLUE);
            DrawLine(WIDTH/2,0, WIDTH/2, HEIGHT, RED);
            DrawFPS(20,20);
            
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}