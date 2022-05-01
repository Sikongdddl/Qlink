#include "gamewidget1.h"
#include "ui_widget.h"

#define m 10
#define n 10
#define r 25//箱子以及人的碰撞体积半径

int numOfSelected=0;
int numOfSelected1=0;
int selx1=0;
int selx11=0;
int selx2=0;
int selx21=0;
int sely1=0;
int sely11=0;
int sely2=0;
int sely21=0;
int secCount=0;
int secCount1=0;
int minCount=0;
int minCount1=0;



gameWidget1::gameWidget1(QWidget *parent) :
    QWidget(parent)
{
    this->resize(2*r*(m+2)+200,2*r*(n+2)+200);
    this->setWindowTitle("QLink!");
    srand((int) time(NULL));

    QTimer *timer=new QTimer(this);
    timer->start(1000);

    QTimer *itemTimer=new QTimer(this);
    itemTimer->start(20000);
    connect(itemTimer,&QTimer::timeout,this,[=]()
    {
       int i=rand()%(m+2);
       int j=rand()%(n+2);
       while(dd[i][j].exist==1)
       {
           i=rand()%(m+2);
           j=rand()%(n+2);
       }
       int itemtype=rand()%3+1;
       dd[i][j].itemFlag=itemtype;
       update();
    });

    QLCDNumber* lcd=new QLCDNumber;
    lcd->setParent(this);
    lcd->move(2*r*(m+2),0);
    lcd->setDigitCount(5);
    lcd->setMode(QLCDNumber::Dec);
    lcd->setSegmentStyle(QLCDNumber::Filled);
    lcd->resize(200,50);

    QLCDNumber* lcd2=new QLCDNumber;
    lcd2->setParent(this);
    lcd2->move(2*r*(m+2),2*r*(n+2));
    lcd2->setDigitCount(5);
    lcd2->setMode(QLCDNumber::Dec);
    lcd2->setSegmentStyle(QLCDNumber::Filled);
    lcd2->resize(200,50);

    connect(timer,&QTimer::timeout,this,[=]()
    {
        secCount++;
        secCount1++;
        if(secCount==60)
        {
            secCount=0;
            minCount++;
        }
        if(secCount1==60)
        {
            secCount1=0;
            minCount1++;
        }
        if(minCount==5)
        {
            timer->stop();
            QMessageBox::information(this,tr("温馨提示"),tr("游戏结束"),QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);
            this->close();
        }
        if(minCount1==5&&doubleFlag==1)
        {
            timer->stop();
            QMessageBox::information(this,tr("温馨提示"),tr("游戏结束"),QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);
            this->close();
        }

        QString min=QString::number(4-minCount);
        QString sec=QString::number(60-secCount);
        if(min.length()==1) min="0"+min;
        if(sec.length()==1) sec="0"+sec;
        QString timeShow=min+":"+sec;
        lcd->display(timeShow);

        if(doubleFlag==1)
        {
            QString min1=QString::number(4-minCount1);
            QString sec1=QString::number(60-secCount1);
            if(min1.length()==1) min1="0"+min1;
            if(sec1.length()==1) sec1="0"+sec1;
            QString timeShow=min1+":"+sec1;
            lcd2->display(timeShow);
        }

    });

    dd=new Block* [m+2];
    for(int i=0;i<m+2;i++)
        dd[i]=new Block [n+2];

    for(int i=1;i<m+1;i++)
        for(int j=1;j<n+1;j++)
        {
            dd[i][j].initPosition(i,j);
            dd[i][j].exist=1;
        }

    image1.load(":/picturesrc/pic1.jpg");
    image2.load(":/picturesrc/pic2.png");
    image3.load(":/picturesrc/pic3.png");
    image4.load(":/picturesrc/pic+1s.png");
    image5.load(":/picturesrc/hint.png");
    image6.load(":/picturesrc/shuffle.png");
    image7.load(":/picturesrc/lanran.jfif");
    image8.load(":/picturesrc/wuyue.jpg");

    b1=new QPushButton;
    b2=new QPushButton;
    b3=new QPushButton;
    b4=new QPushButton;
    b5=new QPushButton;
    b11=new QPushButton;
    b22=new QPushButton;
    b33=new QPushButton;
    b44=new QPushButton;
    b55=new QPushButton;
    b6=new QPushButton;
    b7=new QPushButton;
    b8=new QPushButton;

    b1->move(-50,-50);
    b2->move(-50,-50);
    b3->move(-50,-50);
    b4->move(-50,-50);
    b5->move(-50,-50);
    b11->move(-50,-50);
    b22->move(-50,-50);
    b33->move(-50,-50);
    b44->move(-50,-50);
    b55->move(-50,-50);
    b6->move(2*r*(m+2),10*r);
    b7->move(2*r*(m+2),12*r);
    b8->move(2*r*(m+2),14*r);
    b6->resize(2*r,2*r);
    b7->resize(2*r,2*r);
    b8->resize(2*r,2*r);

    b1->setParent(this);
    b2->setParent(this);
    b3->setParent(this);
    b4->setParent(this);
    b5->setParent(this);
    b11->setParent(this);
    b22->setParent(this);
    b33->setParent(this);
    b44->setParent(this);
    b55->setParent(this);
    b6->setParent(this);
    b7->setParent(this);
    b8->setParent(this);

    b1->setShortcut(tr("W"));
    b2->setShortcut(tr("S"));
    b3->setShortcut(tr("A"));
    b4->setShortcut(tr("D"));
    b5->setShortcut(tr("Q"));

    b11->setShortcut(tr("I"));
    b22->setShortcut(tr("K"));
    b33->setShortcut(tr("J"));
    b44->setShortcut(tr("L"));
    b55->setShortcut(tr("U"));

    b6->setShortcut(tr("P"));
    b7->setShortcut(tr("C"));

    connect(b5,&QPushButton::clicked,this,[=]()
    {
        int i=rand()%(m+2);
        int j=rand()%(n+2);
        while(dd[i][j].exist==1)
        {
            i=rand()%(m+2);
            j=rand()%(n+2);
        }
        gjr.move(i*2*r+r,j*2*r+r);
        update();
    });

    connect(b8,&QPushButton::clicked,this,[=]()
    {
       QString fileName=QFileDialog::getOpenFileName(this,"open file","c:\\");
       QFile file(fileName);
       file.open(QFile::ReadWrite);
       QString playerSituation;
       QString mapSituation;
       //QString timeSituation;
       playerSituation+=QString::number((gjr.x-r)/(2*r));
       playerSituation+=QString::number((gjr.y-r)/(2*r));
       //timeSituation+=QString::number(secCount);
       //timeSituation+=QString::number(minCount);
       for(int i=1;i<=m;i++)
           for(int j=1;j<=n;j++)
           {
               mapSituation+=QString::number(dd[i][j].exist);
               mapSituation+=QString::number(dd[i][j].hintFlag);
               mapSituation+=QString::number(dd[i][j].itemFlag);
               mapSituation+=QString::number(dd[i][j].outFlag);
               mapSituation+=QString::number(dd[i][j].selectFlag);
               mapSituation+=QString::number(dd[i][j].type);
           }
       QString total=playerSituation+mapSituation;
       file.write(total.toUtf8());

    });
    connect(b55,&QPushButton::clicked,this,[=]()
    {
        int i=rand()%(m+2);
        int j=rand()%(n+2);
        while(dd[i][j].exist==1)
        {
            i=rand()%(m+2);
            j=rand()%(n+2);
        }
        px.move(i*2*r+r,j*2*r+r);
        update();
    });

    b6->setText("暂停");
    b7->setText("恢复");
    b8->setText("保存");

    connect(b6,&QPushButton::clicked,this,[=]()
    {
       timer->stop();
       b1->setDisabled(true);
       b2->setDisabled(true);
       b3->setDisabled(true);
       b4->setDisabled(true);
       b5->setDisabled(true);
    });
    connect(b7,&QPushButton::clicked,this,[=]()
    {
       timer->start(1000);
       b1->setEnabled(true);
       b2->setEnabled(true);
       b3->setEnabled(true);
       b4->setEnabled(true);
       b5->setEnabled(true);
    });

    connect(b1,&QPushButton::clicked,this,[=]()
    {
        int xNow=gjr.showX();
        int yNow=gjr.showY();
        if(yNow==r) return;

        if(dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].itemFlag==1&&dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].exist==0)
        {
            secCount-=30;
            dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].itemFlag=0;
            if(secCount<0)
            {
                secCount+=60;
                minCount-=1;
            }
            update();
        }
        if(dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].itemFlag==2&&dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].exist==0)
        {
            hint();
            dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].itemFlag=0;
            update();
        }
        if(dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].itemFlag==3&&dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].exist==0)
        {
            shuffle();
            dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].itemFlag=0;
            update();
        }

        if((yNow!=r)&&dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].exist!=1)
        {
            yNow-=2*r;
            gjr.move(xNow,yNow);
            update();
        }
        else if(dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].exist==1)
        {
            if(dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].selectFlag!=1)
            {
                dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].selectFlag=1;
                numOfSelected++;
                if(numOfSelected==1)
                {
                    selx1=(xNow-r);
                    sely1=(yNow-3*r);
                }
                if(numOfSelected==2)
                {
                    selx2=(xNow-r);
                    sely2=(yNow-3*r);
                    bool f=dealFunc(selx1/(2*r),selx2/(2*r),sely1/(2*r),sely2/(2*r),1);
                    if(f==1)
                    {
                        f=solveable();
                        if(f==0)
                        {
                            timer->stop();
                            QMessageBox::information(this,tr("温馨提示"),tr("游戏结束"),QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);
                            this->close();
                        }
                    }
                }
                //qDebug()<<"selected!";
                update();
            }
            else if(dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].selectFlag==1)
            {
                numOfSelected--;
                dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].selectFlag=0;
                update();
            }
        }
    });
    connect(b11,&QPushButton::clicked,this,[=]()
    {
        int xNow=px.showX();
        int yNow=px.showY();
        if(yNow==r) return;

        if(dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].itemFlag==1&&dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].exist==0)
        {
            secCount1-=30;
            dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].itemFlag=0;
            if(secCount1<0)
            {
                secCount1+=60;
                minCount1-=1;
            }
            update();
        }
        if(dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].itemFlag==2&&dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].exist==0)
        {
            hint();
            dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].itemFlag=0;
            update();
        }
        if(dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].itemFlag==3&&dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].exist==0)
        {
            shuffle();
            dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].itemFlag=0;
            update();
        }

        if((yNow!=r)&&dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].exist!=1)
        {
            yNow-=2*r;
            px.move(xNow,yNow);
            update();
        }
        else if(dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].exist==1)
        {
            if(dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].selectFlag1!=1)
            {
                dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].selectFlag1=1;
                numOfSelected1++;
                if(numOfSelected1==1)
                {
                    selx11=(xNow-r);
                    sely11=(yNow-3*r);
                }
                if(numOfSelected1==2)
                {
                    selx21=(xNow-r);
                    sely21=(yNow-3*r);
                    bool f=dealFunc(selx11/(2*r),selx21/(2*r),sely11/(2*r),sely21/(2*r),1);
                    if(f==1)
                    {
                        f=solveable();
                        if(f==0)
                        {
                            timer->stop();
                            QMessageBox::information(this,tr("温馨提示"),tr("游戏结束"),QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);
                            this->close();
                        }
                    }
                }
                //qDebug()<<"selected!";
                update();
            }
            else if(dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].selectFlag1==1)
            {
                numOfSelected1--;
                dd[(xNow-r)/(2*r)][(yNow-3*r)/(2*r)].selectFlag1=0;
                update();
            }
        }
    });

    connect(b2,&QPushButton::clicked,this,[=]()
    {
        int xNow=gjr.showX();
        int yNow=gjr.showY();
        if(yNow==12*2*r-r) return;
        if(dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].itemFlag==1&&dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].exist==0)
        {
            secCount-=30;
            dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].itemFlag=0;
            if(secCount<0)
            {
                secCount+=60;
                minCount-=1;
            }
            update();
        }
        if(dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].itemFlag==2&&dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].exist==0)
        {
            hint();
            dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].itemFlag=0;
            update();
        }
        if(dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].itemFlag==3&&dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].exist==0)
        {
            shuffle();
            dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].itemFlag=0;
            update();
        }
        if((yNow!=12*2*r-r)&&dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].exist!=1)
        {
            yNow+=2*r;
            gjr.move(xNow,yNow);
            update();
        }
        else if(dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].exist==1)
        {
            if(dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].selectFlag!=1)
            {
                dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].selectFlag=1;
                //qDebug()<<"selected!";
                numOfSelected++;
                if(numOfSelected==1)
                {
                    selx1=(xNow-r);
                    sely1=(yNow+r);
                }
                if(numOfSelected==2)
                {
                    selx2=(xNow-r);
                    sely2=(yNow+r);
                    bool f=dealFunc(selx1/(2*r),selx2/(2*r),sely1/(2*r),sely2/(2*r),1);
                    if(f==1)
                    {
                        f=solveable();
                        if(f==0)
                        {
                            timer->stop();
                            QMessageBox::information(this,tr("温馨提示"),tr("游戏结束"),QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);
                            this->close();
                        }
                    }
                }
                update();
            }
            else
            {
                numOfSelected--;
                dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].selectFlag=0;
                update();
            }
        }
    });

    connect(b22,&QPushButton::clicked,this,[=]()
    {
        int xNow=px.showX();
        int yNow=px.showY();
        if(yNow==12*2*r-r) return;
        if(dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].itemFlag==1&&dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].exist==0)
        {
            secCount1-=30;
            dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].itemFlag=0;
            if(secCount1<0)
            {
                secCount1+=60;
                minCount1-=1;
            }
            update();
        }
        if(dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].itemFlag==2&&dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].exist==0)
        {
            hint();
            dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].itemFlag=0;
            update();
        }
        if(dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].itemFlag==3&&dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].exist==0)
        {
            shuffle();
            dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].itemFlag=0;
            update();
        }
        if((yNow!=12*2*r-r)&&dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].exist!=1)
        {
            yNow+=2*r;
            px.move(xNow,yNow);
            update();
        }
        else if(dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].exist==1)
        {
            if(dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].selectFlag1!=1)
            {
                dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].selectFlag1=1;
                //qDebug()<<"selected!";
                numOfSelected1++;
                if(numOfSelected1==1)
                {
                    selx11=(xNow-r);
                    sely11=(yNow+r);
                }
                if(numOfSelected1==2)
                {
                    selx21=(xNow-r);
                    sely21=(yNow+r);
                    bool f=dealFunc(selx11/(2*r),selx21/(2*r),sely11/(2*r),sely21/(2*r),1);
                    if(f==1)
                    {
                        f=solveable();
                        if(f==0)
                        {
                            timer->stop();
                            QMessageBox::information(this,tr("温馨提示"),tr("游戏结束"),QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);
                            this->close();
                        }
                    }
                }
                update();
            }
            else
            {
                numOfSelected1--;
                dd[(xNow-r)/(2*r)][(yNow+r)/(2*r)].selectFlag1=0;
                update();
            }
        }
    });

    connect(b3,&QPushButton::clicked,this,[=]()
    {
        int xNow=gjr.showX();
        int yNow=gjr.showY();
        if(xNow==r) return;
        if(dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].itemFlag==1&&dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].exist==0)
        {
            secCount-=30;
            dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].itemFlag=0;
            if(secCount<0)
            {
                secCount+=60;
                minCount-=1;
            }
            update();
        }
        if(dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].itemFlag==2&&dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].exist==0)
        {
            hint();
            dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].itemFlag=0;
            update();
        }
        if(dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].itemFlag==3&&dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].exist==0)
        {
            shuffle();
            dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].itemFlag=0;
            update();
        }
        if((xNow!=r)&&dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].exist!=1)
        {
            xNow-=2*r;
            gjr.move(xNow,yNow);
            update();
        }
        else if(dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].exist==1)
        {
            if(dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].selectFlag!=1)
            {
                dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].selectFlag=1;
                //qDebug()<<"selected!";
                numOfSelected++;
                if(numOfSelected==1)
                {
                    selx1=(xNow-3*r);
                    sely1=(yNow-r);
                }
                if(numOfSelected==2)
                {
                    selx2=(xNow-3*r);
                    sely2=(yNow-r);
                    bool f=dealFunc(selx1/(2*r),selx2/(2*r),sely1/(2*r),sely2/(2*r),1);
                    if(f==1)
                    {
                        f=solveable();
                        if(f==0)
                        {
                            timer->stop();
                            QMessageBox::information(this,tr("温馨提示"),tr("游戏结束"),QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);
                            this->close();
                        }
                    }
                }
                update();
            }
            else
            {
                numOfSelected--;
                dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].selectFlag=0;
                update();
            }
        }
    });

    connect(b33,&QPushButton::clicked,this,[=]()
    {
        int xNow=px.showX();
        int yNow=px.showY();
        if(xNow==r) return;
        if(dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].itemFlag==1&&dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].exist==0)
        {
            secCount1-=30;
            dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].itemFlag=0;
            if(secCount1<0)
            {
                secCount1+=60;
                minCount1-=1;
            }
            update();
        }
        if(dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].itemFlag==2&&dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].exist==0)
        {
            hint();
            dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].itemFlag=0;
            update();
        }
        if(dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].itemFlag==3&&dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].exist==0)
        {
            shuffle();
            dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].itemFlag=0;
            update();
        }
        if((xNow!=r)&&dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].exist!=1)
        {
            xNow-=2*r;
            px.move(xNow,yNow);
            update();
        }
        else if(dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].exist==1)
        {
            if(dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].selectFlag1!=1)
            {
                dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].selectFlag1=1;
                //qDebug()<<"selected!";
                numOfSelected1++;
                if(numOfSelected1==1)
                {
                    selx11=(xNow-3*r);
                    sely11=(yNow-r);
                }
                if(numOfSelected1==2)
                {
                    selx21=(xNow-3*r);
                    sely21=(yNow-r);
                    bool f=dealFunc(selx11/(2*r),selx21/(2*r),sely11/(2*r),sely21/(2*r),1);
                    if(f==1)
                    {
                        f=solveable();
                        if(f==0)
                        {
                            timer->stop();
                            QMessageBox::information(this,tr("温馨提示"),tr("游戏结束"),QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);
                            this->close();
                        }
                    }
                }
                update();
            }
            else
            {
                numOfSelected1--;
                dd[(xNow-3*r)/(2*r)][(yNow-r)/(2*r)].selectFlag1=0;
                update();
            }
        }
    });
    connect(b4,&QPushButton::clicked,this,[=]()
    {
        int xNow=gjr.showX();
        int yNow=gjr.showY();
        if(xNow==12*2*r-r) return;
        if(dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].itemFlag==1&&dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].exist==0)
        {
            secCount-=30;
            dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].itemFlag=0;
            if(secCount<0)
            {
                secCount+=60;
                minCount-=1;
            }
            update();
        }
        if(dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].itemFlag==2&&dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].exist==0)
        {
            hint();
            dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].itemFlag=0;
            update();
        }
        if(dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].itemFlag==3&&dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].exist==0)
        {
            shuffle();
            dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].itemFlag=0;
            update();
        }
        if((xNow!=12*2*r-r)&&dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].exist!=1)
        {
            xNow+=2*r;
            gjr.move(xNow,yNow);
            update();
        }
        else if(dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].exist==1)
        {
            if(dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].selectFlag!=1)
            {
                dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].selectFlag=1;
                //qDebug() <<"selected!";
                numOfSelected++;
                if(numOfSelected==1)
                {
                    selx1=(xNow+r);
                    sely1=(yNow-r);
                }
                if(numOfSelected==2)
                {
                    selx2=(xNow+r);
                    sely2=(yNow-r);
                    bool f=dealFunc(selx1/(2*r),selx2/(2*r),sely1/(2*r),sely2/(2*r),1);
                    if(f==1)
                    {
                        f=solveable();
                        if(f==0)
                        {
                            timer->stop();
                            QMessageBox::information(this,tr("温馨提示"),tr("游戏结束"),QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);
                            this->close();
                        }
                    }
                }
                update();
            }
            else
            {
                numOfSelected--;
                dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].selectFlag=0;
                update();
            }
        }
    });
    connect(b44,&QPushButton::clicked,this,[=]()
    {
        int xNow=px.showX();
        int yNow=px.showY();
        if(xNow==12*2*r-r) return;
        if(dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].itemFlag==1&&dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].exist==0)
        {
            secCount1-=30;
            dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].itemFlag=0;
            if(secCount1<0)
            {
                secCount1+=60;
                minCount1-=1;
            }
            update();
        }
        if(dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].itemFlag==2&&dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].exist==0)
        {
            hint();
            dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].itemFlag=0;
            update();
        }
        if(dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].itemFlag==3&&dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].exist==0)
        {
            shuffle();
            dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].itemFlag=0;
            update();
        }
        if((xNow!=12*2*r-r)&&dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].exist!=1)
        {
            xNow+=2*r;
            px.move(xNow,yNow);
            update();
        }
        else if(dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].exist==1)
        {
            if(dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].selectFlag1!=1)
            {
                dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].selectFlag1=1;
                //qDebug() <<"selected!";
                numOfSelected1++;
                if(numOfSelected1==1)
                {
                    selx11=(xNow+r);
                    sely11=(yNow-r);
                }
                if(numOfSelected1==2)
                {
                    selx21=(xNow+r);
                    sely21=(yNow-r);
                    bool f=dealFunc(selx11/(2*r),selx21/(2*r),sely11/(2*r),sely21/(2*r),1);
                    if(f==1)
                    {
                        f=solveable();
                        if(f==0)
                        {
                            timer->stop();
                            QMessageBox::information(this,tr("温馨提示"),tr("游戏结束"),QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);
                            this->close();
                        }
                    }
                }
                update();
            }
            else
            {
                numOfSelected1--;
                dd[(xNow+r)/(2*r)][(yNow-r)/(2*r)].selectFlag1=0;
                update();
            }
        }
    });
}


