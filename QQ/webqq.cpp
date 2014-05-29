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
#include "webqqnet.h"
#include "logindlg.h"
#include "mainwindow.h"
namespace WebQQ {
Msg::Msg(QObject *parent) :
    QObject(parent){
}
QQstatus status;
WebQQNet* webQQNet=0;
LoginDlg* loginDlg=0;
MainWindow* mainWindow=0;
QString qqnum;
QHash<QString,QQgroup*> qqGroups;
QHash<QString,QQfriend*> qqFriends;
QList<QQmsg*> qqmsgs;
QStandardItemModel *qqGroupListModel=new QStandardItemModel();
QStandardItemModel *qqFriendListModel=new QStandardItemModel();
bool isclose=false;
QMutex mutex;
/**
 * @brief login QQ登录函数
 */
void login(){
    //实例化webQQ连接类
    webQQNet=new WebQQNet();
    //实例化登录窗口
    loginDlg=new LoginDlg();
    //显示登录窗口
    loginDlg->show();
}
/**
 * @brief loginFinished 登录完成的回调
 * @param ok 是否成功
 */
void loginFinished(bool ok){
    if(ok){
        mainWindow=new MainWindow();
        //打开主窗口
        mainWindow->show();
        //隐藏登录窗口
        loginDlg->hide();
        //删除登录窗口
        loginDlg->close();
        loginDlg->deleteLater();
    }
}
}
