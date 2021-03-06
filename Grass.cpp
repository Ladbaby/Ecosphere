#include "Parameter.h"
#include "World.h"
#include "Grass.h"
#include <math.h>

extern GrassData grassData;

Grass::Grass() {}
Grass::Grass(grassAtr atr)
{
    id = atr.id;
    positionx = atr.positionx;
    positiony = atr.positiony;
    density = atr.density;
    database = atr.database;
    lastUpdateTime = -1;
}
void Grass::update(double time)
{
    if (lastUpdateTime == -1)
    {
        lastUpdateTime = time;
        return;
    }
    double currentTime = time;
    double dt = currentTime - lastUpdateTime;
    lastUpdateTime = currentTime;
    if (density >= grassData.maxDensity)
    {
        density = grassData.maxDensity;
    }
    else
    {
        double t0 = inverseGrowthFunction(density);
        density = growthFunction(t0 + dt);
    }
}

void Grass::afterPause(double time)
{
    lastUpdateTime = time;
}

double Grass::getDensity() const
{
    return density;
}

double Grass::getPositionX() const
{
    return positionx;
}

double Grass::getPositionY() const
{
    return positiony;
}
int Grass::getID() const
{
    return id;
}

void Grass::setDensity(double Density)
{
    density = Density;
}

double Grass::growthFunction(double t)
{
    return grassData.maxDensity * (1 - exp(-grassData.baseGrowSpeed * t));
}
double Grass::inverseGrowthFunction(double density)
{
    return -(1 / grassData.baseGrowSpeed) * log(1 - density / grassData.maxDensity);
}