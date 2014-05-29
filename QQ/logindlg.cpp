#include "logindlg.h"
#include "ui_logindlg.h"
#include "webqqnet.h"
#include <QDebug>
#include "webqq.h"
/**
 * @brief LoginDlg::LoginDlg 登录对话框构造函数
 * @param parent 父容器
 */
LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    //UI设置
    ui->setupUi(this);
    //输入QQ帐号后检查验证码
    connect(ui->qqnum,SIGNAL(editingFinished()),this,SLOT(checkVerifycode()));
    connect(ui->rtnButton,SIGNAL(clicked()),this,SLOT(rtnButtonClk()));
    //判断是否需要输入验证码
    connect(WebQQ::webQQNet,SIGNAL(checkVerifycodeFinished(bool,QString)),this,SLOT(checkVerifycodeFinished(bool,QString)));
    //接收到后显示在界面
    connect(WebQQ::webQQNet,SIGNAL(getVerifyImgFinished(QByteArray)),this,SLOT(getVerifyImgFinished(QByteArray)));
    //
    connect(WebQQ::webQQNet,SIGNAL(loginFinished(bool,QString)),this,SLOT(loginFinished(bool,QString)));
    ui->verifyCode->hide();
    ui->verifyImg->hide();
}

LoginDlg::~LoginDlg()
{
    delete ui;
}
/**
 * @brief LoginDlg::checkVerifycode 检查验证码
 */
void LoginDlg::checkVerifycode(){
    qDebug()<<"checkVerifycode"<<endl;
    if(ui->qqnum->text().trimmed().isEmpty()){
        return;
    }
    WebQQ::webQQNet->checkVerifyCode(ui->qqnum->text());
}
/**
 * @brief LoginDlg::checkVerifycodeFinished 是否需要验证的回调
 * @param getCode 是否需要验证
 * @param code 返回代码
 */
void LoginDlg::checkVerifycodeFinished(bool getCode, QString code){
    qDebug()<<getCode<<code<<endl;
    if(getCode){
        ui->verifyCode->setText(code);
        ui->verifyImg->setText("不需要验证码");
        ui->verifyCode->hide();
        ui->verifyImg->hide();
    }else{
        //清理验证码
        ui->verifyCode->clear();
        //获取验证码
        WebQQ::webQQNet->getVerifyImg(ui->qqnum->text().trimmed());
    }
}
/**
 * @brief LoginDlg::getVerifyImgFinished 接收到图片的回调
 * @param imgdata 图片数据
 */
void LoginDlg::getVerifyImgFinished(QByteArray imgdata){
    //qDebug()<<"getVerifyImgFinished"<<endl;
    //qDebug()<<imgdata.length()<<endl;
    //实例化并装载图片
    QPixmap p;
    p.loadFromData(imgdata);
    //设置验证码控件并显示
    ui->verifyImg->setPixmap(p);
    ui->verifyCode->show();
    ui->verifyImg->show();
}
/**
 * @brief LoginDlg::rtnButtonClk 点击登录框确定
 */
void LoginDlg::rtnButtonClk(){
    //QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    WebQQ::webQQNet->login(ui->qqnum->text().trimmed(),ui->qqpass->text().trimmed(),ui->verifyCode->text().trimmed());
}
/**
 * @brief LoginDlg::loginFinished 登陆后的回调
 * @param loginok 是否成功
 * @param message 输出信息
 */
void LoginDlg::loginFinished(bool loginok, QString message){
    qDebug()<<loginok<<message<<endl;
    if(loginok){
        WebQQ::qqnum=ui->qqnum->text().trimmed();
        WebQQ::loginFinished(loginok);
    }else{
        //重新检查验证码
        checkVerifycode();
    }
}

