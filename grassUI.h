#ifndef GRASSUI_H
#define GRASSUI_H
#include "creatureUI.h"
// 继承自creatureUI的草的qwidget
class grassUI : public creatureUI{
    Q_OBJECT
public:
    grassUI(QWidget* parent) : creatureUI(parent){
        // 预加载草对应的图片
        setCreatureImage(QString::fromUtf8(":/grass_word.png"));
        // 初始化imageSize
        setImageSize(getCreatureImage().size());
        // 顺手初始化一下grassDensity，虽然是多此一举
        grassDensity = 0.0;
    }
    // 草独有的属性，表示其密度
    double grassDensity;
};
# endif