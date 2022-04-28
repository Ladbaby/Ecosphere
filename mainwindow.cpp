#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), overlookGraph(new graph(this)), database(new D())
{
    ui->setupUi(this);
    overlookGraph->database = database;
    database->grassWidget = ui->horizontalWidget_grass;
    database->cowWidget = ui->horizontalWidget_cow;
    database->tigerWidget = ui->horizontalWidget_tiger;
    QObject::connect(ui->lineEdit_grass,
                    SIGNAL(returnPressed()),
                    this,
                    SLOT(updateNumberOfGrass()));
    QObject::connect(ui->lineEdit_cow,
                    SIGNAL(returnPressed()),
                    this,
                    SLOT(updateNumberOfCow()));
    QObject::connect(ui->lineEdit_tiger,
                    SIGNAL(returnPressed()),
                    this,
                    SLOT(updateNumberOfTiger()));
    // auto overlookGraph = new graph(ui->scrollArea);
    ui->scrollArea->setWidget(overlookGraph);
    // this->overlookGraph = overlookGraph;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateNumberOfGrass(){
    std::string inputString = ui->lineEdit_grass->text().toStdString();
    std::string tempString = trim(inputString);
    int sum = 0;
    if(tempString.length() == 0)
        return;
    for(int i = 0; i < tempString.length(); ++i){
        int tempNumber = tempString[i] - '0';
        if(tempNumber >=0 && tempNumber <=9){
            sum = sum * 10 + tempNumber;
        }
        else
            return;
    }
    database->grassWidget->setNumberOfCreature(sum);
    tempString = "number: " + tempString;
    ui->label_grass->setText(QString::fromStdString(tempString));
    qDebug() << sum << endl;
}

void MainWindow::updateNumberOfCow(){
    std::string inputString = ui->lineEdit_cow->text().toStdString();
    std::string tempString = trim(inputString);
    int sum = 0;
    if(tempString.length() == 0)
        return;
    for(int i = 0; i < tempString.length(); ++i){
        int tempNumber = tempString[i] - '0';
        if(tempNumber >=0 && tempNumber <=9){
            sum = sum * 10 + tempNumber;
        }
        else
            return;
    }
    database->cowWidget->setNumberOfCreature(sum);
    tempString = "number: " + tempString;
    ui->label_cow->setText(QString::fromStdString(tempString));
    qDebug() << sum << endl;
}

void MainWindow::updateNumberOfTiger(){
    std::string inputString = ui->lineEdit_tiger->text().toStdString();
    std::string tempString = trim(inputString);
    int sum = 0;
    if(tempString.length() == 0)
        return;
    for(int i = 0; i < tempString.length(); ++i){
        int tempNumber = tempString[i] - '0';
        if(tempNumber >=0 && tempNumber <=9){
            sum = sum * 10 + tempNumber;
        }
        else
            return;
    }
    database->tigerWidget->setNumberOfCreature(sum);
    tempString = "number: " + tempString;
    ui->label_tiger->setText(QString::fromStdString(tempString));
    qDebug() << sum << endl;
}

std::string MainWindow::trim(std::string str){
    //删除0到第一个不是空格的字符
    str.erase(0, str.find_first_not_of(" "));
    //删除最后一个不是空格的字符到字符串结尾
    str.erase(str.find_last_not_of(" ")+1, str.length());
    return str;
}

void MainWindow::resizeEvent(QResizeEvent *event){
    //重新设置坐标原点位置，并保持原点相对窗口的位置不变
    overlookGraph->painter.setViewport(overlookGraph->viewPort1.x() * overlookGraph->width(),
                        overlookGraph->viewPort1.y() * overlookGraph->height(),
                        overlookGraph->width(),
                        overlookGraph->height());
    //更新图像窗口的宽高信息
    overlookGraph->graphW = overlookGraph->width();
    overlookGraph->graphH = overlookGraph->height();
    ui->verticalWidget->resize(frameGeometry().size());
    // 更新动物图片大小 为opengl窗口的1/20

    database->grassWidget->setImageSize(database->grassWidget->getImageSize().scaled(overlookGraph->width() / 20, overlookGraph->height() / 20, Qt::KeepAspectRatioByExpanding));
    database->cowWidget->setImageSize(database->cowWidget->getImageSize().scaled(overlookGraph->width() / 20, overlookGraph->height() / 20, Qt::KeepAspectRatioByExpanding));
    database->tigerWidget->setImageSize(database->tigerWidget->getImageSize().scaled(overlookGraph->width() / 20, overlookGraph->height() / 20, Qt::KeepAspectRatioByExpanding));
}