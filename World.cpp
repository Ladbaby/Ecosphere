#include"World.h"
#include<stdio.h>     
#include<time.h> 
#include<math.h>
#include"Creature.h"
#include"Grass.h"
#include"Parameter.h"
#include<vector>
#include<list>
#include<iostream>


double getInitialDensity()
{
    double initialAvgDensity = grassData.initialAvgDensity;
    double maxDensity = grassData.maxDensity;
    if (initialAvgDensity <= 0)
    {
        return 0;
    }
    else if (initialAvgDensity >= maxDensity)
    {
        return maxDensity;
    }
    else
    {
        double range = 0.5 * std::min(initialAvgDensity, maxDensity - initialAvgDensity);
        double randomFactor = ((double)rand() / RAND_MAX - 0.5) * 2;
        return initialAvgDensity + randomFactor * range;
    }
}

//Downward integration
int World::getX(double x)
{
    if (int(x) == WorldWidth)
    {
        return int(x) - 1;
    }
    else
    {
        return (int)floor(x);
    }
}

int World::getY(double y)
{
    if (int(y) == WorldHeight)
    {
        return int(y) - 1;
    }
    else
    {
        return (int)floor(y);
    }
}

double World::distance(Creature object, double x, double y)
{
    return sqrt(pow(object.getPositionX() - x, 2) + pow(object.getPositionY() - y, 2));
}

bool World::isInside(int id, double x, double y, double R)
{
    auto it = mapCreature.find(id);
    if (it != mapCreature.end())
    {
        double distance = sqrt(pow((it->second).getPositionX() - x, 2) + pow((it->second).getPositionY() - y, 2));
        if (distance <= R)
            return true;
    }
    return false;
}

bool World::GrassisInside(int id, double x, double y, double R)
{
    auto it = mapGrass.find(id);
    if (it != mapGrass.end())
    {
        double distance = sqrt(pow((it->second).getPositionX() - x, 2) + pow((it->second).getPositionY() - y, 2));
        if (distance <= R)
            return true;
    }
    return false;
}

World::World(int x, int y)
{
    ID = 0;
    WorldWidth = x;
    WorldHeight = y;
    for (int width = 0; width < WorldWidth; width++)
    {
        std::vector<Grid> row;
        for (int height = 0; height < WorldHeight; height++)
        {
            grassAtr tempAtr = {
                .id = allocate(),
                .positionx = double(width),
                .positiony = double(height),
                .density = getInitialDensity(),
                .database = this
            };
            Grass tempGrass(tempAtr);
            mapGrass[tempGrass.getID()] = tempGrass;
            Grid grid = {
                .creatureList = {},
                .grassID = tempGrass.getID()
            };
            row.push_back(grid);
        }
        table.push_back(row);
    }
}

void World::updateAll(double time)
{
    // std::cout << "Update: " << time << std::endl;
    int cow = 0;
    for (int row = 0; row < WorldWidth; row++)
    {
        for (int col = 0; col < WorldHeight; col++)
        {
            int currGrass = table[row][col].grassID;
            mapGrass[currGrass].update(time);
            for (auto it = table[row][col].creatureList.begin(); it != table[row][col].creatureList.end(); )
            {
                // std::cout << "time: " << time << " cow: " << cow << std::endl;
                cow++;
                if (mapCreature[*it].update(time))
                {
                    Creature tempCreature = mapCreature[*it];
                    int currX = getX(tempCreature.getPositionX());
                    int currY = getY(tempCreature.getPositionY());
                    if (currX != row || currY != col)
                    {
                        table[currX][currY].creatureList.push_back(*it);
                        it = table[row][col].creatureList.erase(it);
                    }
                    else
                    {
                        it++;
                    }
                }
                else
                {
                    mapCreature.erase(*it);
                    it = table[row][col].creatureList.erase(it);
                }
            }
        }
    }
}

