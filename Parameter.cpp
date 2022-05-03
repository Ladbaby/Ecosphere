#include"Parameter.h"

GrassData grassData={
    .energyAsFood  = 10,
    .maxDensity    = 1000,
    .baseGrowSpeed = 10,
};

SpecieData cowData={
    .adultAge           = 7,
    .aveAge             = 9,
    .aveBaseSize        = 10,
    .energyFactor       = 10,
    .minReproduceEnergy = 1,
    .reproduceCost      = 10,
    .moveCost           = 0.1,
    .baseCost           = 0.1,
    .valueAsFood        = 10,
    .viewAngle          = PI/4,
    .viewDistance       = 20,
    .allertDistance     = 40,
    .allertTime         = 10,
    .wanderSpeed        = 2,
    .baseRunSpeed       = 5,
    .foods              = {grass},
    .predators          = {tiger},
};

SpecieData tigerData={
    .adultAge           = 7,
    .aveAge             = 9,
    .aveBaseSize        = 10,
    .energyFactor       = 10,
    .minReproduceEnergy = 1,
    .reproduceCost      = 100,
    .moveCost           = 0.1,
    .baseCost           = 0.1,
    .valueAsFood        = 1,
    .viewAngle          = PI/2,
    .viewDistance       = 20,
    .allertDistance     = 40,
    .allertTime         = 10,
    .wanderSpeed        = 3,
    .baseRunSpeed       = 8,
    .foods              = {cow},
    .predators          = {},
};

SpecieData specieDataList[2]={tigerData, cowData};

