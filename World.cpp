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
        return (int)floor(x);
    }

    int World::getY(double y)
    {
        return (int)floor(y);
    }

    double World::distance(Creature object,double x,double y)
    {
        return sqrt( pow(object.getPositionX()-x,2)+pow(object.getPositionY()-y,2) );
    }

    bool World::isInside(int id,double x,double y,double R)
    {
        if(mapCreature.count(id)==1)
        {
            iterC=mapCreature.find(id);

            double distance=sqrt( pow((iterC->second).getPositionX()-x,2)+pow((iterC->second).getPositionY()-y,2) );
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
        for (int height = 0; height < WorldHeight; height++)
        {
            table.push_back(getVector());
        }
        for(int height = 0; height < WorldHeight; height++)
        {
            for (int width = 0; width < WorldWidth; width++ )
            {
                table[height].push_back(getList());
            }
        }
    }

    void World::updateAll(double time)
    {
        Creature objectC;
        Grass objectG;
        for(int i=1;i<=ID;i++)
        {
            if(search(ID,objectC))
            {
                objectC.update(time);
            }
            else if(search(ID,objectG))
            {
                objectG.update(time);
            }
            else 
            continue;
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
        if( search(id, object)||search(id,objectC) )
        {
            int x=getX(object.getPositionX());
            int y=getY(object.getPositionY());
            table[x][y].remove(id);
        }
    }

    int World::allocate()
    {
        ID+=1;
        return ID;
    }

    void World::updateGrassDensity(int id,double density)
    {
        Grass object;
        search(id,object);
        object.setDensity(density);
    }

    void World::updateCreatureEnergy(int id,double energy)
    {
        Creature object;
        search(id,object);
        object.setEnergy(energy);
    }

    void World::updateCouple(int id,int coupleID,State S)
    {
        Creature object;
        search(id,object);
        object.setCoupleID(coupleID);
        object.setState(S);
    }

    bool World::search(int id,Creature &object)
    {
        if(mapCreature.count(id)==1)
        {
            iterC=mapCreature.find(id);
            object=iterC->second;
            return true;
        }
        return false;
    }

    bool World::search(int id,Grass &object)
    {
        if(mapGrass.count(id)==1)
        {
            iterG=mapGrass.find(id);
            object=iterG->second;
            return true;
        }
        return false;
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
                for(iterL=table[i][j].begin(); iterL !=table[i][j].end();iterL++)
                {
                    int id=*iterL;
                    if(isInside(id,x,y,r))
                    {
                        creatureList.push_back(id);
                    }
                    else
                        continue;
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
                for(iterL=table[i][j].begin(); iterL !=table[i][j].end();iterL++)
                {
                    int id=*iterL;
                    if(isInside(id,x,y,r))
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