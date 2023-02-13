#pragma once 
#include "GameObject.h"
#include "math.h"
#include <random>
class Ball: public GameObject
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
    std::vector<GameObject> getCollidingObjects(){
        std::vector<GameObject> colliding;
        for(auto& o: Objects){
            if(CheckCollisionCircleRec(position, radius, o.rec))
            {
                colliding.push_back(o);
            }
        }
        return colliding;
    }
    std::vector<bool> handleCollisionAndUpdatePlayer(){
        bool top = false;
        bool bottom = false;
        bool left = false;
        bool right = false;
        position.x += velocity.x;
        rec.x = position.x - rec.width/2;
        std::vector<GameObject> colliding = getCollidingObjects();
        for (auto& o : colliding){
            if (velocity.x > 0){
                position.x = o.rec.x - rec.width/2 - 1;
                right = true;
              
            }
            if (velocity.x < 0){
                position.x = o.rec.x + o.rec.width + rec.width/2 + 1;
                left = true;
             
            }
        }
        position.y += velocity.y;
        rec.y = position.y - rec.height/2;
        colliding = getCollidingObjects();
        for (auto& o : colliding){
            if (velocity.y < 0){
                position.y = o.rec.y + o.rec.height + rec.height/2 + 1;
                top = true;
            }
            if (velocity.y > 0){
                position.y = o.rec.y - rec.height/2 - 1;
                bottom = true;
            }
        }
        std::vector<bool> values;
        values.push_back(top);
        values.push_back(bottom);
        values.push_back(right);
        values.push_back(left);
        return values;
    }
    void handleCollision(std::vector<bool> values){
        bool top = values[0];
        bool bottom = values[1];
        bool right = values[2];
        bool left = values[3];
        int variation = GetRandomValue(10,15);
        int dvar = GetRandomValue(0,1);
        if(top){
            velocity.y *= -(1*variation/10);
        }
        if(bottom){
            velocity.y *= -(1*variation/10);
        }
        if(right){
            if (dvar == 0){
                velocity.x *= (1*variation/10);
            }
            if (dvar == 1){
                velocity.x *= -(1*variation/10);
            }
            
            velocity.y *= (1*variation/10);
        }
        if(left){
            if (dvar == 0){
                velocity.x *= (1*variation/10);
            }
            if (dvar == 1){
                velocity.x *= -(1*variation/10);
            }
            velocity.y *= (1*variation/10);
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
    std::vector<GameObject> Objects;
    virtual void init(GameObject bar1, GameObject bar2)
    {   
        Objects.push_back(bar1);
        Objects.push_back(bar2);
        speed = moveSpeed;
        position.x = WIDTH/2;
        position.y = HEIGHT/2;
        rec.width = radius*2;
        rec.height = radius*2;
        rec.x = position.x - rec.width/2;
        rec.y = position.y - rec.height/2;
        velocity.x = -8;
        velocity.y = 1;
        col = WHITE;
    }
    virtual void update(GameObject bar1, GameObject bar2) 
    {
        Objects[0] = bar1;
        Objects[1] = bar2;
        handleScreenCollision();
        handleScores();
        std::vector<bool> collisionvalues = handleCollisionAndUpdatePlayer();
        handleCollision(collisionvalues);
    }
    virtual void render() override 
    {
        DrawCircle(position.x, position.y, radius*(3 + 2*sin(GetTime()*5)),{255,255,255,22});
        DrawCircle(position.x, position.y, radius,col);
 
        DrawText(
            std::to_string(playerScore).c_str(),
            30 + 5*sin(GetTime()*10) ,
            HEIGHT - 130,
            130,
            {255,255,255,22}
        );
        DrawText(
            std::to_string(AIScore).c_str(),
            WIDTH/2 + 30 + 5*sin(GetTime()*10) ,
            HEIGHT - 130,
            130,
            {255,255,255,22}
        );
     
    }
};