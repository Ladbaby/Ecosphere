#ifndef TIGERUI_H
#define TIGERUI_H
#include "creatureUI.h"

class tigerUI : public creatureUI{
    Q_OBJECT
public:
    tigerUI(QWidget* parent) : creatureUI(parent){
        setNumberOfCreature(1);
        setCreatureImage(QString::fromUtf8(":/doge.jpg"));
        setImageSize(getCreatureImage().size());
    }

};
#endif