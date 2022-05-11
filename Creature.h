#pragma once
#include <set>
#include <vector>
#include <optional>
#include "World.h"
#include "Parameter.h"

struct foodCandidate
{
    int id;
    bool grassTarget;
    double attractionValue;
};

struct creatureAtr
{
    int id;
    Type type;
    Gender gender;
    double positionx;
    double positiony;

    World *database;
};

class Creature
{
public:
    Creature();
    Creature(creatureAtr);
    bool update(double);
    // If the creature is dead, return false
    // control creature's action and state change according to current state and environment
    void afterPause(double time);

    State getState() const;

    Type getType() const;

    double getAge() const;

    Gender getGender() const;

    double getDirection() const;

    double getEnergy() const;

    double getEnergyRatio() const;

    double getPositionX() const;

    double getPositionY() const;

    void setCoupleID(int coupleID);

    void setState(State s);

    void setEnergy(double Energy);

    void setAge(double);

    int getID() const;

    bool canRun() const;

private:
    void move(double);

    double wanderMove(double);

    void grow(double);

    double healthEnergy() const;

    bool judgeDeath();

    bool detectPredator(State);
    // detect if there exists predator in detect range, if exists, add to predator set
    double calculateDirection(double, double);
    // given the predator position, calculate direction
    // atan2 return value in interval -pi, pi; need use equivalentDirection to convert
    double equivalentDirection(double);
    // map direction to 0,2pi interval for comparison
    double calculateDistance(double, double);
    // give the other object position, calculate the distance

    // 1. escape state functions

    State escapeStateAction(double);
    // main function in escape state

    void removePredator();
    bool predatorEmpty();

    double escapeDirection();

    // 2. allert state functions

    State allertStateAction(double);

    // 3. hunt state functions

    State huntStateAction(double);

    double huntDirection();

    bool judgeHuntSuccess(double);

    double energyGain();

    // 4. reproduce state functions

    State reproduceStateAction(double);

    bool stopReproduce();

    double reproduceDirection();

    // 5. wander state functions

    State wanderStateAction(double);

    bool judgeIfReproduce();
    void addPotentialCouple();

    bool chooseCouple();
    double reproduceProbability(double, double, double);
    // energy of potential couple, coordinate of potential couple

    void addPotentialPrey();
    /* in wanderStateAction we need to check if the potentialSet is empty
    after addPotentialPrey, if empty, just skip hunting*/
    bool preyEmpty();
    bool choosePrey();
    double huntProbability(int, double);
    // food id and attraction value
    double calculateAttraction(Type, double, double, double);
    // prey type, energy, positionx, positiony
    double calculateGrassAttraction(double, double, double);
    // density, positionx, positiony

    void varyDirection(double);
    // expect move distance in dt

    int id;

    Type type;

    double energy;
    double direction; // range [0,2pi]
    State state;
    Gender gender;
    double baseSize;
    double age;
    double baseRunSpeed;
    double sizeFactor;
    double size;
    double positionx;
    double positiony;
    double lastUpdateTime;      // 只要更新就记录时间
    double lastChangeStateTime; // 只有状态变化才记录时间
    double wanderDestinationx;
    double wanderDestinationy;

    int target;
    bool grassTarget;

    std::set<int> predatorset;

    std::vector<int> potentialCouples;
    int couple;

    World *database;
};