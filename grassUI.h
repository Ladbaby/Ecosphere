#ifndef GRASSUI_H
#define GRASSUI_H
#include "creatureUI.h"

class grassUI : public creatureUI{
    Q_OBJECT
public:
    grassUI(QWidget* parent) : creatureUI(parent){
        setNumberOfCreature(100);
        setCreatureImage(QString::fromUtf8(":/grass_word.png"));
        setImageSize(getCreatureImage().size());
    }

};
# endif