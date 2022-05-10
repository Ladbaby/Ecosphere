#pragma once
#include<set>
#include<math.h>
#define PI 2*acos(0.0)


// double PI=2*acos(0.0);
enum Type {tiger = 0, cow, grass};
enum Gender {male, female};
enum State {stray, hunt, escape, allert, reproduce};



struct GrassData
{
    double energyAsFood;
    double maxDensity;
    double baseGrowSpeed;
    double initialAvgDensity;
};

struct SpecieData
{
    double adultAge;
    double aveAge;
    double aveBaseSize;
    double energyFactor;
    double minReproduceEnergy; // 相对于健康能量水平的比值
    double reproduceCost; // 相对于健康能量水平的比值
    double moveCost;
    double baseCost;
    double valueAsFood;
    double viewAngle;
    double viewDistance;
    double allertDistance;
    double allertTime;
    double wanderSpeed;
    double wanderDistance;
    double baseRunSpeed;
    std::set<Type> foods;
    std::set<Type> predators;
};

extern GrassData grassData;
extern SpecieData specieDataList[2];