#include"Parameter.h"
#include"Creature.h"
#include"Grass.h"
#include"World.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<algorithm>
#include<iostream>


// double PI=2*acos(0.0);

extern GrassData grassData;
extern SpecieData specieDataList[2];

// return a random number between 0 and 1
    double getRandom()
    {
        return double(rand())/RAND_MAX;
    }

    bool compareFood(const foodCandidate& x, const foodCandidate& y)
    {
        return x.attractionValue>y.attractionValue;
    }


    Creature::Creature(){}
    Creature::Creature(creatureAtr atr)
    {
        id=atr.id;
        type=atr.type;
        energy=atr.energy;
        gender=atr.gender;
        age=atr.age;
        positionx=atr.positionx;
        positiony=atr.positiony;

        database=atr.database;
        lastUpdateTime=atr.time;
        lastChangeStateTime=atr.time;
    // random from specieData
        baseSize=((getRandom()*0.4-0.2)+1)*specieDataList[type].aveBaseSize;
        baseRunSpeed=((getRandom()*0.4-0.2)+1)*specieDataList[type].baseRunSpeed;
    // calculated
        sizeFactor=std::max(double(1), sqrt(age/specieDataList[type].adultAge));
        size=baseSize*sizeFactor;

    // whatever
        state=stray;

        direction=fmod(getRandom()*10*PI,2*PI);
        wanderDestinationx=getRandom()*(database->getWorldWidth());
        wanderDestinationy=getRandom()*(database->getWorldHeight());

        target=0;
        grassTarget=false;
        predatorset = {};

        couple=0;
        potentialCouples = {};

        potentialPrey = {};   
        potentialGrassPrey = {};
    }

    bool Creature::update(double time)
    {   
        qDebug() << lastUpdateTime << endl;
        qDebug() << time << endl;
        if(judgeDeath())
        {return false;}

        if(detectPredator(state))
        {state=escape;}

        switch(state)
        {
            case escape:
                state=escapeStateAction(time);
                break;
            case allert:
                state=allertStateAction(time);
                break;
            case hunt:
                state=huntStateAction(time);
                break;
            case reproduce:
                state=reproduceStateAction(time);
                break;
            case stray:
                state=wanderStateAction(time);
                break;
        }
        return true;
    }

    State Creature::getState() {return state;}

    Type Creature::getType() const {return type;}

    double Creature::getAge() {return age;}

    Gender Creature::getGender() {return gender;}

    double Creature::getDirection() {return direction;}

    double Creature::getEnergy() {return energy;}

    double Creature::getPositionX() const {return positionx;}
    
    double Creature::getPositionY() const {return positiony;}

    int Creature::getID() {return id;}

    void Creature::setCoupleID(int coupleID)
    {
        couple=coupleID;
    }

    void Creature::setState(State s)
    {
        state=s;
    }

    void Creature::setEnergy (double Energy)
    {
        energy=Energy;
    }
    
    bool Creature::canRun()
    {
        if(age<specieDataList[type].aveAge*1.1 
        && energy>0.5*size*specieDataList[type].energyFactor) {return true;}
        else 
        {return false;}
    }

    bool Creature::judgeDeath()
    {
        double prob=getRandom();
        if(energy<0.3*size*specieDataList[type].energyFactor)
        {return true;}
        else if(prob<pow(age/(2*specieDataList[type].aveAge),2))
        {return true;}
        else
        {return false;}
    }

    bool Creature::detectPredator(State s)
    {
        double currAllertDist=specieDataList[type].allertDistance;
        if(s==escape||s==allert) {currAllertDist*=2;}

        std::set<Type> predators=specieDataList[type].predators;
        std::list<int> list={};
        list=database->rangeSearch(positionx, positiony, specieDataList[type].viewDistance);
        for(auto it=list.cbegin(); it!=list.cend(); it++)
        {
            Creature tempPredator;
            if(database->search(*it, tempPredator)==false)
            {
                continue;
            }
            auto search=predators.find(tempPredator.getType());
            if(search!=predators.end())
            {
                double dis=calculateDistance(tempPredator.getPositionY(), tempPredator.getPositionX());
                if(dis<=currAllertDist) {predatorset.insert(*it);}
                else if(dis<=specieDataList[type].viewDistance)
                {
                    double eqPredatorDirection=calculateDirection(tempPredator.getPositionY(), tempPredator.getPositionX());
                    double viewAngle=specieDataList[type].viewAngle;
                    double eqViewDirection1=equivalentDirection(direction-viewAngle*0.5);
                    double eqViewDirection2=equivalentDirection(direction+viewAngle*0.5);
                    if(eqViewDirection1<eqViewDirection2)
                    {
                        if(eqPredatorDirection>=eqViewDirection1&&eqPredatorDirection<=eqViewDirection2)
                        {predatorset.insert(*it);}
                    }
                    else
                    {
                        if((eqPredatorDirection>=0&&eqPredatorDirection<=eqViewDirection2)
                        ||(eqPredatorDirection>=eqViewDirection1&&eqPredatorDirection<=2*PI))
                        {
                            predatorset.insert(*it);
                        }
                    }
                }
                else{}
            }
        }
        return !predatorEmpty();
    }

    double Creature::calculateDirection(double y, double x)
    {
        double deltaY=y-positiony;
        double deltaX=x-positionx;
        return equivalentDirection(atan2(deltaY, deltaX));
    }

    double Creature::equivalentDirection(double d)
    {
        return fmod(d+10*PI,2*PI); 
    }

    double Creature::calculateDistance(double y, double x)
    {
        double dis;
        dis=sqrt(pow((y-positiony),2)+pow((x-positionx),2));
        return dis;
    }

    // 1. escape state functions

    State Creature::escapeStateAction(double time)
    {
        removePredator();
        double currentTime=time;
        double dt=currentTime-lastUpdateTime;
        lastUpdateTime=currentTime;
        if(predatorEmpty())
        {
            energy-=specieDataList[type].baseCost*dt;
            return allert;
        }
        else
        {
            lastChangeStateTime=currentTime;
            direction=escapeDirection();
            double speed=specieDataList[type].wanderSpeed;
            if(canRun())
            {
                speed=specieDataList[type].baseRunSpeed;
            }
            double dist=speed*dt;
            double deltaX=dist*cos(direction);
            double deltaY=dist*sin(direction);
            
            if(positionx+deltaX>=database->getWorldWidth())
            {positionx=database->getWorldWidth();}
            else if (positionx+deltaX<=0)
            {positionx=0;}
            else
            {positionx+=deltaX;}
            
            if(positiony+deltaY>=database->getWorldHeight())
            {positiony=database->getWorldHeight();}
            else if(positiony+deltaY<=0)
            {positiony=0;}
            else
            {positiony+=deltaY;}

            energy=energy-specieDataList[type].baseCost*dt-specieDataList[type].moveCost*dist;
            return escape;
        }
    }

    void Creature::removePredator()
    {
        for(auto it=predatorset.begin();it!=predatorset.end(); )
        {
            Creature tempPredator;
            if(database->search(*it, tempPredator)==false)
            {
                it=predatorset.erase(it);
                continue;
            }
            double dis=calculateDistance(tempPredator.getPositionY(), tempPredator.getPositionX());
            if(dis<=specieDataList[type].viewDistance) {it++;}
            else
            {
                it=predatorset.erase(it);
            }
        }
    }

    bool Creature::predatorEmpty()
    {
        return predatorset.empty();
    }

    double Creature::escapeDirection()
    {
        double totalx=0;
        double totaly=0;
        double dist=0;
        Creature tempPredator;
        for(auto it=predatorset.cbegin(); it!=predatorset.cend(); it++)
        {
            database->search(*it, tempPredator);
            dist=calculateDistance(tempPredator.getPositionY(), tempPredator.getPositionX());
            if(dist==0)
            {continue;}
            totaly+=(tempPredator.getPositionY()-positiony)/dist;
            totalx+=(tempPredator.getPositionX()-positionx)/dist;
        }
        double escape=calculateDirection(totaly, totalx);
        return escape;
    }

    // 2. allert state function

    State Creature::allertStateAction(double time)
    {
        double currentTime=time;
        double dt=currentTime-lastUpdateTime;
        lastUpdateTime=currentTime;
        energy-=specieDataList[type].baseCost*dt;
        if(currentTime-lastChangeStateTime>specieDataList[type].allertTime)
        {
            lastChangeStateTime=currentTime;
            return stray;
        }
        else
        {
            return allert;
        }
    }

    // 3. hunt state functions

    State Creature::huntStateAction(double time)
    {
        double currentTime=time;
        double dt=currentTime-lastUpdateTime;
        lastUpdateTime=currentTime;
        Creature tempTarget;
        Grass tempGrass;
        if(grassTarget)
        {
            database->search(target, tempGrass);
        }
        else
        {
            if(!database->search(target, tempTarget))
            {
                lastChangeStateTime=currentTime;
                energy-=specieDataList[type].baseCost*dt;
                return stray;
            }
        }

        direction=huntDirection();
        double speed=specieDataList[type].wanderSpeed;
        if(canRun())
        {speed=specieDataList[type].baseRunSpeed;}
        double movedist=speed*dt;
        qDebug() <<"move distance:" << endl;
        qDebug() << movedist << endl;
        qDebug() << dt << endl;
        if(judgeHuntSuccess(movedist))
        {
            double actualMoveDist=calculateDistance(tempTarget.getPositionY(), tempTarget.getPositionX());
            positionx=tempTarget.getPositionX();
            positiony=tempTarget.getPositionY();
            energy=energy-specieDataList[type].baseCost*dt-actualMoveDist*specieDataList[type].moveCost;
            if(grassTarget)
            {
                double eaten=std::min(tempGrass.getDensity(), grassData.maxDensity);
                database->updateGrassDensity(target, tempGrass.getDensity()-eaten);
                energy+=eaten*grassData.energyAsFood;
                lastChangeStateTime=currentTime;
                return stray;
            }
            else
            {
                energy+=tempTarget.getEnergy()*specieDataList[tempTarget.getType()].valueAsFood;
                database->remove(target);
                lastChangeStateTime=currentTime;
                return stray;
            }
        }
        else
        {
            positionx+=movedist*cos(direction);
            positiony+=movedist*sin(direction);
            energy=energy-specieDataList[type].baseCost*dt-specieDataList[type].moveCost*movedist;
            return hunt;
        }
    }

    double Creature::huntDirection()
    {
        Creature tempTarget;
        database->search(target, tempTarget);
        return calculateDirection(tempTarget.getPositionY(), tempTarget.getPositionX());
    }

    bool Creature::judgeHuntSuccess(double movedist)
    {
        Creature tempTarget;
        database->search(target, tempTarget);       
        double dist=calculateDistance(tempTarget.getPositionY(), tempTarget.getPositionX());
        if(dist<=movedist)
        {return true;}
        else
        {return false;}
    }

    // 4. reproduce state function

    State Creature::reproduceStateAction(double time)
    {
        double currentTime=time;
        double dt=currentTime-lastUpdateTime;
        lastUpdateTime=currentTime;
        if(stopReproduce())
        {
            lastChangeStateTime=currentTime;
            energy-=specieDataList[type].baseCost*dt;
            return stray;
        }
        else
        {
            Creature tempCouple;
            database->search(couple, tempCouple);
            direction=reproduceDirection();
            double movedist=specieDataList[type].wanderSpeed*dt;
            if(movedist<calculateDistance(tempCouple.getPositionY(),tempCouple.getPositionX()))
            {
                creatureAtr childAtr;
                Creature child(childAtr);
                database->insert(child);
                database->updateCreatureEnergy(couple, tempCouple.getEnergy()-specieDataList[type].reproduceCost);
                energy=energy-specieDataList[type].baseCost*dt-specieDataList[type].reproduceCost;
                lastChangeStateTime=currentTime;
                return stray;
            }
            else
            {
                positionx+=movedist*cos(direction);
                positiony+=movedist*sin(direction);
                energy=energy-specieDataList[type].baseCost*dt-specieDataList[type].moveCost*movedist;
                return reproduce;
            }
        }
    }

    bool Creature::stopReproduce()
    {
        Creature tempCouple;
        if(!database->search(couple, tempCouple))
        {return true;}
        else if(tempCouple.getState()!=reproduce)
        {return true;}
        else if(calculateDistance(tempCouple.getPositionY(), tempCouple.getPositionX())>specieDataList[type].viewDistance)
        {return true;}
        else if(energy<0.9*specieDataList[type].minReproduceEnergy)
        {return true;}
        else
        {return false;}
    }

    double Creature::reproduceDirection()
    {
        Creature tempCouple;
        database->search(couple, tempCouple);
        return calculateDirection(tempCouple.getPositionY(), tempCouple.getPositionX());
    }

    // 5. wander state functions

    State Creature::wanderStateAction(double time)
    {
        double currentTime=time;
        double dt=currentTime-lastUpdateTime;
        lastUpdateTime=currentTime;
        if(judgeIfReproduce())
        {
            addPotentialCouple();
            if(chooseCouple())
            {
                energy-=specieDataList[type].baseCost*dt;
                lastChangeStateTime=currentTime;
                return reproduce;
            }
        }

        addPotentialPrey();
        if(!preyEmpty())
        {
            if(choosePrey())
            {
                energy-=specieDataList[type].baseCost*dt;
                lastChangeStateTime=currentTime;
                return hunt;
            }
        }
        
        double moveDistance=specieDataList[type].wanderSpeed*dt;
        varyDirection(moveDistance);
        qDebug() <<"move distance:" << endl;
        qDebug() << moveDistance << endl;
        qDebug() << dt << endl;
        positionx+=moveDistance*cos(direction);
        positiony+=moveDistance*sin(direction);
        energy=energy-specieDataList[type].baseCost*dt-moveDistance*specieDataList[type].moveCost;
        return stray;
    }

    bool Creature::judgeIfReproduce()
    {
        if(age<specieDataList[type].adultAge||energy<specieDataList[type].minReproduceEnergy)
        {return false;}
        else
        {return true;}
    }

    void Creature::addPotentialCouple()
    {
        potentialCouples.clear();
        std::list<int> list={};
        list=database->rangeSearch(positionx, positiony, specieDataList[type].viewDistance);
        for(auto it=list.cbegin(); it!=list.cend(); it++)
        {
            Creature tempCreature;
            if(database->search(*it, tempCreature)==false)
            {
                continue;
            }
            if(tempCreature.getType()==type&&tempCreature.getAge()>specieDataList[type].adultAge
            &&gender!=tempCreature.getGender()&&tempCreature.getState()==stray)
            {
                potentialCouples.push_back(*it);
            }
        }
    }

    bool Creature::chooseCouple()
    {
        for(auto it=potentialCouples.cbegin(); it!=potentialCouples.cend(); it++)
        {
            Creature tempCreature;
            database->search(*it, tempCreature);
            double probability=reproduceProbability(tempCreature.getEnergy(), tempCreature.getPositionX(), tempCreature.getPositionY());
            double prob=getRandom();
            if(prob<probability)
            {
                database->updateCouple(*it, id, reproduce);
                return true;
            }
        }
        return false;
    }

    double Creature::reproduceProbability(double coupleEnergy, double x, double y)
    {
        double prob;
        double factor1=energy/specieDataList[type].minReproduceEnergy;
        double factor2=coupleEnergy/specieDataList[type].minReproduceEnergy;
        double factor3=0.1;
        double distance=calculateDistance(y,x);
        if(distance==0)
        {prob=1;}
        else
        {
            double factor4=specieDataList[type].viewDistance/distance;
            prob=(2/PI)*atan(factor1*factor2*factor3*factor4);
        }
        return prob;
    }

    void Creature::addPotentialPrey()
    {
        std::list<int> list={};
        std::list<int> grasslist={};
        Creature tempCreature;
        list=database->rangeSearch(positionx, positiony, specieDataList[type].viewDistance);
        auto findgrass=specieDataList[type].foods.find(grass);
        if(findgrass!=specieDataList[type].foods.end())
        {
            grasslist=database->rangeSearchGrass(positionx, positiony, specieDataList[type].viewDistance);
        }
        for(auto it=list.cbegin(); it!=list.cend(); it++)
        {
            database->search(*it, tempCreature);
            auto findfood=specieDataList[type].foods.find(tempCreature.getType());
            if(findfood!=specieDataList[type].foods.end())
            {
                potentialPrey.push_back(*it);
            }
        }
        for(auto it=grasslist.cbegin(); it!=grasslist.cend(); it++)
        {
            potentialGrassPrey.push_back(*it);
        }
    }

    bool Creature::choosePrey()
    {
        std::vector<foodCandidate> candidates;
        Creature tempCreature;
        Grass tempGrass;
        for(auto it=potentialPrey.cbegin(); it!=potentialPrey.cend(); it++)
        {
            database->search(*it, tempCreature);
            foodCandidate currCandidate;
            currCandidate.id=*it;
            currCandidate.grassTarget=false;
            currCandidate.attractionValue=calculateAttraction(tempCreature.getType(),tempCreature.getEnergy(), tempCreature.getPositionX(), tempCreature.getPositionY());
            candidates.push_back(currCandidate);
        }
        for(auto it=potentialGrassPrey.cbegin(); it!=potentialGrassPrey.cend(); it++)
        {
            database->search(*it, tempGrass);
            foodCandidate currCandidate;
            currCandidate.id=*it;
            currCandidate.grassTarget=true;
            currCandidate.attractionValue=calculateGrassAttraction(tempGrass.getDensity(), tempGrass.getPositionX(), tempGrass.getPositionY());
            candidates.push_back(currCandidate);
        }
        std::sort(candidates.begin(), candidates.end(), compareFood);
        for(auto it=candidates.cbegin(); it!=candidates.cend(); it++)
        {
            double prob=getRandom();
            double probability=huntProbability(it->id, it->attractionValue);
            if(prob<probability)
            {
                target=it->id;
                if(it->grassTarget)
                {grassTarget=true;}
                return true;
            }
        }
        return false;
    }

    bool Creature::preyEmpty()
    {
        return potentialPrey.empty()&&potentialGrassPrey.empty();
    }

    double Creature::huntProbability(int foodId, double attraction)
    {
        double probability;
        probability=(2/PI)*atan(attraction*size*specieDataList[type].energyFactor/pow(energy,2));
        return probability;
    }

    double Creature::calculateAttraction(Type t, double e, double x, double y)
    {
        double attraction;
        std::list<int> list={};
        list=database->rangeSearch(x, y, 0.5*specieDataList[type].viewDistance);
        int competitor=1;
        Creature tempCreature;
        for(auto it=list.cbegin(); it!=list.cend(); it++)
        {
            database->search(*it, tempCreature);
            auto isPredator=specieDataList[t].predators.find(tempCreature.getType());
            if(isPredator!=specieDataList[t].predators.end())
            {
                competitor++;
            }
        }
        attraction=(specieDataList[t].valueAsFood*e)/sqrt(competitor);
        return attraction;
    }

    double Creature::calculateGrassAttraction(double d, double x, double y)
    {
        double attraction;
        std::list<int> list={};
        list=database->rangeSearch(x, y, 0.5*specieDataList[type].viewDistance);
        int competitor=1;
        Creature tempCreature;
        for(auto it=list.cbegin(); it!=list.cend(); it++)
        {
            database->search(*it, tempCreature);
            auto isPredator=specieDataList[grass].predators.find(tempCreature.getType());
            if(isPredator!=specieDataList[grass].predators.end())
            {
                competitor++;
            }
        }
        attraction=(d*grassData.energyAsFood)/sqrt(competitor);
        return attraction;       
    }

    

    void Creature::varyDirection(double movedist)
    {
        double distToDestination=calculateDistance(wanderDestinationy, wanderDestinationx);
        if(distToDestination<movedist)
        {
            wanderDestinationx=getRandom()*(database->getWorldWidth());
            wanderDestinationy=getRandom()*(database->getWorldHeight());
            direction=calculateDirection(wanderDestinationy, wanderDestinationx);
        }
    }
