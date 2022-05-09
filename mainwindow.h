#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// #include "grassUI.h"
// #include "cowUI.h"
// #include "tigerUI.h"
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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Widgets *widgets;
    World *world;
    // grassUI *grassWidget;
    // cowUI *cowWidget;
    // tigerUI * tigerWidget;

private:
    Ui::MainWindow *ui;
    std::string trim(std::string str);
    void resizeEvent(QResizeEvent *event);
    QImage paintCroppedImage(int width, int height, QImage sourceImage);
    graph *overlookGraph;
    QTimer *timer;
    bool ifOnDisplay;
    bool ifPause;

private slots:
    void updateNumberOfGrass();
    void updateNumberOfCow();
    void updateNumberOfTiger();
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
    void startAndStopSlot();
    void pauseAndResumeSlot();
    void updateWorld();
};
#endif // MAINWINDOW_H
