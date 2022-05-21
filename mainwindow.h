#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include "graph.h"
#include <QFileDialog>
#include <QGraphicsView>
#include <QTimer>
#include "Widgets.h"
#include <chrono>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
// 主窗口
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // 访问三个qwidgets
    Widgets *widgets;
    // 来自后端的“世界”对象，使得能够访问后端
    World *world;

private:
    Ui::MainWindow *ui;
    // 去掉字符串前后的空格
    std::string trim(std::string str);
    // 响应窗口缩放
    void resizeEvent(QResizeEvent *event);
    // 更新widgets中各个widget存的creatureImage_cropped
    QImage paintCroppedImage(int width, int height, QImage sourceImage);
    // graph.h对应qwidget的别名
    graph *overlookGraph;
    // 计时器，控制“世界”的更新频率
    QTimer *timer;
    // 判定当前是否需要绘制“世界”的情况
    bool ifOnDisplay;
    // 判定当前“世界”的更新是否暂停了
    bool ifPause;

private slots:
    // 更新草，牛，老虎的数量
    void updateNumberOfGrass();
    void updateNumberOfCow();
    void updateNumberOfTiger();
    // UI菜单中各个按钮被点击时对应的响应函数
    void on_actionwhite_triggered();
    void on_actionsample_image_triggered();
    void on_actioncustomized_image_triggered();
    void on_actionGrid_triggered();
    void on_actionAxis_triggered();
    void on_actiongrass_triggered();
    void on_actioncow_triggered();
    void on_actiontiger_triggered();
    void on_actionSave_Image_triggered();
    void on_actionage_triggered();
    void on_actionenergy_triggered();
    void on_actionstate_triggered();
    // 开始，停止按钮被点击时响应
    void startAndStopSlot();
    // 暂停，继续按钮被点击时响应
    void pauseAndResumeSlot();
    // 后端中更新世界状态
    void updateWorld();
};
#endif
