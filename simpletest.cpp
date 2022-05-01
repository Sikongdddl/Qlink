#include "gamewidget1.h"
#include "simpletest.h"

simpletest::simpletest()
{
    gameWidget1 game;
}

void simpletest::case1_testcase()
{
    gameWidget1 game;
    QVERIFY(game.judgeFunc(1,2,1,1,0)==1);
}
void simpletest::case2_testcase()
{
    gameWidget1 game;
    QVERIFY(game.judgeFunc(1,2,2,1,0)==1);
}
void simpletest::case3_testcase()
{
    gameWidget1 game;
    QVERIFY(game.judgeFunc(1,3,3,2,0)==1);
}
void simpletest::case4_testcase()
{
    gameWidget1 game;
    QVERIFY(game.judgeFunc(2,2,1,3,0)==0);
}
void simpletest::caseEmpty_testcase()
{
    gameWidget1 game;
    QVERIFY(game.judgeFunc(0,0,0,1,0)==0);//空空
    QVERIFY(game.judgeFunc(0,1,0,1,0)==0);//空块
    QVERIFY(game.judgeFunc(1,3,1,1,0)==0);//两种不同类型的方块
    QVERIFY(game.judgeFunc(10000,20000,30000,40000,0)==0);//越界
}


//QTEST_MAIN(simpletest)
