#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "grassUI.h"
#include "cowUI.h"
#include "tigerUI.h"
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    grassUI *grassWidget;
    cowUI *cowWidget;
    tigerUI *tigerWidget;
    std::string trim(std::string str);

private slots:
    void updateNumberOfGrass();
    void updateNumberOfCow();
    void updateNumberOfTiger();
};
#endif // MAINWINDOW_H
