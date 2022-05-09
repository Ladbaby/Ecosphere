#include"Parameter.h"

GrassData grassData={
    .energyAsFood      = 100,
    .maxDensity        = 1000,
    .baseGrowSpeed     = 0.02,
    .initialAvgDensity = 0 // must be less than maxDensity
};

SpecieData cowData={
    .adultAge           = 30,
    .aveAge             = 300,
    .aveBaseSize        = 10,
    .energyFactor       = 10,
    .minReproduceEnergy = 150000,
    .reproduceCost      = 100000,
    .moveCost           = 0.01,
    .baseCost           = 0.01,
    .valueAsFood        = 1000,
    .viewAngle          = PI*2/3,
    .viewDistance       = 10,
    .allertDistance     = 10,
    .allertTime         = 3,
    .wanderSpeed        = 2,
    .wanderDistance     = 50,
    .baseRunSpeed       = 5,
    .foods              = {grass},
    .predators          = {tiger},
};

SpecieData tigerData={
    .adultAge           = 30,
    .aveAge             = 300,
    .aveBaseSize        = 10,
    .energyFactor       = 10,
    .minReproduceEnergy = 150000,
    .reproduceCost      = 100000,
    .moveCost           = 0.1,
    .baseCost           = 0.1,
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

