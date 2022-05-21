#include "graph.h"
#include "mainwindow.h"

graph::graph(QWidget* parent) : QOpenGLWidget(parent){}

void graph::paintEvent(QPaintEvent* event) {
    //由于QImage对性能有较大影响，为了提高性能，分两种方法渲染
    //平时不使用QImage而直接画在widget上
    if (!ifSave) {
        //给图像窗口创建一个画笔
        QPainter painter(this);
        //设置绘制图像的抗锯齿属性
        painter.setRenderHint(QPainter::Antialiasing);
        //裁切圆角，并填充空白部分为灰色以达成圆角效果
        painter.fillRect(this->rect(), QColor(205, 205, 205));
        QPainterPath path;
        path.addRoundedRect(this->rect(), 30, 30);
        painter.setClipPath(path);
        //调用绘图函数
        paintGraph(painter);
    }
    else {//保存图片时临时使用QImage渲染
        background = QImage(this->size(), QImage::Format_RGB32);
        //给图像窗口创建一个画笔
        QPainter painter(&background);
        //设置绘制图像的抗锯齿属性
        painter.setRenderHint(QPainter::Antialiasing);
        paintGraph(painter);
        //把background画到widget上
        QPainter canvasPainter(this);
        canvasPainter.setRenderHint(QPainter::Antialiasing);
        //保持该帧仍然为圆角
        canvasPainter.fillRect(this->rect(), QColor(205, 205, 205));
        QPainterPath path;
        path.addRoundedRect(this->rect(), 30, 30);
        canvasPainter.setClipPath(path);
        canvasPainter.drawImage(this->rect(), background, background.rect());
    }
}

