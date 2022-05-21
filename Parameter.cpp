#include"Parameter.h"

GrassData grassData={
    .energyAsFood      = 0.1,
    .maxDensity        = 1000,
    .baseGrowSpeed     = 0.2,// 0.01
    .initialAvgDensity = 200 //800 must be less than maxDensity
};

SpecieData cowData={
    .adultAge           = 100,
    .aveAge             = 300,
    .aveBaseSize        = 10,
    .energyFactor       = 10,
    .minReproduceEnergy = 1.3,
    .reproduceCost      = 0.75,
    .moveCost           = 1,
    .baseCost           = 1,
    .valueAsFood        = 0.46,
    .viewAngle          = PI*2/3,
    .viewDistance       = 10,
    .allertDistance     = 10,//5
    .allertTime         = 3,
    .wanderSpeed        = 2,
    .wanderDistance     = 50,
    .baseRunSpeed       = 5,
    .foods              = {grass},
    .predators          = {tiger},
};

SpecieData tigerData={
    .adultAge           = 100,
    .aveAge             = 300,
    .aveBaseSize        = 10,
    .energyFactor       = 10,
    .minReproduceEnergy = 1.3,
    .reproduceCost      = 0.75,
    .moveCost           = 0.1,//0.5
    .baseCost           = 0.1,//0.3
    .valueAsFood        = 1,
    .viewAngle          = PI,
    .viewDistance       = 20,
    .allertDistance     = 12,
    .allertTime         = 3,
    .wanderSpeed        = 3,
    .wanderDistance     = 15,
    .baseRunSpeed       = 8,
    .foods              = {cow},
    .predators          = {},
};

SpecieData specieDataList[2]={tigerData, cowData};

