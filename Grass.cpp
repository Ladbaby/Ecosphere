#include"Parameter.h"
#include"World.h"
#include"Grass.h"
#include<math.h>

extern GrassData grassData;

    Grass::Grass(){}
    Grass::Grass(grassAtr atr)
    {
        id=atr.id;
        positionx=atr.positionx;
        positiony=atr.positiony;
        density=atr.density;
        database=atr.database;
        lastUpdateTime=atr.time;
    }
    void Grass::update(double time)
    {
        double currentTime=time;
        double dt=currentTime-lastUpdateTime;
        lastUpdateTime=currentTime;
        if(density>=grassData.maxDensity)
        {
            density=grassData.maxDensity;
        }
        else
        {
            double t0=inverseGrowthFunction(density);
            density=growthFunction(t0+dt);
        }
    }

    double Grass::getDensity()
    {
        return density;
    }

    double Grass::getPositionX()
    {
        return positionx;
    }

    double Grass::getPositionY()
    {
        return positiony;
    }
    double Grass::getID()
    {
        return id;
    }

    void Grass::setDensity(double Density)
    {
        density=Density;
    }

    double Grass::growthFunction(double t)
    {
        double density;
        density=grassData.maxDensity*(1-exp(grassData.baseGrowSpeed*t));
        return density;
    }
    double Grass::inverseGrowthFunction(double density)
    {
        double time;
        time=-(1/grassData.baseGrowSpeed)*log(1-density/grassData.maxDensity);
        return time;
    }