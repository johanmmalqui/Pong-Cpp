#pragma once 
#include "GameObject.h"
#include <random>
class BallG: public GameObject
{
private:
    void AppearSequence(){
        
        position.x = WIDTH/2;
        position.y = HEIGHT/2;
       
        if ((AIScore + playerScore)%2 == 0){
            velocity.x = -1*GetRandomValue(5,15);
        }
        else if ((AIScore + playerScore)%2 == 1){
            velocity.x = 1*GetRandomValue(5,15);
        }
        
        velocity.y = GetRandomValue(5,15);
    
        
    }
    void handleScores(){
        if(position.x < -20){
            AIScore += 1;
            AppearSequence();
        }
        else if(position.x > WIDTH + 20){
            playerScore += 1;
            AppearSequence();
        }
    }
    void updatePlayerPosition(){
        position.y += velocity.y;
        position.x += velocity.x;
    }
    void updatePlayerRect(){
        rec.x = position.x - rec.width/2;
        rec.y = position.y - rec.height/2;
    }
    void handleScreenCollision(){
        Rectangle upperRec = {0,-100,WIDTH,100};
        Rectangle lowerRec = {0,HEIGHT,WIDTH,100};
        if (CheckCollisionCircleRec(position,radius,upperRec)||CheckCollisionCircleRec(position,radius,lowerRec)){
            velocity.y *= -1;
        }
    }
    void handleCollision(GameObject gameobject){
        if (CheckCollisionCircleRec(position, radius, gameobject.rec))
        {
            if (velocity.x<0){
                velocity.x = GetRandomValue(5,10);
            }
            else if (velocity.x >0){
                velocity.x = -1*GetRandomValue(5,10);
            }
            
          
            velocity.y = GetRandomValue(5,10);
            
        }
    }
public:

    int playerScore = 0;
    int AIScore = 0;
    int radius = 5;
    float moveSpeed = 7;
    float speed;
    int HEIGHT = GetScreenHeight();
    int WIDTH = GetScreenWidth();
    virtual void init() override
    {
        speed = moveSpeed;
        position.x = WIDTH/2;
        position.y = HEIGHT/2;
        rec.width = radius*2;
        rec.height = radius*2;
        rec.x = position.x - rec.width/2;
        rec.y = position.y - rec.height/2;
        velocity.x = speed;
        velocity.y = speed;
        col = WHITE;
    }
    virtual void p_update(GameObject bar1, GameObject bar2) 
    {
        handleCollision(bar1);
        handleCollision(bar2);
        handleScreenCollision();
        handleScores();
        updatePlayerPosition();
        updatePlayerRect();
    }
    virtual void render() override 
    {
        DrawCircle(position.x, position.y, radius,col);
        DrawText(std::to_string(playerScore).c_str(),WIDTH/4, HEIGHT/8, 30, RAYWHITE);
        DrawText(std::to_string(AIScore).c_str(),3*WIDTH/4, HEIGHT/8, 30, RAYWHITE);
    }
};