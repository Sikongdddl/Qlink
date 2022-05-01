#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <ctime>
#include <stdio.h>
#include <cstdlib>

#include <QDebug>
class Block
{
private:
    int x;
    int y;
public:
    Block(int x1,int y1);
    Block();
    int exist;
    int type;
    bool selectFlag;
    bool selectFlag1;
    bool outFlag;
    int itemFlag;
    bool hintFlag;
    bool isExist();
    void initPosition(int x2,int y2);
    void initRandom();

};

#endif // BLOCK_H
