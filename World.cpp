#include"World.h"
#include<stdio.h>     
#include<time.h> 
#include<math.h>
#include"Creature.h"
#include"Grass.h"
#include<vector>
#include<list>


//Downward integration
    int World::getX(double x)
    {
        if(int(x)==WorldWidth)
        {
            return int(x)-1;
        }
        else
        {
            return (int)floor(x);
        }
    }

    int World::getY(double y)
    {
        if(int(y)==WorldHeight)
        {
            return int(y)-1;
        }
        else
        {
            return (int)floor(y);
        }
    }

    double World::distance(Creature object,double x,double y)
    {
        return sqrt( pow(object.getPositionX()-x,2)+pow(object.getPositionY()-y,2) );
    }

    bool World::isInside(int id,double x,double y,double R)
    {
        auto it=mapCreature.find(id);
        if(it!=mapCreature.end())
        {
            double distance=sqrt( pow((it->second).getPositionX()-x,2)+pow((it->second).getPositionY()-y,2) );
            if(distance<=R)
            return true;
        }
        return false;
    }

    bool World::GrassisInside(int id,double x,double y,double R)
    {
        auto it=mapGrass.find(id);
        if(it!=mapGrass.end())
        {
            double distance=sqrt( pow((it->second).getPositionX()-x,2)+pow((it->second).getPositionY()-y,2) );
            if(distance<=R)
            return true;
        }
        return false;
    }

    std::vector<std::list<int>> World::getVector()
    {
        std::vector <std::list<int>> s1;
        return s1;
    }

    std::list<int> World::getList()
    {
        std::list<int> l1;
        return l1;
    }

    World::World(int x ,int y)
    {
        WorldWidth=x;
        WorldHeight=y;
        for (int width = 0; width < WorldWidth; width++)
        {
            table.push_back(getVector());
        }
        for(int width = 0; width < WorldWidth; width++)
        {
            for (int height = 0; height < WorldHeight; height++ )
            {
                table[width].push_back(getList());
            }
        }
    }

    void World::updateAll(double time)
    {
        for(auto iterC=mapCreature.begin();iterC!=mapCreature.end();)
        {
            int id=iterC->first;
            int x=getX(iterC->second.getPositionX());
            int y=getY(iterC->second.getPositionY());
            table[x][y].remove(id);
            if((iterC->second).update(time))
            {
                x=getX(iterC->second.getPositionX());
                y=getY(iterC->second.getPositionY());
                table[x][y].push_back(iterC->first);
                iterC++;
            }
            else
            {
                iterC=mapCreature.erase(iterC);
            }
        }
        for(auto iterG=mapGrass.begin();iterG!=mapGrass.end();iterG++)
        {
            int id=iterG->first;
            int x=getX(iterG->second.getPositionX());
            int y=getY(iterG->second.getPositionY());
            table[x][y].remove(id);
            (iterG->second).update(time);
            x=getX(iterG->second.getPositionX());
            y=getY(iterG->second.getPositionY());
            table[x][y].push_back(iterG->first);
        }

    }
    
    void World::setWorldWidth( int width)
    {
        WorldWidth=width;
    }

    void World::setWorldHeight(int height)
    {
        WorldHeight=height;
    }

    void World::insert(Creature object)
    {
        int x=getX(object.getPositionX());
        int y=getY(object.getPositionY());
        table[x][y].push_back(object.getID());
        mapCreature[object.getID()]=object;
    }

    void World::insert(Grass object)
    {
        int x=getX(object.getPositionX());
        int y=getY(object.getPositionY());
        table[x][y].push_back(object.getID());
        mapGrass[object.getID()]=object;
    }

    void World::remove(int id)
    {
        Grass object;
        Creature objectC;
        auto iterC=mapCreature.find(id);
        auto iterG=mapGrass.find(id);
        if(iterC!=mapCreature.end())
        {
            int x=getX(iterC->second.getPositionX());
            int y=getY(iterC->second.getPositionY());
            table[x][y].remove(id);
            mapCreature.erase(iterC);
        }
        if(iterG!=mapGrass.end())
        {
            int x=getX(iterG->second.getPositionX());
            int y=getY(iterG->second.getPositionY());
            table[x][y].remove(id);
            mapGrass.erase(iterG);
        }
    }

    int World::allocate()
    {
        ID+=1;
        return ID;
    }

    void World::updateGrassDensity(int id,double density)
    {
        auto grassPair=mapGrass.find(id);
        if(grassPair!=mapGrass.end())
        {
            grassPair->second.setDensity(density);
        }
    }

    void World::updateCreatureEnergy(int id,double energy)
    {
        auto creaturePair=mapCreature.find(id);
        if(creaturePair!=mapCreature.end())
        {
            creaturePair->second.setEnergy(energy);
        }
    }

    void World::updateCouple(int id,int coupleID, State S)
    {
        auto creaturePair=mapCreature.find(id);
        if(creaturePair!=mapCreature.end())
        {
            creaturePair->second.setCoupleID(coupleID);
            creaturePair->second.setState(S);
        }
    }

    const Creature* World::search(int id)
    {
        auto iterC=mapCreature.find(id);
        if(iterC!=mapCreature.end())
        {
            // Creature object=iterC->second;
            return &(iterC->second);
        }
        return nullptr;
    }

    const Grass* World::searchGrass(int id)
    {
        auto iterG=mapGrass.find(id);
        if(iterG!=mapGrass.end())
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

    std::list<int> World::rangeSearch(double x,double y,double r)
    {
        std::list<int> creatureList;
        int x_left=(int)floor(x-r);
        if(x-r<=0)  x_left=0;
        int x_right=(int)ceil(x+r);
        if(x_right>=WorldWidth) x_right=WorldWidth;
        int y_bottom=(int)floor(y-r);
        if(y_bottom<=0) y_bottom=0;
        int y_up=(int)ceil(y+r);
        if(y_up>WorldHeight)    y_up=WorldHeight;
        for(int i=x_left;i<x_right;i++)
        {
            for(int j=y_bottom;j<y_up;j++)
            {
                for(auto iterL=table[i][j].begin(); iterL !=table[i][j].end();iterL++)
                {
                    int id=*iterL;
                    if(isInside(id,x,y,r))
                    {
                        creatureList.push_back(id);
                    }
                }
            }
        }
        return creatureList;
    }

    std::list<int> World::rangeSearchGrass(double x,double y,double r)
    {
        std::list<int>grasslist;
        int x_left=(int)floor(x-r);
        if(x-r<=0)  x_left=0;
        int x_right=(int)ceil(x+r);
        if(x_right>=WorldWidth)     x_right=WorldWidth;
        int y_bottom=(int)floor(y-r);
        if(y_bottom<=0) y_bottom=0;
        int y_up=(int)ceil(y+r);
        if(y_up>WorldHeight)    y_up=WorldHeight;
        for(int i=x_left;i<x_right;i++)
        {
            for(int j=y_bottom;j<y_up;j++)
            {
                for(auto iterL=table[i][j].begin(); iterL !=table[i][j].end();iterL++)
                {
                    int id=*iterL;
                    if(GrassisInside(id,x,y,r))
                    {
                        grassList.push_back(id);
                    }
                    else
                        continue;
                }
            }
        }
        return grassList;
    }