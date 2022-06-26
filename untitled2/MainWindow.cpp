﻿#include "MainWindow.h"
#include "ui_mainwindow.h"
#include<QSqlDatabase>
#include<QtDebug>
#include<QSqlError>
#include<QSqlQuery>
#include<QMessageBox>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","mainwindow");
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
        qDebug()<<"主界面连接数据库成功";
    }

    QSqlQuery query("select username from user",db);
    while(query.next())
    {

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

       //返回主界面
       emit showMain();        //发射showMain信号
       this->hide();            //  隐藏
}
