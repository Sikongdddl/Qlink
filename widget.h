#ifndef SUBWIDGET_H
#define SUBWIDGET_H
#pragma once

#include <QWidget>
#include <QPushButton>
#include "gamewidget1.h"
#include <QFileDialog>
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
private:
    QPushButton *b1;
    QPushButton *b2;
    QPushButton *b3;
    gameWidget1 w1;
};

#endif // SUBWIDGET_H