void graph::paintGraph(QPainter& painter) {
    //画背景
    //用图片作背景的情况
    if (ifImage) {
        customizedImage = customizedImage.scaled(this->width(), this->height(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        painter.drawImage(QPoint(0, 0), customizedImage);
    }
    else {//颜色作背景的情况
        painter.fillRect(this->rect(), backgroundColor);
    }
    //设定viewPort
    if (firstRender) {//初始化viewPort1，若放在MainWindow的构造器中初始化将得到错误的图像窗口宽高信息
        this->viewPort1 = QPointF(0.01, 0.99);
        this->graphW = this->width();
        this->graphH = this->height();
        this->scale = 10;
        firstRender = false;
    }
    painter.setViewport(this->viewPort1.x() * this->width(), this->viewPort1.y() * this->height(), this->width(), this->height());

    //开始画网格
    //设置刻度数字的字体
    QFont font("Microsoft YaHei UI", 10, QFont::Bold, true);
    painter.setFont(font);
    //控制轴的刻线最多为15个
    int upperLimit = (this->height() / scale) / 15;
    //防止出现除数为0
    if (upperLimit == 0) {
        upperLimit = 1;
    }
    if (ifGrid) {//判定是否需要画网格
        //垂直x轴的竖线及刻度数字
        for (int c = (-1) * this->viewPort1.x() * this->width() / scale;
            c <= (1 - this->viewPort1.x()) * this->width() / scale;
            ++c) {//只画显示区域
            if (c % upperLimit == 0) {
                //线的部分
                if (c % 5 != 0) {
                    painter.setPen(QPen(QColor("#E3E3E3"), 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                }
                else {//每5个线就加深加粗
                    painter.setPen(QPen(QColor("#AAAAAA"), 3, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                }
                painter.drawLine(QPoint(c * scale, this->viewPort1.y() * this->height() * (-1)), QPointF(c * scale, (1 - this->viewPort1.y()) * this->height()));
                //刻度数字部分
                painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                if (ifAxis) {//有坐标轴才画刻度数字
                    //实现坐标轴超界时刻度悬浮于边界
                    if ((viewPort1.y() - 1) * height() >= -70) {//x轴超出显示区域下界
                        painter.drawText(QPoint(c * scale - 40, (1 - viewPort1.y()) * height() - 35), QString::number(c));
                    }
                    else if (viewPort1.y() <= 0) {//x轴超出显示区域上界
                        painter.drawText(QPoint(c * scale - 40, (-1) * viewPort1.y() * height() + 35), QString::number(c));
                    }
                    else {
                        painter.drawText(QPoint(c * scale - 40, 35), QString::number(c));
                    }
                }
            }
        }
        //垂直y轴横线及刻度数字
        for (int c = (-1) * this->viewPort1.y() * this->height() / scale;
            c <= (1 - this->viewPort1.y()) * this->height() / scale;
            ++c) {
            if (c % upperLimit == 0) {
                if (c % 5 != 0) {
                    painter.setPen(QPen(QColor("#E3E3E3"), 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                }
                else {
                    painter.setPen(QPen(QColor("#AAAAAA"), 3, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                }
                painter.drawLine(QPoint(this->viewPort1.x() * this->width() * (-1), c * scale), QPointF((1 - this->viewPort1.x()) * this->width(), c * scale));
                painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                if (ifAxis && c != 0) {
                    if (viewPort1.x() >= 1) {
                        painter.drawText(QPoint((1 - viewPort1.x()) * width() - 50, c * scale - 5), QString::number(-c));
                    }
                    else if (viewPort1.x() * width() <= 100) {
                        painter.drawText(QPoint((-1) * viewPort1.x() * width() + 50, c * scale - 5), QString::number(-c));
                    }
                    else {
                        painter.drawText(QPoint(-50, c * scale - 5), QString::number(-c));
                    }
                }
            }
        }
    }
    else if (ifAxis) {//不需要网格但需要坐标轴的情况，这里先画刻度线
        painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        //垂直x轴的竖线及刻度数字
        for (int c = (-1) * this->viewPort1.x() * this->width() / scale;c <= (1 - this->viewPort1.x()) * this->width() / scale;++c) {
            if (c % upperLimit == 0) {
                painter.drawLine(QPoint(c * scale, 0), QPointF(c * scale, 10));
                if ((viewPort1.y() - 1) * height() >= -70) {
                    painter.drawText(QPoint(c * scale - 40, (1 - viewPort1.y()) * height() - 35), QString::number(c));
                }
                else if (viewPort1.y() <= 0) {
                    painter.drawText(QPoint(c * scale - 40, (-1) * viewPort1.y() * height() + 35), QString::number(c));
                }
                else {
                    painter.drawText(QPoint(c * scale - 40, 35), QString::number(c));
                }
            }
        }
        //垂直y轴的横线及刻度数字
        for (int c = (-1) * this->viewPort1.y() * this->height() / scale;c <= (1 - this->viewPort1.y()) * this->height() / scale;++c) {
            if (c != 0 && c % upperLimit == 0) {
                painter.drawLine(QPoint(0, c * scale), QPointF(-10, c * scale));
                if (viewPort1.x() >= 1) {
                    painter.drawText(QPoint((1 - viewPort1.x()) * width() - 50, c * scale - 5), QString::number(-c));
                }
                else if (viewPort1.x() * width() <= 100) {
                    painter.drawText(QPoint((-1) * viewPort1.x() * width() + 50, c * scale - 5), QString::number(-c));
                }
                else {
                    painter.drawText(QPoint(-50, c * scale - 5), QString::number(-c));
                }
            }
        }

    }

    //开始画坐标系的线
    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    if (ifAxis) {
        //x轴
        painter.drawLine(QPointF(this->viewPort1.x() * this->width() * (-1), 0),
            QPointF((1 - this->viewPort1.x()) * this->width(), 0));
        //x轴的箭头
        painter.drawLine(QPointF((1 - this->viewPort1.x()) * this->width() - 10, -10),
            QPointF((1 - this->viewPort1.x()) * this->width(), 0));
        painter.drawLine(QPointF((1 - this->viewPort1.x()) * this->width() - 10, 10),
            QPointF((1 - this->viewPort1.x()) * this->width(), 0));
        //y轴
        painter.drawLine(QPointF(0, this->viewPort1.y() * this->height() * (-1)),
            QPointF(0, (1 - this->viewPort1.y()) * this->height()));
        //y轴的箭头
        painter.drawLine(QPointF(-10, this->viewPort1.y() * this->height() * (-1) + 10),
            QPointF(0, this->viewPort1.y() * this->height() * (-1)));
        painter.drawLine(QPointF(10, this->viewPort1.y() * this->height() * (-1) + 10),
            QPointF(0, this->viewPort1.y() * this->height() * (-1)));
    }
    // 开始绘制“世界”的情况
    if (ifOnDisplay) {
        // 统计草格子的数量
        int grassNumber = 0;
        // 所有草格子的密度之和，方便后续求平均
        int grassDensitySum = 0;
        for (auto it = world->grassBegin(); it != world->grassEnd(); it++) {// 迭代器拿到后端中所有的草
            painter.save();
            // 草的密度对应于图片的透明度
            painter.setOpacity(it->second.getDensity() / grassData.maxDensity);
            // 画草
            painter.drawImage(QRectF(QPointF((it->second.getPositionX() - 0.5) * scale, (it->second.getPositionY() + 0.5) * scale * (-1)), widgets->grassWidget->getImageSize()), widgets->grassWidget->getCreatureImage());
            painter.restore();
            grassNumber++;
            grassDensitySum += it->second.getDensity();
        }
        // 更新UI的控制面板中显示的所有草的平均密度
        widgets->grassWidget->grassDensity = (double) grassDensitySum / (double) grassNumber;

        // 统计牛，老虎的数量
        int cowNumber = 0;
        int tigerNumber = 0;
        // 统计牛，老虎中的雌雄比例
        int cowNumber_male = 0;
        int tigerNumber_male = 0;
        for (auto it = world->creatureBegin(); it != world->creatureEnd(); it++) {// 拿到后端中的所有“动物”的迭代器，包含了牛和老虎
            if (it->second.getType() == cow) {
                cowNumber++;
                // 画牛的头像
                painter.drawImage(QPointF(it->second.getPositionX() * scale - widgets->cowWidget->getSmallerEdge() / 2, ((it->second.getPositionY()) * scale + widgets->cowWidget->getSmallerEdge() / 2) * (-1)), widgets->cowWidget->getImage_cropped());
                painter.save();
                // 画牛的运动方向
                painter.setViewport(it->second.getPositionX() * scale + viewPort1.x() * this->width(), it->second.getPositionY() * scale * (-1) + viewPort1.y() * this->height(), this->width(), this->height());
                painter.rotate(it->second.getDirection() / 3.14 * 180 * (-1));
                painter.drawImage(QRectF(QPointF(widgets->cowWidget->getSmallerEdge() / 2, widgets->cowWidget->getSmallerEdge() / 2 * (-1) * 0.5), QPointF(widgets->cowWidget->getSmallerEdge() * 0.7, widgets->cowWidget->getSmallerEdge() / 2 * 0.5)), widgets->cowWidget->getArrowImage());
                painter.restore();
                // 画性别标识的圈圈
                painter.save();
                if (it->second.getGender() == male) {// 雄性为蓝色
                    painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                    cowNumber_male++;
                }
                else {// 雌性为红色
                    painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                }
                painter.drawEllipse(QPointF(it->second.getPositionX() * scale, ((it->second.getPositionY()) * scale) * (-1)), widgets->cowWidget->getSmallerEdge() / 2, widgets->cowWidget->getSmallerEdge() / 2);
                painter.restore();
            }
            else if (it->second.getType() == tiger) {
                // 老虎与牛同理
                tigerNumber++;
                painter.drawImage(QPointF(it->second.getPositionX() * scale - widgets->tigerWidget->getSmallerEdge() / 2, ((it->second.getPositionY()) * scale + widgets->tigerWidget->getSmallerEdge() / 2) * (-1)), widgets->tigerWidget->getImage_cropped());
                painter.save();
                painter.setViewport(it->second.getPositionX() * scale + viewPort1.x() * this->width(), it->second.getPositionY() * scale * (-1) + viewPort1.y() * this->height(), this->width(), this->height());
                painter.rotate(it->second.getDirection() / 3.14 * 180 * (-1));
                painter.drawImage(QRectF(QPointF(widgets->tigerWidget->getSmallerEdge() / 2, widgets->tigerWidget->getSmallerEdge() / 2 * (-1) * 0.5), QPointF(widgets->tigerWidget->getSmallerEdge() * 0.7, widgets->tigerWidget->getSmallerEdge() / 2 * 0.5)), widgets->tigerWidget->getArrowImage());
                painter.restore();
                // 画性别标识的圈圈
                painter.save();
                if (it->second.getGender() == male) {// 雄性为蓝色
                    painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                    tigerNumber_male++;
                }
                else {// 雌性为红色
                    painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                }
                painter.drawEllipse(QPointF(it->second.getPositionX() * scale, ((it->second.getPositionY()) * scale) * (-1)), widgets->cowWidget->getSmallerEdge() / 2, widgets->cowWidget->getSmallerEdge() / 2);
                painter.restore();
            }
            // 判断是否需要画动物的“能量”
            if (ifEnergy) {
                // 标识能量数值
                painter.drawText(QPointF(it->second.getPositionX() * scale - widgets->cowWidget->getSmallerEdge() / 2, ((it->second.getPositionY()) * scale + widgets->cowWidget->getSmallerEdge() / 2) * (-1)), QString::fromStdString("energy:" + std::to_string(it->second.getEnergyRatio())));
            }
            // 判断是否需要画动物的“年龄”
            if (ifAge) {
                painter.drawText(QPointF(it->second.getPositionX() * scale + widgets->cowWidget->getSmallerEdge() / 2, ((it->second.getPositionY()) * scale - widgets->cowWidget->getSmallerEdge() / 2) * (-1)), QString::fromStdString("age:" + std::to_string(it->second.getAge())));
            }
            // 判断是否需要画动物的“状态”
            if (ifState) {
                switch (it->second.getState())
                {
                case stray:// 散步
                    painter.drawText(QPointF(it->second.getPositionX() * scale + widgets->cowWidget->getSmallerEdge() / 2, ((it->second.getPositionY()) * scale) * (-1)), QString::fromStdString("stage:stray"));
                    break;
                case hunt:// 猎食
                    painter.drawText(QPointF(it->second.getPositionX() * scale + widgets->cowWidget->getSmallerEdge() / 2, ((it->second.getPositionY()) * scale) * (-1)), QString::fromStdString("stage:hunt"));
                    break;
                case escape:// 逃跑
                    painter.drawText(QPointF(it->second.getPositionX() * scale + widgets->cowWidget->getSmallerEdge() / 2, ((it->second.getPositionY()) * scale) * (-1)), QString::fromStdString("stage:escape"));
                    break;
                case allert:// 警戒
                    painter.drawText(QPointF(it->second.getPositionX() * scale + widgets->cowWidget->getSmallerEdge() / 2, ((it->second.getPositionY()) * scale) * (-1)), QString::fromStdString("stage:allert"));
                    break;
                case reproduce:// 繁殖
                    painter.drawText(QPointF(it->second.getPositionX() * scale + widgets->cowWidget->getSmallerEdge() / 2, ((it->second.getPositionY()) * scale) * (-1)), QString::fromStdString("stage:reproduce"));
                    break;
                default:
                    break;
                }
            }
        }
        // 更新牛和老虎在UI中显示的数量
        widgets->cowWidget->setNumberOfCreature(cowNumber);
        widgets->cowWidget->setNumberOfMale(cowNumber_male);
        widgets->tigerWidget->setNumberOfCreature(tigerNumber);
        widgets->tigerWidget->setNumberOfMale(tigerNumber_male);
    }


}

void graph::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {//是否是左键点击
        ifDrag = true;
        //记录鼠标按下的位置
        pressPosition = event->pos();
    }
}
void graph::mouseMoveEvent(QMouseEvent* event) {
    if ((event->buttons() & Qt::LeftButton) && ifDrag) {//保证鼠标左键按下
        double tempX = viewPort1.x() + (event->pos().x() - pressPosition.x()) / graphW;
        double tempY = viewPort1.y() + (event->pos().y() - pressPosition.y()) / graphH;
        // 更新坐标原点的位置
        viewPort1.setX(tempX);
        viewPort1.setY(tempY);
        pressPosition = event->pos();
        this->repaint();
    }
}
void graph::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        ifDrag = false;
    }
}

void graph::wheelEvent(QWheelEvent* event) {
    //更新图像窗口显示图像的缩放系数
    scale += event->angleDelta().y() / 120;
    //防止underflow，限制图像最小缩放倍率
    if (scale <= 0.3) {
        scale -= event->angleDelta().y() / 120;
    }
    // 更新草的头像的显示大小
    widgets->grassWidget->setImageSize(widgets->grassWidget->getImageSize().scaled(scale, scale, Qt::KeepAspectRatioByExpanding));
    //及时刷新图像
    this->update();
}