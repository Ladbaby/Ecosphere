#pragma once
#include<set>

enum Type {tiger = 0, cow, grass};
enum Gender {male, female};
enum State {stray, hunt, escape, allert, reproduce};

struct GrassData
{
    double energyAsFood;
    double maxDensity;
    double baseGrowSpeed;
};

struct SpecieData
{
    double adultAge;
    double aveAge;
    double aveBaseSize;
    double energyFactor;
    double minReproduceEnergy;
    double reproduceCost;
    double moveCost;
    double baseCost;
    double valueAsFood;
    double viewAngle;
    double viewDistance;
    double allertDistance;
    double allertTime;
    double wanderSpeed;
    double baseRunSpeed;
    std::set<Type> foods;
    std::set<Type> predators;
};
