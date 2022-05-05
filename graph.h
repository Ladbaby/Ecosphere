#ifndef GRAPH_H
#define GRAPH_H

#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QColor>
#include <QPainterPath>
#include <QDebug>
#include <stdlib.h>
#include <time.h>
#include "Widgets.h"
#include "World.h"
#include "Creature.h"
#include "Grass.h"
// #include "mainwindow.h"

//自定义图像显示区域的QOpenGLWidget
class graph : public QOpenGLWidget
{
    Q_OBJECT
public:
    graph(QWidget *parent);
    //主力画笔
    QPainter painter;
    //viewPort的原点位置（也就是坐标轴原点）与窗口大小的比值，便于控制缩放时原点相对于窗口的位置不变
    QPointF viewPort1;
    //记录此时图像窗口的宽高
    double graphW;
    double graphH;
    //图像，在保存图片时使用
    QImage background;
    //背景颜色
    QColor backgroundColor = Qt::white;
    //用户自定义的背景图片
    QImage customizedImage;
    Widgets *widgets;
    World *world;
    // Ui::MainWindow *ui;
    //判定是否有customizedImage
    bool ifImage = false;
    //判定鼠标是否按下并拖拽
    bool ifDrag = false;
    //记录是否需要显示网格
    bool ifGrid = true;
    //记录是否需要坐标系
    bool ifAxis = true;
    //记录Save按钮是否被触发
    bool ifSave = false;
    //是否显示关键点
    bool ifPoint = false;
    //判定是否渲染的为第一帧，用以初始化viewPort1
    bool firstRender = true;
    bool ifOnDisplay = false;
    
    //记录图像窗口的坐标数字和像素之间的变换倍率
    //每1个坐标数字对应于scale个像素
    int scale = 10;
private:
    //把paintEvent里重复的代码抽象出来
    void paintGraph(QPainter &painter);
    //鼠标上一帧时的坐标位置
    QPointF pressPosition;
    

public slots:
    //响应鼠标事件，实现拖动图像
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    //响应滚轮事件，实现缩放图像
    void wheelEvent(QWheelEvent *event);
    //渲染图像窗口的每一帧
    void paintEvent(QPaintEvent *event);
};

#endif