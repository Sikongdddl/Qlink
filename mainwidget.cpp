#include "mainwidget.h"

mainWidget::mainWidget()
{
    this->resize(500,500);
    b1=new QPushButton;
    b1->setParent(this);
    b1->resize(50,50);
    b1->move(225,225);
    connect(b1,&QPushButton::clicked,this,[=]()
    {
       this->hide();
       widget w;
       w.show();
    });
}