void World::setWorldWidth(int width)
{
    WorldWidth = width;
}

void World::setWorldHeight(int height)
{
    WorldHeight = height;
}

void World::insert(Creature object)
{
    int x = getX(object.getPositionX());
    int y = getY(object.getPositionY());
    table[x][y].creatureList.push_back(object.getID());
    mapCreature[object.getID()] = object;
}

void World::remove(int id)
{
    auto tempCreature = mapCreature.find(id);
    if (tempCreature != mapCreature.end())
    {
        int x = getX(tempCreature->second.getPositionX());
        int y = getY(tempCreature->second.getPositionY());
        table[x][y].creatureList.remove(id);
        mapCreature.erase(tempCreature);
    }
}

int World::allocate()
{
    ID += 1;
    return ID;
}

void World::updateGrassDensity(int id, double density)
{
    auto grassPair = mapGrass.find(id);
    if (grassPair != mapGrass.end())
    {
        grassPair->second.setDensity(density);
    }
}

void World::updateCreatureEnergy(int id, double energy)
{
    auto creaturePair = mapCreature.find(id);
    if (creaturePair != mapCreature.end())
    {
        creaturePair->second.setEnergy(energy);
    }
}

void World::updateCouple(int id, int coupleID, State S)
{
    auto creaturePair = mapCreature.find(id);
    if (creaturePair != mapCreature.end())
    {
        creaturePair->second.setCoupleID(coupleID);
        creaturePair->second.setState(S);
    }
}

const Creature* World::search(int id)
{
    auto iterC = mapCreature.find(id);
    if (iterC != mapCreature.end())
    {
        // Creature object=iterC->second;
        return &(iterC->second);
    }
    return nullptr;
}

const Grass* World::searchGrass(int id)
{
    auto iterG = mapGrass.find(id);
    if (iterG != mapGrass.end())
    {
        // Grass object=iterG->second;
        return &(iterG->second);
    }
    return nullptr;
}

int World::getWorldWidth()
{
    return WorldWidth;
}

int World::getWorldHeight()
{
    return WorldHeight;
}

std::list<int> World::rangeSearch(double x, double y, double r)
{
    std::list<int> resultCreatureList;
    int x_left = (int)floor(x - r);
    if (x - r <= 0)  x_left = 0;
    int x_right = (int)ceil(x + r);
    if (x_right >= WorldWidth) x_right = WorldWidth;
    int y_bottom = (int)floor(y - r);
    if (y_bottom <= 0) y_bottom = 0;
    int y_up = (int)ceil(y + r);
    if (y_up > WorldHeight)    y_up = WorldHeight;
    for (int i = x_left;i < x_right;i++)
    {
        for (int j = y_bottom;j < y_up;j++)
        {
            for (auto iterL = table[i][j].creatureList.begin(); iterL != table[i][j].creatureList.end();iterL++)
            {
                int id = *iterL;
                if (isInside(id, x, y, r))
                {
                    resultCreatureList.push_back(id);
                }
            }
        }
    }
    return resultCreatureList;
}

std::list<int> World::rangeSearchGrass(double x, double y, double r)
{
    std::list<int> resultGrassList;
    int x_left = (int)floor(x - r);
    if (x - r <= 0)  x_left = 0;
    int x_right = (int)ceil(x + r);
    if (x_right >= WorldWidth)     x_right = WorldWidth;
    int y_bottom = (int)floor(y - r);
    if (y_bottom <= 0) y_bottom = 0;
    int y_up = (int)ceil(y + r);
    if (y_up > WorldHeight)    y_up = WorldHeight;
    for (int i = x_left;i < x_right;i++)
    {
        for (int j = y_bottom;j < y_up;j++)
        {
            int currGrass = table[i][j].grassID;
            if (GrassisInside(currGrass, x, y, r))
            {
                resultGrassList.push_back(currGrass);
            }
        }
    }
    return resultGrassList;
}