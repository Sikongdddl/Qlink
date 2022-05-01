#include "worker.h"
#define r 25
worker::worker()
{
    x=r;
    y=r;
    score=0;
}

void worker::move(int x1,int y1)
{
    this->x=x1;
    this->y=y1;
}

int worker::showX()
{
    return this->x;
}

int worker::showY()
{
    return this->y;
}
