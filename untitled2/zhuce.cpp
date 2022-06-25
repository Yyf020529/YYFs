#include "zhuce.h"
#include "ui_zhuce.h"
#include<QtDebug>
#include<QSqlError>
#include<QSqlQuery>
#include<QMessageBox>
#pragma execution_character_set("utf-8")
zhuce::zhuce(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::zhuce)
{
    ui->setupUi(this);

    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");    //创建数据库实例，添加mysql驱动
    QStringList list=QSqlDatabase::drivers();          //查询qt的数据库驱动
    qDebug()<<list;
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);

    QSqlQuery query;
    QString name=ui->lineEdit->text();
    QString password_1=ui->lineEdit_2->text();
    QString password_2=ui->lineEdit_3->text();
}

zhuce::~zhuce()
{
    delete ui;
}

void zhuce::on_pushButton_clicked()
{
    emit showMain_1();
    this->hide();
}

void zhuce::on_back_clicked()
{

    QSqlQuery query;
    QString name=ui->lineEdit->text();
    QString password_1=ui->lineEdit_2->text();
    QString password_2=ui->lineEdit_3->text();

    if(password_1 == password_2)
    {
        query.prepare("insert into user (username,password)"  "VALUES (:name,:password_1)");
        query.bindValue(":name",name);
        query.bindValue(":password_1",password_1);
        query.exec();
    }
    else
    {
        QMessageBox::warning(NULL,"错误 ","密码不一致 ");
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
    }
}
