#ifndef TIGERUI_H
#define TIGERUI_H
#include "creatureUI.h"

class tigerUI : public creatureUI{
    Q_OBJECT
public:
    tigerUI(QWidget* parent) : creatureUI(parent){
        setNumberOfCreature(1);
    }

};
#endif