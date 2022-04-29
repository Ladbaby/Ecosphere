#include"Parameter.h"

GrassData grassData={
    .energyAsFood  = 1,
    .maxDensity    = 1,
    .baseGrowSpeed = 1,
};

SpecieData cowData={
    .adultAge           = 1,
    .aveAge             = 1,
    .aveBaseSize        = 1,
    .energyFactor       = 1,
    .minReproduceEnergy = 1,
    .reproduceCost      = 1,
    .moveCost           = 1,
    .baseCost           = 1,
    .valueAsFood        = 1,
    .viewAngle          = 1,
    .viewDistance       = 1,
    .allertDistance     = 1,
    .allertTime         = 1,
    .wanderSpeed        = 1,
    .baseRunSpeed       = 1,
    .foods              = {grass},
    .predators          = {tiger},
};

SpecieData tigherData={
    .adultAge           = 1,
    .aveAge             = 1,
    .aveBaseSize        = 1,
    .energyFactor       = 1,
    .minReproduceEnergy = 1,
    .reproduceCost      = 1,
    .moveCost           = 1,
    .baseCost           = 1,
    .valueAsFood        = 1,
    .viewAngle          = 1,
    .viewDistance       = 1,
    .allertDistance     = 1,
    .allertTime         = 1,
    .wanderSpeed        = 1,
    .baseRunSpeed       = 1,
    .foods              = {cow},
    .predators          = {},
};

SpecieData specieDataList[2]={tigherData, cowData};

