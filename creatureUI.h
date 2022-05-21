#ifndef CREATUREUI_H
#define CREATUREUI_H
#include <QWidget>
#include <string>
#include <QDebug>
#include "World.h"

// grassUI, cowUI, tigerUI的基类，继承自qwidget，是UI中三个控制面板的所属类
class creatureUI : public QWidget{
    Q_OBJECT
public:
    creatureUI(QWidget* parent) : QWidget(parent){
        // 预加载arrowImage
        arrowImage.load(QString::fromUtf8(":/arrow.png"));
    }
    // 数据成员numberOfCreature的set和get函数
    void setNumberOfCreature(int n){
        numberOfCreature = n;
    }
    const int getNumberOfCreature()const{
        return numberOfCreature;
    }
    // 数据成员creatureImage的set和get函数
    void setCreatureImage(const QString &str){
        creatureImage.load(str);
    }
    void setCreatureImage(const QImage &i){
        creatureImage = i;
    }
    const QImage getCreatureImage()const{
        return creatureImage;
    }
    // 数据成员imageSize的set和get函数
    void setImageSize(const QSize &s){
        imageSize = s;
    }
    QSize getImageSize(){
        return imageSize;
    }
    // 数据成员creatureImage_cropped的set和get函数
    void setImage_cropped(const QImage &i){
        creatureImage_cropped = i;
    }
    const QImage getImage_cropped() const{
        return creatureImage_cropped;
    }
    // 返回arrowImage
    const QImage getArrowImage() const{
        return arrowImage;
    }
    // 数据成员smallerEdge的set和get函数
    void setSmallerEdge(int s){
        smallerEdge = s;
    }
    const int getSmallerEdge() const{
        return smallerEdge;
    }
    // 数据成员numberOfMale的set和get函数
    void setNumberOfMale(const int &m){
        numberOfMale = m;
    }
    const int getNumberOfMale()const{
        return numberOfMale;
    }
    // 来自后端的“世界”对象，使得能够访问后端
    World* world;
private:
    // 该物种的数量（对草而言为无用属性）
    int numberOfCreature;
    // 该物种中雄性的数量（对草而言为无用属性）
    int numberOfMale;
    // 可被用户自定义化的 该物种对应的头像图片
    QImage creatureImage;
    // creatureImage被裁切成圆形之后的图像
    QImage creatureImage_cropped;
    // 表示个体的运动方向的箭头
    QImage arrowImage;
    // creatureImage_cropped的外接矩形的边长
    QSize imageSize;
    // creatureImage中较短边的长度
    int smallerEdge;
    
};
#endif