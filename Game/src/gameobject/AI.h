#pragma once 
#include "GameObject.h"


class AI: public GameObject
{
private:
    
    void brain(GameObject bar, GameObject ball){
        float difference = ball.position.y - position.y;
        float distx = position.x - ball.position.x;
  
       
        if (difference <0){
            
            if (difference <= -50){
                speed = -1*dashSpeed;
               
            }
            else{
                rec.height = 75;
                speed = -1*moveSpeed;

            }
        }
        else if(difference >0){
            
            if (difference >= 50){
                speed = dashSpeed;
              
            }
            else{
                rec.height = 75;
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
   
  
    bool doDash;
    int speed;
    int moveSpeed = 5;
    int dashSpeed = 15;
    int HEIGHT = GetScreenHeight();
    int WIDTH = GetScreenWidth();
    virtual void p_init(GameObject bar)
    {  
        doDash = false;
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
    virtual void ai_update(GameObject bar, GameObject ball) 
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