gameWidget1::~gameWidget1()
{
}

bool gameWidget1::judgeFunc(int x1,int x2,int y1,int y2,bool roadNeed)
{
    numOfSelected=0;
    numOfSelected1=0;
    bool findFlag=0;
    if(dd[x1][y1].type!=dd[x2][y2].type)
    {
        dd[x1][y1].selectFlag=0;
        dd[x2][y2].selectFlag=0;
        dd[x1][y1].selectFlag1=0;
        dd[x2][y2].selectFlag1=0;
        return 0;
    }
    else
    {
        //roadFunc(x1,y1,x2,y2,findFlag,numOfTurn);
        //函数roadFunc是一具尸体,但花了几个小时功夫，不舍得删了

        //思路：分为三种连线情况去判断。
        bool line1Flag=1;
        bool line2Flag=1;
        bool line3Flag=1;

        int xLarger=(x1>=x2)?x1:x2;
        int xSmaller=(x1<=x2)?x1:x2;
        int yLarger=(y1>=y2)?y1:y2;
        int ySmaller=(y1<=y2)?y1:y2;

        //一条线：
        if(xLarger==xSmaller)
        {
            for(int i=ySmaller+1;i<yLarger;i++)
                if(dd[xLarger][i].exist==1) line1Flag=0;
            if(line1Flag==1)
            {
                if(roadNeed) for(int i=ySmaller;i<=yLarger;i++)
                {
                        yroad.push_back(i);
                        xroad.push_back(xSmaller);
                }
                findFlag=1;
            }
        }
        if(yLarger==ySmaller)
        {
            for(int i=xSmaller+1;i<xLarger;i++)
                if(dd[i][yLarger].exist==1) line1Flag=0;
            if(line1Flag==1)
            {
                if(roadNeed) for(int i=xSmaller;i<=xLarger;i++)
                {
                    xroad.push_back(i);
                    yroad.push_back(ySmaller);
                }
                findFlag=1;
            }
        }

        //两条线,三条线：
        if(findFlag==0)
        {
            //两条线有四种情况：
            //右下角：
            for(int i=xSmaller+1;i<=xLarger;i++)
                if(dd[i][yLarger].exist==1) line2Flag=0;
            for(int j=ySmaller+1;j<yLarger;j++)
                if(dd[xLarger][j].exist==1) line2Flag=0;

            if(line2Flag==1)
            {
                if(roadNeed) for(int i=xSmaller;i<=xLarger;i++)
                {
                    xroad.push_back(i);
                    yroad.push_back(yLarger);
                }
                if(roadNeed) for(int j=ySmaller;j<=yLarger;j++)
                {
                    xroad.push_back(xLarger);
                    yroad.push_back(j);
                }
                findFlag=1;
            }
            else//左上角
            {
                line2Flag=1;
                for(int j=ySmaller;j<yLarger;j++)
                    if(dd[xSmaller][j].exist==1) line2Flag=0;
                for(int i=xSmaller+1;i<xLarger;i++)
                    if(dd[i][ySmaller].exist==1) line2Flag=0;
            }

            if(line2Flag==1)
            {
                findFlag=1;
                if(xroad.empty())
                {
                    if(roadNeed) for(int i=xSmaller;i<=xLarger;i++)
                    {
                        xroad.push_back(i);
                        yroad.push_back(ySmaller);
                    }
                    if(roadNeed) for(int j=ySmaller;j<=yLarger;j++)
                    {
                        xroad.push_back(xSmaller);
                        yroad.push_back(j);
                    }
                }
            }

            else//左下角
            {
                line2Flag=1;
                for(int j=ySmaller+1;j<=yLarger;j++)
                    if(dd[xSmaller][j].exist==1) line2Flag=0;
                for(int i=xSmaller+1;i<xLarger;i++)
                    if(dd[i][yLarger].exist==1) line2Flag=0;
            }
            if(line2Flag==1)
            {
                findFlag=1;
                if(xroad.empty())
                {
                    if(roadNeed) for(int j=ySmaller;j<=yLarger;j++)
                    {
                        xroad.push_back(xSmaller);
                        yroad.push_back(j);
                    }
                    if(roadNeed) for(int i=xSmaller;i<=xLarger;i++)
                    {
                        xroad.push_back(i);
                        yroad.push_back(yLarger);
                    }
                }
            }

            else//右上角
            {
                line2Flag=1;
                for(int i=xSmaller+1;i<=xLarger;i++)
                    if(dd[i][ySmaller].exist==1) line2Flag=0;
                for(int j=ySmaller+1;j<yLarger;j++)
                    if(dd[xLarger][j].exist==1) line2Flag=0;
            }

            if(line2Flag==1)
            {
                findFlag=1;
                if(xroad.empty())
                {
                    if(roadNeed) for(int i=xSmaller;i<=xLarger;i++)
                    {
                        xroad.push_back(i);
                        yroad.push_back(ySmaller);
                    }
                    if(roadNeed) for(int j=ySmaller;j<=yLarger;j++)
                    {
                        xroad.push_back(xLarger);
                        yroad.push_back(j);
                    }
                }
            }

            else if(findFlag==0)//把剪枝权重拉满，最后判断三条线：
            {
                //三条线一共分为六种情况，是最复杂的。
                //这里的o(n2)算法是我的好兄弟启发我的，感谢我的好兄弟zyy同学
                //亲测这个算法够快，尤其是检查地图上是否还有解的时候足够快，可以满足游戏的交互性需求了。

                for(int i=0;i<m+2;i++)//竖向遍历，寻找可以横着链接的路径
                {
                    if(findFlag==0)
                    {
                        line3Flag=1;
                        for(int j=xSmaller;j<=xLarger;j++)
                            if(dd[j][i].exist==1) line3Flag=0;
                        if(line3Flag==1) //这里有一条横着的路径i 接下来判断两个点能否到达这条路径
                        {
                            //qDebug()<<"有一条横着的路径";
                            //qDebug()<<i;

                            if(i<ySmaller&&line3Flag==1)//路径在上面
                            {
                                for(int p=yLarger-1;p>=i;p--)
                                {
                                    if(dd[xSmaller][p].exist==1) {line3Flag=0;}
                                    if(line3Flag==0) break;
                                }
                                for(int p=ySmaller-1;p>=i;p--)
                                {
                                    if(dd[xLarger][p].exist==1) {line3Flag=0;}
                                    if(line3Flag==0) break;
                                }
                                if(line3Flag==1)
                                {
                                    findFlag=1;
                                    if(xroad.empty()&&roadNeed==1)
                                    {
                                        xroad.push_back(xSmaller);
                                        xroad.push_back(xSmaller);
                                        xroad.push_back(xLarger);
                                        xroad.push_back(xLarger);
                                        yroad.push_back(yLarger);
                                        yroad.push_back(i);
                                        yroad.push_back(i);
                                        yroad.push_back(ySmaller);
                                    }
                                }
                                else
                                {
                                    line3Flag=1;
                                    for(int p=yLarger-1;p>=i;p--)
                                    {
                                        if(dd[xLarger][p].exist==1) {line3Flag=0;}
                                        if(line3Flag==0) break;
                                    }
                                    for(int p=ySmaller-1;p>=i;p--)
                                    {
                                        if(dd[xSmaller][p].exist==1) {line3Flag=0;}
                                        if(line3Flag==0) break;
                                    }
                                    if(line3Flag==1)
                                    {
                                        findFlag=1;
                                        if(xroad.empty()&&roadNeed==1)
                                        {
                                            xroad.push_back(xSmaller);
                                            xroad.push_back(xSmaller);
                                            xroad.push_back(xLarger);
                                            xroad.push_back(xLarger);
                                            yroad.push_back(ySmaller);
                                            yroad.push_back(i);
                                            yroad.push_back(i);
                                            yroad.push_back(yLarger);
                                        }
                                    }
                                }
                            }

                            if(i>yLarger&&line3Flag==1)//路径在下面
                            {
                                for(int p=yLarger+1;p<=i;p++)
                                {
                                    if(dd[xSmaller][p].exist==1) {line3Flag=0;}
                                    if(line3Flag==0) break;
                                }
                                for(int p=ySmaller+1;p<=i;p++)
                                {
                                    if(dd[xLarger][p].exist==1) {line3Flag=0;}
                                    if(line3Flag==0) break;
                                }
                                if(line3Flag==1)
                                {
                                    findFlag=1;
                                    if(xroad.empty()&&roadNeed==1)
                                    {
                                        xroad.push_back(xSmaller);
                                        xroad.push_back(xSmaller);
                                        xroad.push_back(xLarger);
                                        xroad.push_back(xLarger);
                                        yroad.push_back(yLarger);
                                        yroad.push_back(i);
                                        yroad.push_back(i);
                                        yroad.push_back(ySmaller);
                                    }
                                }
                                else
                                {
                                    line3Flag=1;
                                    for(int p=yLarger+1;p<=i;p++)
                                    {
                                        if(dd[xLarger][p].exist==1) {line3Flag=0;}
                                        if(line3Flag==0) break;
                                    }
                                    for(int p=ySmaller+1;p<=i;p++)
                                    {
                                        if(dd[xSmaller][p].exist==1) {line3Flag=0;}
                                        if(line3Flag==0) break;
                                    }
                                    if(line3Flag==1)
                                    {
                                        findFlag=1;
                                        if(xroad.empty()&&roadNeed==1)
                                        {
                                            xroad.push_back(xSmaller);
                                            xroad.push_back(xSmaller);
                                            xroad.push_back(xLarger);
                                            xroad.push_back(xLarger);
                                            yroad.push_back(ySmaller);
                                            yroad.push_back(i);
                                            yroad.push_back(i);
                                            yroad.push_back(yLarger);
                                        }
                                    }
                                }
                            }

                            if(i>ySmaller&&i<yLarger&&line3Flag==1)//路径在中间
                            {
                                for(int p=yLarger-1;p>=i;p--)
                                {
                                    if(dd[xSmaller][p].exist==1) {line3Flag=0;}
                                    if(line3Flag==0) break;
                                }
                                for(int p=ySmaller+1;p<=i;p++)
                                {
                                    if(dd[xLarger][p].exist==1) {line3Flag=0;}
                                    if(line3Flag==0) break;
                                }
                                if(line3Flag==1)
                                {
                                    findFlag=1;
                                    if(xroad.empty()&&roadNeed==1)
                                    {
                                        xroad.push_back(xSmaller);
                                        xroad.push_back(xSmaller);
                                        xroad.push_back(xLarger);
                                        xroad.push_back(xLarger);
                                        yroad.push_back(yLarger);
                                        yroad.push_back(i);
                                        yroad.push_back(i);
                                        yroad.push_back(ySmaller);
                                    }
                                }
                                else
                                {
                                    line3Flag=1;
                                    for(int p=yLarger-1;p>=i;p--)
                                    {
                                        if(dd[xLarger][p].exist==1) {line3Flag=0;}
                                        if(line3Flag==0) break;
                                    }
                                    for(int p=ySmaller+1;p<=i;p++)
                                    {
                                        if(dd[xSmaller][p].exist==1) {line3Flag=0;}
                                        if(line3Flag==0) break;
                                    }
                                    if(line3Flag==1)
                                    {
                                        findFlag=1;
                                        if(xroad.empty()&&roadNeed==1)
                                        {
                                            xroad.push_back(xSmaller);
                                            xroad.push_back(xSmaller);
                                            xroad.push_back(xLarger);
                                            xroad.push_back(xLarger);
                                            yroad.push_back(ySmaller);
                                            yroad.push_back(i);
                                            yroad.push_back(i);
                                            yroad.push_back(yLarger);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                for(int j=0;j<n+2;j++)//横向遍历，寻找可以竖着链接的路径
                {
                    if(findFlag==0)
                    {
                        line3Flag=1;
                        for(int i=ySmaller;i<=yLarger;i++)
                            if(dd[j][i].exist==1) line3Flag=0;
                        if(line3Flag==1)//这里有一条竖着的路径，接下来会发生什么应该不用我多说了
                        {
                            //qDebug()<<"有一条竖着的路径";
                            //qDebug()<<j;

                            if(j<xSmaller&&line3Flag==1)//路径在左面
                            {
                                for(int p=xLarger-1;p>=j;p--) if(dd[p][ySmaller].exist==1) {line3Flag=0;}
                                for(int p=xSmaller-1;p>=j;p--) if(dd[p][yLarger].exist==1) {line3Flag=0;}
                                if(line3Flag==1)
                                {
                                    findFlag=1;
                                    if(xroad.empty()&&roadNeed==1)
                                    {
                                        xroad.push_back(xLarger);
                                        xroad.push_back(j);
                                        xroad.push_back(j);
                                        xroad.push_back(xSmaller);
                                        yroad.push_back(ySmaller);
                                        yroad.push_back(ySmaller);
                                        yroad.push_back(yLarger);
                                        yroad.push_back(yLarger);
                                    }
                                }
                                else
                                {
                                    line3Flag=1;
                                    for(int p=xSmaller-1;p>=j;p--) if(dd[p][ySmaller].exist==1) {line3Flag=0;}
                                    for(int p=xLarger-1;p>=j;p--) if(dd[p][yLarger].exist==1) {line3Flag=0;}
                                    if(line3Flag==1)
                                    {
                                        findFlag=1;
                                        if(xroad.empty()&&roadNeed==1)
                                        {
                                            xroad.push_back(xSmaller);
                                            xroad.push_back(j);
                                            xroad.push_back(j);
                                            xroad.push_back(xLarger);
                                            yroad.push_back(ySmaller);
                                            yroad.push_back(ySmaller);
                                            yroad.push_back(yLarger);
                                            yroad.push_back(yLarger);
                                        }
                                    }
                                }
                            }

                            if(j>xLarger&&line3Flag==1)//路径在右面
                            {
                                for(int p=xLarger+1;p<=j;p++) if(dd[p][ySmaller].exist==1) {line3Flag=0;}
                                for(int p=xSmaller+1;p<=j;p++) if(dd[p][yLarger].exist==1) {line3Flag=0;}
                                if(line3Flag==1)
                                {
                                    findFlag=1;
                                    if(xroad.empty()&&roadNeed==1)
                                    {
                                        xroad.push_back(xLarger);
                                        xroad.push_back(j);
                                        xroad.push_back(j);
                                        xroad.push_back(xSmaller);
                                        yroad.push_back(ySmaller);
                                        yroad.push_back(ySmaller);
                                        yroad.push_back(yLarger);
                                        yroad.push_back(yLarger);
                                    }
                                }
                                else
                                {
                                    line3Flag=1;
                                    for(int p=xLarger+1;p<=j;p++) if(dd[p][yLarger].exist==1) {line3Flag=0;}
                                    for(int p=xSmaller+1;p<=j;p++) if(dd[p][ySmaller].exist==1) {line3Flag=0;}
                                    if(line3Flag==1)
                                    {
                                        findFlag=1;
                                        if(xroad.empty()&&roadNeed==1)
                                        {
                                            xroad.push_back(xSmaller);
                                            xroad.push_back(j);
                                            xroad.push_back(j);
                                            xroad.push_back(xLarger);
                                            yroad.push_back(ySmaller);
                                            yroad.push_back(ySmaller);
                                            yroad.push_back(yLarger);
                                            yroad.push_back(yLarger);
                                        }
                                    }
                                }
                            }

                            if(j>xSmaller&&j<xLarger&&line3Flag==1)//路径在中间
                            {
                                for(int p=xLarger-1;p>=j;p--) if(dd[p][ySmaller].exist==1) {line3Flag=0;}
                                for(int p=xSmaller+1;p<=j;p++) if(dd[p][yLarger].exist==1) {line3Flag=0;}
                                if(line3Flag==1)
                                {
                                    findFlag=1;
                                    if(xroad.empty()&&roadNeed==1)
                                    {
                                        xroad.push_back(xLarger);
                                        xroad.push_back(j);
                                        xroad.push_back(j);
                                        xroad.push_back(xSmaller);
                                        yroad.push_back(ySmaller);
                                        yroad.push_back(ySmaller);
                                        yroad.push_back(yLarger);
                                        yroad.push_back(yLarger);
                                    }
                                }
                                else
                                {
                                    line3Flag=1;
                                    for(int p=xLarger-1;p>=j;p--) if(dd[p][yLarger].exist==1) {line3Flag=0;}
                                    for(int p=xSmaller+1;p<=j;p++) if(dd[p][ySmaller].exist==1) {line3Flag=0;}
                                    if(line3Flag==1)
                                    {
                                        findFlag=1;
                                        if(xroad.empty()&&roadNeed==1)
                                        {
                                            xroad.push_back(xSmaller);
                                            xroad.push_back(j);
                                            xroad.push_back(j);
                                            xroad.push_back(xLarger);
                                            yroad.push_back(ySmaller);
                                            yroad.push_back(ySmaller);
                                            yroad.push_back(yLarger);
                                            yroad.push_back(yLarger);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return findFlag;
    }
}

bool gameWidget1::dealFunc(int x1,int x2,int y1,int y2,bool roadNeed)
{
    int flag=judgeFunc(x1,x2,y1,y2,roadNeed);
    if(flag==1)
    {
        dd[x1][y1].exist=0;
        dd[x2][y2].exist=0;
        if(dd[x1][y1].selectFlag==1) gjr.score+=2;
        if(dd[x1][y1].selectFlag1==1) px.score+=2;
        dd[x1][y1].hintFlag=0;
        dd[x2][y2].hintFlag=0;
        dd[x1][y1].selectFlag=0;
        dd[x2][y2].selectFlag=0;
        dd[x1][y1].selectFlag1=0;
        dd[x2][y2].selectFlag1=0;
    }
    if(flag==0)
    {
        dd[x1][y1].selectFlag=0;
        dd[x2][y2].selectFlag=0;
        dd[x1][y1].selectFlag1=0;
        dd[x2][y2].selectFlag1=0;
    }
    return flag;
}

//这是一具尸体，是我曾经写出的递归函数
//然而，在RPG版本的连连看内，判断是否有合理路径这件事是愚蠢的。
//人能走的地方，便是路径。
//人能碰到两个方块，就说明两个方块之间有合理的路径。
/*void Widget::roadFunc(int xStart,int yStart,int xTerm,int yTerm,bool &flag, int num)
{
    //出口

    if(xStart==-1||xStart==m+2||yStart==-1||yStart==n+2) {num--;return;}//越界
    qDebug()<<xStart<<" "<<yStart;

    if(num==4) {num--;qDebug()<<"太能拐了！";return;}//拐弯次数超过两次
    if(flag==1) return;//下班

    if(dd[xStart][yStart].exist==1&&dd[xStart][yStart].selectFlag!=1)
    {
        qDebug()<<"有方块不能走";
        num--;
        return;
    }

    if(dd[xStart][yStart].mark==1) {num--;return;}//不能走回头路

    if(xStart==xTerm&&yStart==yTerm)
    {
        flag=1;
        qDebug()<<"找到了";
        return;
    }

    dd[xStart][yStart].mark=1;

    num++;
    roadFunc(xStart,yStart-1,xTerm,yTerm,flag,num);//上
    num++;
    roadFunc(xStart-1,yStart,xTerm,yTerm,flag,num);//左
    num++;
    roadFunc(xStart,yStart+1,xTerm,yTerm,flag,num);//下
    num++;
    roadFunc(xStart+1,yStart,xTerm,yTerm,flag,num);//右

    dd[xStart][yStart].mark=0;
    return;

}*/

void gameWidget1::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.drawPixmap(gjr.x-r,gjr.y-r,2*r,2*r,image7);
    if(doubleFlag==1) painter.drawPixmap(px.x-r,px.y-r,2*r,2*r,image8);

    if(doubleFlag==0)
    {
        QString getScore="Your scores : "+QString::number(gjr.score);
        painter.drawText(2*r*(m+2),200,getScore);
    }
    if(doubleFlag==1)
    {
        QString getScore1="Player1 scores : "+QString::number(gjr.score);
        painter.drawText(2*r*(m+2),200,getScore1);
        QString getScore2="Player2 scores : "+QString::number(px.score);
        painter.drawText(2*r*(m+2),500,getScore2);
    }

    for(int i=0;i<m+2;i++)
        for(int j=0;j<n+2;j++)//画地图
        {
            if(dd[i][j].isExist()) painter.drawRect(2*r*i,2*r*j,2*r,2*r);

            if(dd[i][j].itemFlag==1) painter.drawPixmap(2*r*i,2*r*j,2*r,2*r,image4);
            if(dd[i][j].itemFlag==2) painter.drawPixmap(2*r*i,2*r*j,2*r,2*r,image5);
            if(dd[i][j].itemFlag==3) painter.drawPixmap(2*r*i,2*r*j,2*r,2*r,image6);

            if(dd[i][j].type==1&&dd[i][j].isExist())
                painter.drawPixmap(2*r*i,2*r*j,2*r,2*r,image1);
            if(dd[i][j].type==2&&dd[i][j].isExist())
                painter.drawPixmap(2*r*i,2*r*j,2*r,2*r,image2);
            if(dd[i][j].type==3&&dd[i][j].isExist())
                painter.drawPixmap(2*r*i,2*r*j,2*r,2*r,image3);

            if(dd[i][j].selectFlag==1||dd[i][j].selectFlag1==1)
                painter.drawRect(2*r*i+r/2,2*r*j+r/2,r,r);

            if(dd[i][j].hintFlag==1)
            {
                QColor color(255,0,0,127);
                painter.fillRect(2*r*i,2*r*j,2*r,2*r,color);
            }
        }

    if(xroad.empty()==0)
    {
        for(int i=0;i<xroad.size()-1;i++)
        {
            painter.drawLine(xroad[i]*2*r+r,yroad[i]*2*r+r,xroad[i+1]*2*r+r,yroad[i+1]*2*r+r);
        }
        xroad.clear();
        yroad.clear();
    }
}

void gameWidget1::hint()
{
    QTimer* timer;
    timer=new QTimer(this);
    timer->start(100);
    connect(timer,QTimer::timeout,this,[=]()
    {
        dd[Clearable1.x()][Clearable1.y()].hintFlag=1;
        dd[Clearable2.x()][Clearable2.y()].hintFlag=1;
        update();
    });

    QTimer* timer2;
    timer2=new QTimer(this);
    timer2->start(10000);
    connect(timer2,&QTimer::timeout,this,[=]()
    {
       timer->stop();
    });


}

void gameWidget1::shuffle()
{
    int numOfBlock=0;
    int* numOfType;
    numOfType=new int [3];

    Clearable1.setX(-1);
    Clearable2.setY(-1);
    Clearable2.setX(-1);
    Clearable2.setY(-1);

    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        {
            if(dd[i][j].exist==1) numOfBlock++;
            if(dd[i][j].exist==1&&dd[i][j].type==1) numOfType[0]++;
            if(dd[i][j].exist==1&&dd[i][j].type==2) numOfType[1]++;
            if(dd[i][j].exist==1&&dd[i][j].type==3) numOfType[2]++;
        }
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        {
            dd[i][j].exist=0;
        }

    int iMax=0;
    if(numOfBlock%m==0) iMax=m;
    else iMax=numOfBlock%m;
    int jMax=0;
    if(numOfBlock%m==0) jMax=numOfBlock/m;
    else jMax=numOfBlock/m+1;


    for(int j=1;j<=jMax;j++)
    {
        if(j==jMax) for(int i=1;i<=iMax;i++)
        {
            int randtmp=rand()%3+1;
            while(numOfType[randtmp-1]==0)
                randtmp=rand()%3+1;
            numOfType[randtmp-1]--;
            dd[i][j].type=randtmp;
            dd[i][j].exist=1;
        }
        else for(int i=1;i<=m;i++)
        {
            int randtmp=rand()%3+1;
            while(numOfType[randtmp-1]==0)
                randtmp=rand()%3+1;
            numOfType[randtmp-1]--;
            dd[i][j].type=randtmp;
            dd[i][j].exist=1;
        }
    }
}

/*void Widget::shuffle()
{
    int numOfBlock=0;
    int numOfType1=0;
    int numOfType2=0;
    int numOfType3=0;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        {
            if(dd[i][j].exist==1) numOfBlock++;
            if(dd[i][j].exist==1&&dd[i][j].type==1) numOfType1++;
            if(dd[i][j].exist==1&&dd[i][j].type==2) numOfType2++;
            if(dd[i][j].exist==1&&dd[i][j].type==3) numOfType3++;
        }
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        {
            dd[i][j].exist=0;
        }

    for(int i=0;i<numOfType1;i++)
    {
        int ip=rand()%numOfBlock+1;
        while(dd[ip/m+1][ip%m].exist==1) {ip=rand()%numOfBlock+1;}
        qDebug()<<ip<<" "<<(ip/m+1)<<" "<<(ip%m);
        if(ip%m!=0)
        {
            dd[ip/m+1][(ip%m)].exist=1;
            dd[ip/m+1][(ip%m)].type=1;
        }
        if(ip%m==0)
        {
            dd[ip/m][m].exist=1;
            dd[ip/m][m].type=1;
        }
    }
    for(int i=0;i<numOfType2;i++)
    {
        int ip=rand()%numOfBlock+1;
        while(dd[ip/m+1][ip%m].exist==1) {ip=rand()%numOfBlock+1;}
        if(ip%m!=0)
        {
            dd[ip/m+1][(ip%m)].exist=1;
            dd[ip/m+1][(ip%m)].type=2;
        }
        if(ip%m==0)
        {
            dd[ip/m][m].exist=1;
            dd[ip/m][m].type=1;
        }
    }
    for(int i=0;i<numOfType3;i++)
    {
        int ip=rand()%numOfBlock+1;
        while(dd[ip/m+1][ip%m].exist==1) {ip=rand()%numOfBlock+1;}
        if(ip%m!=0)
        {
            dd[ip/m+1][(ip%m)].exist=1;
            dd[ip/m+1][(ip%m)].type=3;
        }
        if(ip%m==0)
        {
            dd[ip/m][m].exist=1;
            dd[ip/m][m].type=1;
        }
    }
}*/

bool gameWidget1::solveable()
{
    bool solveFlag=0;
    for(int i=1;i<=m;i++) for(int j=1;j<=n;j++)
        if(dd[i][j].exist==1)
        {
            if(dd[i+1][j].exist==1&&dd[i-1][j].exist==1&&dd[i][j+1].exist==1&&dd[i][j-1].exist==1)
                dd[i][j].outFlag=0;
            else dd[i][j].outFlag=1;
        }

    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            if(dd[i][j].exist==1&&dd[i][j].outFlag==1&&solveFlag==0)
            {
                for(int p=1;p<=m;p++) for(int q=1;q<=n;q++)
                {
                    if(p==i&&q==j) continue;
                    if(dd[p][q].outFlag==1&&dd[p][q].exist==1&&judgeFunc(i,p,j,q,0)==1)
                    {
                        solveFlag=1;
                        Clearable1.setX(i);
                        Clearable1.setY(j);
                        Clearable2.setX(p);
                        Clearable2.setY(q);
                    }
                }
            }
    return solveFlag;
}
