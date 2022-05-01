#ifndef WIDGET_H
#define WIDGET_H
#pragma once

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QMessageBox>
#include <Vector>
#include <Stack>
#include <QTimer>
#include <QLCDNumber>
#include <QString>
#include <QList>
#include <QVector>
#include "block.h"
#include "worker.h"
#include "item.h"


namespace Ui {
class gameWidgetplus;
}

class gameWidgetplus : public QWidget
{
    Q_OBJECT

public:
    explicit gameWidgetplus(QWidget *parent = 0);
    ~gameWidget2();
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap image4;
    QPixmap image5;
    QPixmap image6;
    QPixmap image7;

    QPushButton* b1;
    QPushButton* b2;
    QPushButton* b3;
    QPushButton* b4;
    QPushButton* b5;
    QPushButton* b6;
    QPushButton* b7;

    QVector <int> xroad;
    QVector <int> yroad;
    QPoint Clearable1;
    QPoint Clearable2;
    bool judgeFunc(int x1,int x2,int y1,int y2,bool roadNeed);
    bool dealFunc(int x1,int x2,int y1,int y2,bool roadNeed);
    void itemFunc();
    bool solveable();
    void shuffle();
    void hint();
    //void roadFunc(int xStart,int yStart,int xTerm,int yTerm,bool &flag, int num);

private:
    Block** dd;
    worker gjr;
    item older;


protected:
    void paintEvent(QPaintEvent*);

};

#endif // WIDGET_H
