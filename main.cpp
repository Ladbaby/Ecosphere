#pragma execution_character_set("utf-8")

#include <QApplication>
#include <QTextCodec>

#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 创建程序UI主窗口
    MainWindow mainWindow;
    // 设定窗口的标题名字
    mainWindow.setWindowTitle("Ecosphere");
    mainWindow.show();

    return a.exec();
}
