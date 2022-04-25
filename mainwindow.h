#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// #include "grassUI.h"
// #include "cowUI.h"
// #include "tigerUI.h"
#include <string>
#include "graph.h"
// #include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    D *database;

private:
    Ui::MainWindow *ui;
    std::string trim(std::string str);
    void resizeEvent(QResizeEvent *event);
    graph *overlookGraph;

private slots:
    void updateNumberOfGrass();
    void updateNumberOfCow();
    void updateNumberOfTiger();
};
#endif // MAINWINDOW_H
