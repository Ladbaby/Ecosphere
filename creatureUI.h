#ifndef CREATUREUI_H
#define CREATUREUI_H
#include <QWidget>

class creatureUI{
    Q_OBJECT

public:
    void setNumberOfCreature(int n){
        numberOfCreature = n;
    }
    const int getNumberOfCreature()const{
        return numberOfCreature;
    }

private:
    int numberOfCreature;

// private slots:
//     virtual void initForm();

};
#endif