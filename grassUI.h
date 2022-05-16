#ifndef GRASSUI_H
#define GRASSUI_H
#include "creatureUI.h"

class grassUI : public creatureUI{
    Q_OBJECT
public:
    grassUI(QWidget* parent) : creatureUI(parent){
        setNumberOfCreature(100);
        setCreatureImage(QString::fromUtf8(":/grass_word.png"));
        setCreatureImage(getCreatureImage().convertToFormat(QImage::Format_ARGB32));
        setImageSize(getCreatureImage().size());
        grassDensity = 0.0;
    }
    double grassDensity;
};
# endif