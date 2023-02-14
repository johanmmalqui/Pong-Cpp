#pragma once 
#include "../../include/raylib.h"
#include <iostream>
#include <charconv>
class GameObject
{
public:
    Vector2 position; 
    Vector2 velocity;
    Color col; 
    Rectangle rec;
    Rectangle bbox;
    virtual void init(){}
    virtual void update(){}
    virtual void render(){}

    virtual ~GameObject(){}
};

