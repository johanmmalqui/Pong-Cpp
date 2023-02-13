//Raylib Files
#include "../include/raylib.h"
#include "../include/rlgl.h"
#include "gameobject/Bar.h"
#include "gameobject/AI.h"
#include "gameobject/Ball.h"
#include <iostream>

//TODO
//CREATE A FUNCTION THAT RETURNS THE SIDE OF A RECTANGLE WHICH IS COLLIDING WITH ANOTHER RECTANGLE
int BARSIZE = 75;
int ENEMYBARSIZE = 255;
int HEIGHT = 1000;
int WIDTH = 1200;


int main(void){
    InitWindow(WIDTH,HEIGHT,"Game");
    SetTargetFPS(60);
    BarG bar;
    AI enemy;
    BallG ball;
    bar.init();
    enemy.p_init(bar);
    ball.init();

    Shader bloomShader = LoadShader(0, TextFormat("#version 330\n\
        uniform sampler2D source;\n\
        uniform vec2 resolution;\n\
        uniform float threshold;\n\
        uniform float intensity;\n\
        out vec4 outColor;\n\
        \n\
        vec4 bloom(sampler2D image, vec2 uv, float threshold)\n\
        {\n\
            vec4 sum = vec4(0.0);\n\
            vec2 texelSize = vec2(1.0)/resolution;\n\
            \n\
            for (int i = -5; i <= 5; ++i)\n\
            {\n\
                for (int j = -5; j <= 5; ++j)\n\
                {\n\
                    vec2 offset = vec2(float(i), float(j))*texelSize;\n\
                    vec4 sample = texture(image, uv + offset);\n\
                    \n\
                    if (sample.r > threshold)\n\
                    {\n\
                        sum += sample;\n\
                    }\n\
                }\n\
            }\n\
            \n\
            return sum;\n\
        }\n\
        \n\
        void main()\n\
        {\n\
            vec2 uv = gl_FragCoord.xy/resolution.xy;\n\
            vec4 color = texture(source, uv);\n\
            vec4 bloomColor = bloom(source, uv, threshold);\n\
            \n\
            outColor = color + bloomColor*intensity;\n\
        }\n"));
    float resolution[2] = { (float)WIDTH, (float)HEIGHT };
    SetShaderValue(bloomShader, GetShaderLocation(bloomShader, "resolution"), resolution, SHADER_UNIFORM_VEC2);


    while(!WindowShouldClose()){
        bar.update();
        enemy.ai_update(bar, ball);
        ball.p_update(bar, enemy);
        BeginDrawing();
            ClearBackground(BLACK);
            BeginShaderMode(bloomShader);
            bar.render();
            enemy.render();
            ball.render();
            DrawLine(0,HEIGHT/2, WIDTH, HEIGHT/2, BLUE);
            DrawLine(WIDTH/2,0, WIDTH/2, HEIGHT, RED);
            DrawFPS(20,20);
            EndShaderMode(); 
        EndDrawing();
    }
    UnloadShader(bloomShader);
    CloseWindow();
    return 0;
}