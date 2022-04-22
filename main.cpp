#pragma execution_character_set("utf-8")

#include "frmbattery.h"
#include <QApplication>
#include <QTextCodec>

#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // QFont font;
    // font.setFamily("Microsoft Yahei");
    // font.setPixelSize(13);
    // a.setFont(font);

    // QTextCodec *codec = QTextCodec::codecForName("utf-8");
    // QTextCodec::setCodecForLocale(codec);

    // frmBattery w;
    // w.setWindowTitle("Data Structure");
    // w.show();
    MainWindow mainWindow;
    mainWindow.setWindowTitle("Ecosphere");
    mainWindow.show();

    return a.exec();
}
