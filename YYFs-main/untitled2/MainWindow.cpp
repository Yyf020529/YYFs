#include "MainWindow.h"
#include "ui_mainwindow.h"
#include<QSqlDatabase>
#include<QtDebug>
#include<QSqlError>
#include<QSqlQuery>
#include<QMessageBox>
#include<QSqlQueryModel>
#include<QTableView>

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


       emit showMain();        //发射showMain信号
       this->hide();            //  隐藏
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}



void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

void MainWindow::on_pushButton_5_clicked()  //查询员工信息
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","mainwindow_1");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery("select * from user",db);
    model->setHeaderData(0,Qt::Horizontal,tr("id"));
    model->setHeaderData(1,Qt::Horizontal,tr("password"));

    ui->tableView->setModel(model);
    ui->tableView->show();

}
