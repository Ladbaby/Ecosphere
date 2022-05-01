#include"Parameter.h"

GrassData grassData={
    .energyAsFood  = 100,
    .maxDensity    = 1000,
    .baseGrowSpeed = 100,
};

SpecieData cowData={
    .adultAge           = 7,
    .aveAge             = 9,
    .aveBaseSize        = 10,
    .energyFactor       = 10,
    .minReproduceEnergy = 1,
    .reproduceCost      = 100,
    .moveCost           = 1,
    .baseCost           = 10,
    .valueAsFood        = 10,
    .viewAngle          = 4 / 3 * PI,
    .viewDistance       = 10,
    .allertDistance     = 5,
    .allertTime         = 1,
    .wanderSpeed        = 1,
    .baseRunSpeed       = 2,
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
    .moveCost           = 1,
    .baseCost           = 10,
    .valueAsFood        = 1,
    .viewAngle          = PI,
    .viewDistance       = 100,
    .allertDistance     = 1,
    .allertTime         = 1,
    .wanderSpeed        = 1,
    .baseRunSpeed       = 2.2,
    .foods              = {cow},
    .predators          = {},
};

SpecieData specieDataList[2]={tigerData, cowData};

