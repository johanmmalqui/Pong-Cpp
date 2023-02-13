#pragma once
#include "GameObject.h"

class Bar: public GameObject
{
private:
    void inputHandler(){
        if(IsKeyDown(KEY_W)){
            velocity.y = speed*-1;
        }
        else if (IsKeyDown(KEY_S)){
            velocity.y = speed;
        }
        else{
            velocity.y = 0;
        }
    }
    void setScreenBounds(){
        if(position.y <= 0){
            position.y = 0;
        }
        if(position.y >= HEIGHT - rec.height){
            position.y = HEIGHT - rec.height;
        }
    }
    void handleDash(){
        if(IsKeyDown(KEY_LEFT_SHIFT)){
            speed = dashSpeed;
            col = RED;
        }
        else{
            speed = moveSpeed;
            col = WHITE;
        }
    }
    void updatePlayerPosition(){
        position.y += velocity.y;
        position.x += velocity.x;
    }
    void updatePlayerRect(){
        rec.x = position.x;
        rec.y = position.y;
    }
public:
    int speed;
    int moveSpeed = 5;
    int dashSpeed = 15;
    int HEIGHT = GetScreenHeight();
    int WIDTH = GetScreenWidth();
    virtual void init() override
    {
        speed = moveSpeed;
        rec.width = 20;
        rec.height = 75;
        rec.x = 50;
        rec.y = HEIGHT/2 - rec.height/2;
        position.x = rec.x;
        position.y = rec.y;
        velocity.x = 0;
        velocity.y = 0;
        col = WHITE;
    };
    virtual void update() override
    {
        inputHandler();
        handleDash();
        setScreenBounds();
        updatePlayerPosition();
        updatePlayerRect();
        
    };
    virtual void render() override
    {
        DrawRectangle(position.x, position.y, rec.width, rec.height, col);
    };
};

