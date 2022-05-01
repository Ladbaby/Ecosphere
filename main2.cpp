#include"World.h"
#include"Creature.h"
#include"Grass.h"
#include<iostream>

int main()
{
    World world(192, 108);
    int cid=world.allocate();
    double time=0;
    creatureAtr tiger1Atr={
        .id=cid,
        .type=tiger,
        .energy=100,
        .gender=female,
        .age=18,
        .positionx=102.3,
        .positiony=66.7,
        .database=&world,
        .time=time
    };
    Creature tiger1(tiger1Atr);
    world.insert(tiger1);
    
    time=1;
    world.updateAll(time);
}