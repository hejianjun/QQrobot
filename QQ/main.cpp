/****************************************************************************
**
** Copyright (C) 2013 Jeffrey Lee.
** All rights reserved.
** Contact: vipjeffreylee@gmail.com
** Please keep the author contact information.
** 2013-10-10
**
****************************************************************************/
#include "webqq.h"
#include <QApplication>
/**
 * @brief main 程序入口
 * @param argc 参数数量
 * @param argv 参数列表
 * @return 进入Qt
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //启动登录
    WebQQ::login();
    return a.exec();
}
