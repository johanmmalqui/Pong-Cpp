#pragma once
#include "GameObject.h"
#include "math.h"
class Bar: public GameObject
{
private:
    void brain(GameObject bar, GameObject ball){
        float disty = ball.position.y - position.y - rec.height/2;
        float distx = ball.position.x - position.x;
        float dis = sqrt(disty*disty + distx*distx);
  
        if (disty <0){
            if (dis <= 250 and ball.velocity.x < 0){
                speed = -1*dashSpeed;
                col = RED;
           
            }
            else{
                col = WHITE;
                speed = -1*moveSpeed;
            }
        }
        else if(disty >0){           
            if (dis <= 250 and ball.velocity.x < 0 ){
                speed = dashSpeed;     
                col = RED;
                
            }
            else{
                col = WHITE;
                speed =  moveSpeed;            
            }
        }
        else{
            speed = 0;
        }
        velocity.y = speed;
    }
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
    void updatePosition(){
        position.y += velocity.y;
        position.x += velocity.x;
    }
    void updateRect(){
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
        bbox = {rec.x - 200, rec.y, rec.width + 200, rec.height};
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
    virtual void update(GameObject bar, GameObject ball)
    {
        
        inputHandler();
        handleDash();
        setScreenBounds();
        updatePosition();
        updateRect();
        bbox = {rec.x - 200, rec.y, rec.width + 200, rec.height};
        
    };
    virtual void render() override
    {
        DrawRectangle(position.x, position.y, rec.width, rec.height, col);
      
    };
};

