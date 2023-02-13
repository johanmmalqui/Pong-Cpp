#pragma once 
#include "GameObject.h"
#include <math.h>

class AI: public GameObject
{
private:
    void brain(GameObject bar, GameObject ball){
        float disty = ball.position.y - position.y - rec.height/2;
        float distx = ball.position.x - position.x;
        float dis = sqrt(disty*disty + distx*distx);
  
        if (disty <0){
            if (dis <= 350 and ball.velocity.x > 0){
                speed = -1*dashSpeed;
                col = RED;
           
            }
            else{
                col = WHITE;
                speed = -1*moveSpeed;
            }
        }
        else if(disty >0){           
            if (dis <= 350 and ball.velocity.x > 0 ){
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
    void setScreenBounds(){
        if(position.y <= 0){
            position.y = 0;
        }
        if(position.y >= HEIGHT - rec.height){
            position.y = HEIGHT - rec.height;
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
    virtual void init(GameObject bar)
    {  
        speed = moveSpeed;
        rec.width = 20;
        rec.height = 80;
        rec.x = WIDTH - rec.width - bar.rec.x;
        rec.y = HEIGHT/2 - rec.height/2;
        position.x = rec.x;
        position.y = rec.y;
        velocity.x = 0;
        velocity.y = 0;
        col = WHITE;
    };
    virtual void update(GameObject bar, GameObject ball) 
    {
        setScreenBounds();
        brain(bar,ball);
        updatePlayerPosition();
        updatePlayerRect();
    };
    virtual void render() override
    {
        DrawRectangle(position.x, position.y, rec.width, rec.height, col);
    };
};