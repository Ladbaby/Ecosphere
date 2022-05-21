#ifndef COWUI_H
#define COWUI_H
#include "creatureUI.h"

// 继承自creatureUI的牛的qwidget
class cowUI : public creatureUI{
    Q_OBJECT
public:
    cowUI(QWidget* parent) : creatureUI(parent){
        // 默认初始数量为10
        setNumberOfCreature(10);
        // 预加载默认头像
        setCreatureImage(QString::fromUtf8(":/oceancat.jpg"));
        // 初始化imageSize
        setImageSize(getCreatureImage().size());
    }

};
#endif