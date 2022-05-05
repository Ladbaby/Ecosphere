#pragma once
#include"World.h"
#include"Parameter.h"

struct grassAtr
{
    int id;
    double positionx;
    double positiony;
    double density;

    World* database;
};



class Grass
{
public:
    Grass();
    Grass(grassAtr);
    void update(double);
    double getDensity()const;
    double getPositionX()const;
    double getPositionY()const;
    double getID()const;
    void setDensity(double Density);
private:
    double growthFunction(double);
    double inverseGrowthFunction(double);
    int id;
    
    double lastUpdateTime;
    double positionx;
    double positiony;
    double density;

    World* database;
};