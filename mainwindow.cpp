#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), overlookGraph(new graph(this)), widgets(new Widgets()), ifOnDisplay(false)
{
    ui->setupUi(this);

    // overlookGraph->database = database;
    widgets->grassWidget = ui->horizontalWidget_grass;
    widgets->cowWidget = ui->horizontalWidget_cow;
    widgets->tigerWidget = ui->horizontalWidget_tiger;

    ui->horizontalWidget_grass->world = world;
    ui->horizontalWidget_cow->world = world;
    ui->horizontalWidget_tiger->world = world;
    overlookGraph->world = world;
    overlookGraph->widgets = widgets;
    // grassWidget = ui->horizontalWidget_grass;
    // cowWidget = ui->horizontalWidget_cow;
    // tigerWidget = ui->horizontalWidget_tiger;

    QPixmap image("");
    double h = ui->icon_grass->height();
    double w = ui->icon_grass->width();
    image.convertFromImage(ui->horizontalWidget_grass->getCreatureImage().scaled(w,h,Qt::KeepAspectRatio));
    ui->icon_grass->setPixmap(image);

    h = ui->icon_cow->height();
    w = ui->icon_cow->width();
    image.convertFromImage(ui->horizontalWidget_cow->getCreatureImage().scaled(w,h,Qt::KeepAspectRatio));
    ui->icon_cow->setPixmap(image);

    h = ui->icon_tiger->height();
    w = ui->icon_tiger->width();
    image.convertFromImage(ui->horizontalWidget_tiger->getCreatureImage().scaled(w,h,Qt::KeepAspectRatio));
    ui->icon_tiger->setPixmap(image);

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
    QObject::connect(ui->startButton,
                    SIGNAL(pressed()),
                    this,
                    SLOT(startAndStopSlot()));
    // QObject::connect(ui->actionBackground,
    //                 SIGNAL(triggered()),
    //                 this,
    //                 SLOT(on_actionBackground_tiggered()));
    // auto overlookGraph = new graph(ui->scrollArea);
    ui->scrollArea->setWidget(overlookGraph);
    // this->overlookGraph = overlookGraph;
    srand((unsigned)time(NULL));
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
    ui->horizontalWidget_grass->setNumberOfCreature(sum);
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
    ui->horizontalWidget_cow->setNumberOfCreature(sum);
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
    ui->horizontalWidget_tiger->setNumberOfCreature(sum);
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

    ui->horizontalWidget_grass->setImageSize(ui->horizontalWidget_grass->getImageSize().scaled(overlookGraph->scale, overlookGraph->scale, Qt::KeepAspectRatioByExpanding));
    ui->horizontalWidget_cow->setImageSize(ui->horizontalWidget_cow->getImageSize().scaled(overlookGraph->width() / 20, overlookGraph->height() / 20, Qt::KeepAspectRatioByExpanding));
    ui->horizontalWidget_tiger->setImageSize(ui->horizontalWidget_tiger->getImageSize().scaled(overlookGraph->width() / 20, overlookGraph->height() / 20, Qt::KeepAspectRatioByExpanding));
}

