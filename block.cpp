#include "block.h"

Block::Block()
{
    exist=0;
    selectFlag=0;
    selectFlag1=0;
    outFlag=0;
    itemFlag=0;
    hintFlag=0;
    initRandom();
}

Block::Block(int x1,int y1)
{
    x=x1;
    y=y1;
    exist=1;
}

bool Block::isExist()
{
    return exist==1;
}

void Block::initPosition(int x2,int y2)
{
    x=x2;
    y=y2;
}

void Block::initRandom()
{
    this->type=rand()%3+1;
}
