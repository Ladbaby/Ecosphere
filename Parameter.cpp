#include"Parameter.h"

GrassData grassData={
    .energyAsFood      = 10,
    .maxDensity        = 1000,
    .baseGrowSpeed     = 10,
    .initialAvgDensity = 400 // must be less than maxDensity
};

SpecieData cowData={
    .adultAge           = 100,
    .aveAge             = 100,
    .aveBaseSize        = 10,
    .energyFactor       = 10,
    .minReproduceEnergy = 1,
    .reproduceCost      = 100,
    .moveCost           = 0.1,
    .baseCost           = 0.1,
    .valueAsFood        = 10,
    .viewAngle          = PI*2/3,
    .viewDistance       = 5,
    .allertDistance     = 10,
    .allertTime         = 10,
    .wanderSpeed        = 2,
    .wanderDistance     = 15,
    .baseRunSpeed       = 5,
    .foods              = {grass},
    .predators          = {tiger},
};

SpecieData tigerData={
    .adultAge           = 100,
    .aveAge             = 100,
    .aveBaseSize        = 10,
    .energyFactor       = 10,
    .minReproduceEnergy = 1,
    .reproduceCost      = 100,
    .moveCost           = 0.1,
    .baseCost           = 0.1,
    .valueAsFood        = 1,
    .viewAngle          = PI,
    .viewDistance       = 5,
    .allertDistance     = 12,
    .allertTime         = 10,
    .wanderSpeed        = 3,
    .wanderDistance     = 15,
    .baseRunSpeed       = 8,
    .foods              = {cow},
    .predators          = {},
};

SpecieData specieDataList[2]={tigerData, cowData};

