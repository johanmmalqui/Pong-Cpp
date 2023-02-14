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
       
        if(GetTime() - scoreTime > 1){
            if ((AIScore + playerScore)%2 == 0){
            velocity.x = -1*GetRandomValue(5,15);
            }
            else if ((AIScore + playerScore)%2 == 1){
                velocity.x = 1*GetRandomValue(5,15);
            }
            velocity.y = GetRandomValue(5,15);
        }
        
    }

    void handleScores(){
        //std::cout<<scoreTime<<"-"<<GetTime()<<std::endl;
        //std::cout<<GetTime() - scoreTime<<std::endl; 
        if(position.x < -20){
            AIScore += 1;
            scoreTime = GetTime();
            position.x = WIDTH/2;
            position.y = HEIGHT/2; 
            velocity.x = 0;
            velocity.y = 0;
            pointScored = true;
        }
        else if(position.x > WIDTH + 20){
            playerScore += 1;
            scoreTime = GetTime();
            position.x = WIDTH/2;
            position.y = HEIGHT/2; 
            velocity.x = 0;
            velocity.y = 0;
            pointScored =  true;
        }
        if(pointScored == true){
            float winradius;
            winradius = 300 - 196*cos((GetTime() - scoreTime));
            if(winradius<5){
                winradius = 5;
            }
            std::cout<<std::to_string(255 - sin(PI*0.5*(GetTime()-scoreTime))).c_str()<<std::endl;
            DrawCircle(position.x, position.y, winradius*(3 + 2*sin(GetTime()*5)),{255,255,255,(unsigned char)(255 - 255*sin(PI*0.5*(GetTime()-scoreTime)))});
           
            
           
        }
        if((GetTime() - scoreTime > 1) && (pointScored == true)){
            DrawText(
                "ASSIGN SPEED NOW",
                30,
                180,
                20,
                BLUE
            );
            radius = 5;
            if ((AIScore + playerScore)%2 == 0){
                velocity.x = -1*GetRandomValue(5,15);
            }
            else if ((AIScore + playerScore)%2 == 1){
                velocity.x = 1*GetRandomValue(5,15);
            }
            velocity.y = GetRandomValue(5,7);
            pointScored = false;
            
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
            if(CheckCollisionCircleRec(position, radius, o.bbox))
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
                position.x = o.bbox.x - rec.width/2 - 1;
                right = true;
              
            }
            if (velocity.x < 0){
                position.x = o.bbox.x + o.bbox.width + rec.width/2 + 1;
                left = true;
             
            }
        }
        position.y += velocity.y;
        rec.y = position.y - rec.height/2;
        colliding = getCollidingObjects();
        for (auto& o : colliding){
            if (velocity.y < 0){
                position.y = o.bbox.y + o.bbox.height + rec.height/2 + 1;
                top = true;
            }
            if (velocity.y > 0){
                position.y = o.bbox.y - rec.height/2 - 1;
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
        
        if(top){
            velocity.y *= -1;
        }
        if(bottom){
            velocity.y *= -1;
        }
        if(right){
            float temp = velocity.x;
            velocity.x = abs(velocity.y);
            velocity.y /= abs(velocity.y);
            velocity.y *= abs(temp) * 0.95;
            velocity.x *= -1.35;
        }
        if(left){       
            float temp = velocity.x;
            velocity.x = abs(velocity.y);
            velocity.y /= abs(velocity.y);
            velocity.y *= abs(temp) *0.95;
            velocity.x *= 1.35;   
        }
    }
public:
    int playerScore = 0;
    int AIScore = 0;
    int radius = 5;
    float moveSpeed = 7;
    float speed;
    float HEIGHT = GetScreenHeight();
    float WIDTH = GetScreenWidth();
    double scoreTime = GetTime();
    bool pointScored = false;
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
        velocity.x = -5;
        velocity.y = -5;
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
            WIDTH -170 + 5*sin(GetTime()*10) ,
            20,
            130,
            {255,255,255,22}
        );

        
     
    }
};