void MainWindow::on_actionwhite_triggered(){
    overlookGraph->backgroundColor = Qt::white;
    overlookGraph->ifImage = false;
    overlookGraph->repaint();
}
void MainWindow::on_actionsample_image_triggered(){
    overlookGraph->customizedImage.load(":/background.jpg");
    overlookGraph->ifImage = true;
    overlookGraph->repaint();
}
void MainWindow::on_actioncustomized_image_triggered()
{
    //弹出图像选择框，获取图片绝对路径
    QString OpenFile = QFileDialog::getOpenFileName(this,
            "choose an image for the background",
            "//",
            "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
    //不点取消时
    if (OpenFile != "")
    {
        //加载图像并重画
        overlookGraph->customizedImage.load(OpenFile);
        overlookGraph->ifImage = true;
        overlookGraph->repaint();
    }
}
void MainWindow::on_actionGrid_triggered()
{
    overlookGraph->ifGrid = (overlookGraph->ifGrid == true ? false : true);
    overlookGraph->repaint();
}

void MainWindow::on_actionAxis_triggered()
{
    overlookGraph->ifAxis = (overlookGraph->ifAxis == true ? false : true);
    overlookGraph->repaint();
}
void MainWindow::on_actiongrass_triggered(){
    QString OpenFile = QFileDialog::getOpenFileName(this,
            "choose an image for the background",
            "//",
            "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
    //不点取消时
    if (OpenFile != "")
    {
        //加载图像并重画
        ui->horizontalWidget_grass->setCreatureImage(OpenFile);
        QPixmap image("");
        double h = ui->icon_grass->height();
        double w = ui->icon_grass->width();
        image.convertFromImage(ui->horizontalWidget_grass->getCreatureImage().scaled(w,h,Qt::KeepAspectRatio));
        ui->icon_grass->setPixmap(image);
        this->update();
    }
}
void MainWindow::on_actioncow_triggered(){
    QString OpenFile = QFileDialog::getOpenFileName(this,
            "choose an image for the background",
            "//",
            "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
    //不点取消时
    if (OpenFile != "")
    {
        //加载图像并重画
        ui->horizontalWidget_cow->setCreatureImage(OpenFile);
        QPixmap image("");
        double h = ui->icon_cow->height();
        double w = ui->icon_cow->width();
        image.convertFromImage(ui->horizontalWidget_cow->getCreatureImage().scaled(w,h,Qt::KeepAspectRatio));
        ui->icon_cow->setPixmap(image);
        this->update();
    }
}
void MainWindow::on_actiontiger_triggered(){
    QString OpenFile = QFileDialog::getOpenFileName(this,
            "choose an image for the background",
            "//",
            "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
    //不点取消时
    if (OpenFile != "")
    {
        //加载图像并重画
        ui->horizontalWidget_tiger->setCreatureImage(OpenFile);
        QPixmap image("");
        double h = ui->icon_tiger->height();
        double w = ui->icon_tiger->width();
        image.convertFromImage(ui->horizontalWidget_tiger->getCreatureImage().scaled(w,h,Qt::KeepAspectRatio));
        ui->icon_tiger->setPixmap(image);
        this->update();
    }
}
void MainWindow::on_actionSave_Image_triggered(){
    //弹出保存位置的选择框，顺便获取绝对路径
    QString filePath = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG (*.png);;JPEG (*.jpg *jpeg);;All files(*.*)");
    //点了取消按钮
    if(filePath == "")
        return;
    //调用paintEvent绘制图片
    overlookGraph->ifSave = true;
    overlookGraph->repaint();
    overlookGraph->ifSave = false;
    //保存
    overlookGraph->background.save(filePath);
}
void MainWindow::startAndStopSlot(){
    if (!ifOnDisplay){
        world = new World(192, 108);
        overlookGraph->world = world;
        // double currentTime = (double) (std::chrono::steady_clock::now().time_since_epoch().count() / 1000000000.0);
        for (int i = 0; i < widgets->cowWidget->getNumberOfCreature(); ++i){
            int cid = world->allocate();
            int cgender = (int) rand() % 2;
            if (cgender == 0){
                creatureAtr cowAtr = {
                    .id = cid,
                    .type = cow,
                    .energy = 100,
                    .gender = male,
                    .age = rand() / double(RAND_MAX) * 15,
                    .positionx = rand() / double(RAND_MAX) * 192,
                    .positiony = rand() / double(RAND_MAX) * 108,
                    .database = world,
                    // .time = currentTime
                };
                Creature cowTemp(cowAtr);
                world->insert(cowTemp);
            }
            else{
                creatureAtr cowAtr = {
                    .id = cid,
                    .type = cow,
                    .energy = 100,
                    .gender = female,
                    .age = rand() / double(RAND_MAX) * 15,
                    .positionx = rand() / double(RAND_MAX) * 192,
                    .positiony = rand() / double(RAND_MAX) * 108,
                    .database = world,
                    // .time = currentTime
                };
                Creature cowTemp(cowAtr);
                world->insert(cowTemp);
            }
        }
        for (int i = 0; i < widgets->tigerWidget->getNumberOfCreature(); ++i){
            int cid = world->allocate();
            int cgender = (int) rand() % 2;
            if (cgender == 0){
                creatureAtr tigerAtr = {
                    .id = cid,
                    .type = tiger,
                    .energy = 100,
                    .gender = male,
                    .age = rand() / double(RAND_MAX) * 15,
                    .positionx = rand() / double(RAND_MAX) * 192,
                    .positiony = rand() / double(RAND_MAX) * 108,
                    .database = world,
                    // .time = currentTime
                };
                Creature tigerTemp(tigerAtr);
                world->insert(tigerTemp);
            }
            else{
                creatureAtr tigerAtr = {
                    .id = cid,
                    .type = tiger,
                    .energy = 100,
                    .gender = female,
                    .age = rand() / double(RAND_MAX) * 15,
                    .positionx = rand() / double(RAND_MAX) * 192,
                    .positiony = rand() / double(RAND_MAX) * 108,
                    .database = world,
                    // .time = currentTime
                };
                Creature tigerTemp(tigerAtr);
                world->insert(tigerTemp);
            }
        }
    }
    timer = new QTimer();
    timer->setInterval(1000);
    
    QObject::connect(timer,
                    SIGNAL(timeout()),
                    this,
                    SLOT(updateWorld()));

    ifOnDisplay = !ifOnDisplay;
    overlookGraph->ifOnDisplay = !overlookGraph->ifOnDisplay;
    // qDebug() << "fuck1" << endl;
    overlookGraph->repaint();
    timer->start();
}

void MainWindow::updateWorld(){
    
    double currentTime = (double) (std::chrono::steady_clock::now().time_since_epoch().count() / 1000000000.0);
    // qDebug() << currentTime << endl;
    world->updateAll(currentTime);
    overlookGraph->repaint();
    // qDebug() << "fuck2" << endl;
}