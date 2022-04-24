#ifndef CREATUREUI_H
#define CREATUREUI_H
#include <QWidget>
#include <string>
#include <QDebug>

class creatureUI : public QWidget{
    Q_OBJECT
public:
    creatureUI(QWidget* parent) : QWidget(parent){}
    void setNumberOfCreature(int n){
        numberOfCreature = n;
    }
    const int getNumberOfCreature()const{
        return numberOfCreature;
    }

private:
    int numberOfCreature;
    // std::string trim(std::string str){
    //     //删除0到第一个不是空格的字符
    //     str.erase(0, str.find_first_not_of(" "));
    //     //删除最后一个不是空格的字符到字符串结尾
    //     str.erase(str.find_last_not_of(" ")+1, str.length());
    //     return str;
    // }

private slots:
    // void updateNumberOfCreature(const QString &inputString){
    //     std::string tempString = trim(inputString.toStdString());
    //     int sum = 0;
    //     if(tempString.length() == 0)
    //         return;
    //     for(int i = 0; i < tempString.length(); ++i){
    //         int tempNumber = tempString[i] - '0';
    //         if(tempNumber >=0 && tempNumber <=9){
    //             sum = sum * 10 + tempNumber;
    //         }
    //         else
    //             return;
    //     }
    //     setNumberOfCreature(sum);
    //     qDebug() << sum << endl;
    // }

};
#endif