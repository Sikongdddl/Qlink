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
#include <QFile>
#include <QFileDialog>

namespace Ui {
class gameWidget1;
}

class gameWidget1 : public QWidget
{
    Q_OBJECT

public:
    explicit gameWidget1(QWidget *parent = 0);
    ~gameWidget1();

    bool doubleFlag;
    QString save;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap image4;
    QPixmap image5;
    QPixmap image6;
    QPixmap image7;
    QPixmap image8;

    QPushButton* b1,*b11;
    QPushButton* b2,*b22;
    QPushButton* b3,*b33;
    QPushButton* b4,*b44;
    QPushButton* b5,*b55;
    QPushButton* b6;
    QPushButton* b7;
    QPushButton* b8;

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
    Block** dd;
    worker gjr;
    worker px;
    item older;
    //void roadFunc(int xStart,int yStart,int xTerm,int yTerm,bool &flag, int num);

private:



protected:
    void paintEvent(QPaintEvent*);

};

#endif // WIDGET_H
