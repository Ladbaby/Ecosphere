#ifndef TIGERUI_H
#define TIGERUI_H
#include "creatureUI.h"

// 继承自creatureUI的老虎的qwidget
class tigerUI : public creatureUI{
    Q_OBJECT
public:
    tigerUI(QWidget* parent) : creatureUI(parent){
        // 默认初始数量为1
        setNumberOfCreature(1);
        // 预加载头像
        setCreatureImage(QString::fromUtf8(":/doge.jpg"));
        // 初始化imageSize
        setImageSize(getCreatureImage().size());
    }

};
#endif