#include "widget.h"
#include "ui_widget.h"
#include<QSqlDatabase>
#include<QtDebug>
#include<QSqlError>
#include<QSqlQuery>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(&son,SIGNAL(showMain()),this,SLOT(show_myself()));
    connect(&mun,SIGNAL(showMain_1()),this,SLOT(show_myself()));

    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");    //创建数据库实例，添加mysql驱动
    QStringList list=QSqlDatabase::drivers();          //查询qt的数据库驱动
    qDebug()<<list;
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
        qDebug()<<"成功！恭喜";
    }

    QSqlQuery query;
    QString sql="select * from user";
    query.exec(sql);
    while(query.next())
    {
        qDebug()<<query.value("username").toString();
        qDebug()<<query.value("password").toString();
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{


    this->hide();
    son.show();
}

void Widget::show_myself()
{
    this->show();
    //son.hide();
}

void Widget::on_pushButton_2_clicked()
{
    this->hide();
    mun.show();
}
