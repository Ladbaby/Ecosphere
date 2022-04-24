#ifndef COWUI_H
#define COWUI_H
#include "creatureUI.h"

class cowUI : public creatureUI{
    Q_OBJECT
public:
    cowUI(QWidget* parent) : creatureUI(parent){
        setNumberOfCreature(10);
    }

};
#endif