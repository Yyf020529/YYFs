#include "widget.h"
#include "ui_widget.h"
#include<QSqlDatabase>
#include<QtDebug>
#include<QSqlError>
#include<QSqlQuery>
#include<QMessageBox>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(&son,SIGNAL(showMain()),this,SLOT(show_myself()));
    connect(&mun,SIGNAL(showMain_1()),this,SLOT(show_myself()));

   /*** QSqlDatabase db=QSqlDatabase::database("qt_sql_default_connection");    //已添加过驱动
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);


    if(!db.open())
    {
        qDebug()<<"失败原因"<<db.lastError().text();        //返回错误信息
    }
    else
    {
        qDebug()<<"登录界面连接数据库成功";
    }

    QSqlQuery query;
    QString sql="select * from user";
    query.exec(sql);
    while(query.next())
    {
        qDebug()<<query.value("username").toString();
        qDebug()<<query.value("password").toString();
    } **/
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()        //登录按钮
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    int flag=1;

    if(!db.open())
    {
        qDebug()<<"失败原因"<<db.lastError().text();        //返回错误信息
    }
    else
    {
        qDebug()<<"登录界面连接数据库成功";
    }
    QString name=ui->zhanghao->text();
    QString password=ui->mima->text();

    QSqlQuery query;
    QString sql="select username,password from user";
    query.exec(sql);
    while(query.next())
    {
        if(query.value("username").toString()==name && query.value("password").toString()==password)
        {
            ui->zhanghao->clear();
            ui->mima->clear();
            this->hide();
            son.show();
            flag=0;
            break;
        }
        else
        {
            flag=1;
        }
    }

    if(flag)
    {
        ui->zhanghao->clear();
        ui->mima->clear();
        QMessageBox::warning(NULL,"错误 ","账号或密码错误 ");
    }
    db.close();

}

void Widget::show_myself()
{
    this->show();
    //son.hide();

}

void Widget::on_pushButton_2_clicked()      //去注册按钮
{
    this->hide();
    mun.show();
}

