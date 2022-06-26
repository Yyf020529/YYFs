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
    QString sql=QString("select * from employee_information where %1 = \"%2\"").arg(ui->comboBox->currentText()).arg(ui->textEdit->toPlainText());
    model->setQuery(sql,db);
    model->setHeaderData(0,Qt::Horizontal,tr("员工编号"));
    model->setHeaderData(1,Qt::Horizontal,tr("姓名"));
    model->setHeaderData(2,Qt::Horizontal,tr("性别"));
    model->setHeaderData(3,Qt::Horizontal,tr("出生日期"));
    model->setHeaderData(4,Qt::Horizontal,tr("入职时间"));
    model->setHeaderData(5,Qt::Horizontal,tr("所属部门"));
    model->setHeaderData(6,Qt::Horizontal,tr("职位"));
    model->setHeaderData(7,Qt::Horizontal,tr("职称"));
    model->setHeaderData(8,Qt::Horizontal,tr("政治面貌"));
    model->setHeaderData(9,Qt::Horizontal,tr("婚姻情况"));

    ui->tableView->setModel(model);


    db.close();

}

void MainWindow::on_pushButton_6_clicked()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","mainwindow_2");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);
    db.open();

    QString sql_2=QString("select * from employee_information where %1 = %2").arg(ui->comboBox->currentText()).arg(ui->textEdit->toPlainText().toInt());
    QString sql= QString("update employee_information set %1 = \"%2\" where %3 =\"%4\"").arg(ui->comboBox_2->currentText()).arg(ui->textEdit_2->toPlainText())
            .arg(ui->comboBox->currentText()).arg(ui->textEdit->toPlainText());
    QSqlQuery query(db);
    query.exec(sql);

    QSqlQueryModel *model_2=new QSqlQueryModel;



    model_2->setQuery(sql_2,db);
    model_2->setHeaderData(0,Qt::Horizontal,tr("员工编号"));
    model_2->setHeaderData(1,Qt::Horizontal,tr("姓名"));
    model_2->setHeaderData(2,Qt::Horizontal,tr("性别"));
    model_2->setHeaderData(3,Qt::Horizontal,tr("出生日期"));
    model_2->setHeaderData(4,Qt::Horizontal,tr("入职时间"));
    model_2->setHeaderData(5,Qt::Horizontal,tr("所属部门"));
    model_2->setHeaderData(6,Qt::Horizontal,tr("职位"));
    model_2->setHeaderData(7,Qt::Horizontal,tr("职称"));
    model_2->setHeaderData(8,Qt::Horizontal,tr("政治面貌"));
    model_2->setHeaderData(9,Qt::Horizontal,tr("婚姻情况"));

    ui->tableView->setModel(model_2);


    db.close();
}
