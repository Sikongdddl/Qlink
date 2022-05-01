#include "widget.h"
#define r 25
#define m 10
#define n 10
Widget::Widget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("QLink!");
    b1=new QPushButton ("开始单人游戏",this);
    b1->resize(400,50);
    b1->move(50,225);
    b2=new QPushButton("开始双人游戏",this);
    b2->resize(400,50);
    b2->move(50,325);

    b3=new QPushButton("读取游戏",this);
    b3->resize(400,50);
    b3->move(50,425);

    this->resize(500,500);
    connect(b1,&QPushButton::clicked,this,[=]()
    {
        this->hide();
        w1.show();
        w1.doubleFlag=0;
    });
    
    connect(b2,&QPushButton::clicked,this,[=]()
    {
        this->hide();
        w1.show();
        w1.doubleFlag=1;
    });

    connect(b3,&QPushButton::clicked,this,[=]()
    {
       QString fileName=QFileDialog::getOpenFileName(this,"open file","C:\\");
       QFile file(fileName);
       file.open(QFile::ReadWrite);
       QByteArray t=file.readAll();
       QString tmp1=t;
       this->hide();
       w1.save=tmp1;
       w1.doubleFlag=0;
       char* tmp;
       tmp=new char [w1.save.length()];
       QByteArray ttmp=w1.save.toLatin1();
       tmp=ttmp.data();

       w1.gjr.x=(tmp[0]-'0')*(2*r)+r;
       w1.gjr.y=(tmp[1]-'0')*(2*r)+r;

       int peel=2;
       for(int i=1;i<=m;i++)
           for(int j=1;j<=n;j++)
           {
               w1.dd[i][j].exist=tmp[peel]-'0';
               w1.dd[i][j].hintFlag=tmp[peel+1]-'0';
               w1.dd[i][j].itemFlag=tmp[peel+2]-'0';
               w1.dd[i][j].outFlag=tmp[peel+3]-'0';
               w1.dd[i][j].selectFlag=tmp[peel+4]-'0';
               w1.dd[i][j].type=tmp[peel+5]-'0';
               peel+=6;
           }

       w1.show();
       w1.update();
    });
}


