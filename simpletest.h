#ifndef SIMPLETEST_H
#define SIMPLETEST_H
#include <QtTest/QtTest>

class simpletest:public QObject
{
    Q_OBJECT
public slots:
    void case1_testcase();
    void case2_testcase();
    void case3_testcase();
    void case4_testcase();
    void caseEmpty_testcase();
public:
    simpletest();
};

#endif // SIMPLETEST_H
