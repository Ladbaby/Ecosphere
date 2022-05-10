#pragma once
#include <list>
#include <map>
#include <vector>
#include "Parameter.h"

class Creature;
class Grass;

struct Grid
{
    std::list<int> creatureList;
    int grassID;
};

class World
{
private:
    std::vector<std::vector<Grid>> table;
    std::map<int, Creature> mapCreature;
    std::map<int, Grass> mapGrass;

    int getX(double x);
    int getY(double y);

    double distance(Creature object, double x, double y);
    bool isInside(int id, double x, double y, double R);
    bool GrassisInside(int id, double x, double y, double R);

    int WorldWidth;
    int WorldHeight;

    int ID;
    /*vector<vector <int> > ivec;
    ivec.resize(m,vector<int>(n));*/

public:
    World(int x = 96, int y = 54);

    // updateAll(double time)
    // update all creatures and grass, given the current time
    void updateAll(double);
    void afterPause(double);

    void setWorldWidth(int width);
    void setWorldHeight(int height);
    int getWorldWidth();
    int getWorldHeight();

    void insert(Creature);

    // remove(int id)
    // given the creature/grass id, remove it
    void remove(int);

    // allocate() returns an available id
    // the user will use this id to create new creature/grass
    int allocate();

    // updateGrassDensity(int id, double density)
    // given the grass id, update its density
    void updateGrassDensity(int, double);

    // updateCreatureEnergy(int id, double energy)
    // given the creature id, update its energy
    void updateCreatureEnergy(int, double);

    // updateCouple(int id, int coupleID, State s)
    // given the creature id, set its couple=coupleID and state=s.
    void updateCouple(int, int, State);

    const Creature *search(int);
    const Grass *searchGrass(int);

    // given the center and radius
    // find all objects of certain creature in that circle
    std::list<int> rangeSearch(double, double, double); // center(x,y) ,R
    std::list<int> rangeSearchGrass(double, double, double);

    std::map<int, Creature>::const_iterator creatureBegin()
    {
        return mapCreature.begin();
    }
    std::map<int, Creature>::const_iterator creatureEnd()
    {
        return mapCreature.end();
    }
    std::map<int, Grass>::const_iterator grassBegin()
    {
        return mapGrass.begin();
    }
    std::map<int, Grass>::const_iterator grassEnd()
    {
        return mapGrass.end();
    }
};
