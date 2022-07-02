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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()//退出登录
{


       emit showMain();        //发射showMain信号
       this->hide();            //  隐藏
}



void MainWindow::on_pushButton_5_clicked()  //查询员工信息
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);
    db.open();

    QSqlQueryModel *model=new QSqlQueryModel;
    QString sql=QString("CALL exec_1(%1)").arg(ui->textEdit->toPlainText().toInt());

    model->setQuery(sql,db);//设置一个QSqlQuery对象，获取数据
    model->setHeaderData(0,Qt::Horizontal,tr("员工编号"));//设置表头名称
    model->setHeaderData(1,Qt::Horizontal,tr("姓名"));
    model->setHeaderData(2,Qt::Horizontal,tr("性别"));
    model->setHeaderData(3,Qt::Horizontal,tr("出生日期"));
    model->setHeaderData(4,Qt::Horizontal,tr("入职时间"));
    model->setHeaderData(5,Qt::Horizontal,tr("所属部门"));
    model->setHeaderData(6,Qt::Horizontal,tr("职位"));
    model->setHeaderData(7,Qt::Horizontal,tr("职称"));
    model->setHeaderData(8,Qt::Horizontal,tr("政治面貌"));
    model->setHeaderData(9,Qt::Horizontal,tr("婚姻情况"));
    ui->tableView->setModel(model);//设置表格属性

    ui->label_2->setText("员工信息查询结果");
    db.close();
}

void MainWindow::on_pushButton_6_clicked()//修改员工信息
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);
    db.open();

    QString sql_2=QString("select * from employee_information where %1 = \"%2\"").arg(ui->comboBox->currentText()).arg(ui->textEdit->toPlainText());
    QString sql= QString("update employee_information set %1 = \"%2\" where %3 =\"%4\"").arg(ui->comboBox_2->currentText()).arg(ui->textEdit_2->toPlainText())
            .arg(ui->comboBox->currentText()).arg(ui->textEdit->toPlainText());
    QSqlQuery query(db);
    if(!query.exec(sql))
    {
         QMessageBox::warning(NULL,"错误 ","输入信息错误 ");
    }

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

        ui->label_2->setText("员工信息修改结果");
    db.close();
}

void MainWindow::on_pushButton_7_clicked()//删除指定员工信息
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);
    db.open();

    QString sql_2=QString("select * from employee_information where %1 = %2").arg(ui->comboBox->currentText()).arg(ui->textEdit->toPlainText().toInt());
    QString sql=QString("delete from employee_information where %1=\"%2\"").arg(ui->comboBox_3->currentText()).arg(ui->textEdit_3->toPlainText());

    QSqlQuery query(db);
    if(!query.exec(sql))
    {
        QMessageBox::warning(NULL,"错误 ","输入信息错误 ");
    }

    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_2,db);
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
    ui->label_2->setText("员工信息删除结果");
    db.close();
}

void MainWindow::on_pushButton_8_clicked()//查看员工历史信息表
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);
    db.open();

    QSqlQueryModel *model=new QSqlQueryModel;
    QString sql=QString("select * from view_1");
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
    model->setHeaderData(10,Qt::Horizontal,tr("操作类型"));
    model->setHeaderData(11,Qt::Horizontal,tr("操作时间"));

    ui->tableView->setModel(model);
    ui->label_2->setText("员工信息操作历史");
    db.close();
}


void MainWindow::on_pushButton_13_clicked()//查询部门信息
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);
    db.open();


    QSqlQueryModel *model=new QSqlQueryModel;
    QString sql=QString("CALL exec_3(\"%1\")").arg(ui->textEdit_7->toPlainText());
    model->setQuery(sql,db);
    model->setHeaderData(0,Qt::Horizontal,tr("部门名称"));
    model->setHeaderData(1,Qt::Horizontal,tr("部门负责人"));
    model->setHeaderData(2,Qt::Horizontal,tr("部门人数"));

    ui->tableView_3->setModel(model);
    db.close();
    ui->label_5->setText("部门信息查询结果");
}

void MainWindow::on_pushButton_14_clicked()//修改部门信息
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);
    db.open();

    QString sql= QString("update employ_department set %1 = \"%2\" where department_name =\"%3\"").arg(ui->comboBox_5->currentText())
            .arg(ui->textEdit_8->toPlainText()).arg(ui->textEdit_7->toPlainText());
    QSqlQuery query(db);
    query.exec(sql);


    QString sql_3=QString("update employee_information set department =\"%1\" where department=\"%2\"").arg(ui->textEdit_8->toPlainText()).arg(ui->textEdit_7->toPlainText());
    query.exec(sql_3);

    QSqlQueryModel *model=new QSqlQueryModel;
    QString sql_2=QString("CALL exec_3(\"%1\")").arg(ui->textEdit_7->toPlainText());
    model->setQuery(sql_2,db);
    model->setHeaderData(0,Qt::Horizontal,tr("部门名称"));
    model->setHeaderData(1,Qt::Horizontal,tr("部门负责人"));
    model->setHeaderData(2,Qt::Horizontal,tr("部门人数"));
    ui->tableView_3->setModel(model);

    db.close();
    ui->label_5->setText("部门信息修改结果");
}

void MainWindow::on_pushButton_15_clicked()         //删除部门信息
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);
    db.open();

    QString sql=QString("delete from employ_department where department_name=\"%1\"").arg(ui->textEdit_9->toPlainText());
    QSqlQuery query(db);
    query.exec(sql);

    QString sql_3=QString("delete from employee_information where department=\"%1\"").arg(ui->textEdit_9->toPlainText());//删除部门时，同时删除相应的部门员工
    query.exec(sql_3);

    QSqlQueryModel *model=new QSqlQueryModel;
    QString sql_2=QString("CALL exec_3(\"%1\")").arg(ui->textEdit_9->toPlainText());
    model->setQuery(sql_2,db);
    model->setHeaderData(0,Qt::Horizontal,tr("部门名称"));
    model->setHeaderData(1,Qt::Horizontal,tr("部门负责人"));
    model->setHeaderData(2,Qt::Horizontal,tr("部门人数"));
    ui->tableView_3->setModel(model);

    db.close();
}

void MainWindow::on_pushButton_16_clicked()//查询部门的历史信息
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);
    db.open();

    QSqlQueryModel *model=new QSqlQueryModel;
    QString sql=QString("CALL exec_4");
    model->setQuery(sql,db);
    model->setHeaderData(0,Qt::Horizontal,tr("部门名称"));
    model->setHeaderData(1,Qt::Horizontal,tr("部门负责人"));
    model->setHeaderData(2,Qt::Horizontal,tr("部门人数"));
    model->setHeaderData(3,Qt::Horizontal,tr("操作"));
    model->setHeaderData(4,Qt::Horizontal,tr("时间"));

    ui->tableView_3->setModel(model);
    db.close();
    ui->label_5->setText("部门历史信息");
}

void MainWindow::on_pushButton_9_clicked()//查询指定员工的工资信息
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    QString sql;
    if(ui->comboBox_10->currentText()=="id")
    {
    sql=QString("CALL exec_5(\"%1\",\"%2\",%3)").arg(ui->comboBox_8->currentText()).arg(ui->comboBox_9->currentText()).arg(ui->textEdit_4->toPlainText());
    }
    else
    {
        sql=QString("CALL exec_7(\"%1\",\"%2\",\"%3\")").arg(ui->comboBox_8->currentText()).arg(ui->comboBox_9->currentText()).arg(ui->textEdit_4->toPlainText());
    }

    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql,db);
    model->setHeaderData(0,Qt::Horizontal,tr("员工编号"));
    model->setHeaderData(1,Qt::Horizontal,tr("发放日期"));
    model->setHeaderData(2,Qt::Horizontal,tr("基础工资"));
    model->setHeaderData(3,Qt::Horizontal,tr("岗位津贴"));
    model->setHeaderData(4,Qt::Horizontal,tr("奖金"));
    model->setHeaderData(5,Qt::Horizontal,tr("扣除"));
    model->setHeaderData(6,Qt::Horizontal,tr("公积金"));
    model->setHeaderData(7,Qt::Horizontal,tr("养老金"));
    model->setHeaderData(8,Qt::Horizontal,tr("医疗保险"));
    model->setHeaderData(9,Qt::Horizontal,tr("失业保险"));
    model->setHeaderData(10,Qt::Horizontal,tr("生育保险"));
    model->setHeaderData(11,Qt::Horizontal,tr("扣税"));

    ui->tableView_2->setModel(model);
    db.close();

    ui->label_4->setText("员工工资查询结果");
}

void MainWindow::on_pushButton_17_clicked()//修改指定员工的工资信息
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    QString sql;
    QString sql_2;
    QString sql_3;
    QSqlQuery query(db);
    if(ui->comboBox_10->currentText()=="id")//通过id查询到指定员工的工资信息，然后修改
    {
        sql=QString("update salary set %1=\"%2\" where id=\"%3\" and release_date between \"%4\" and \"%5\"").arg(ui->comboBox_7->currentText()).arg(ui->textEdit_10->toPlainText()).arg(ui->textEdit_4->toPlainText()).arg(ui->comboBox_8->currentText()).arg(ui->comboBox_9->currentText());
        sql_2=QString("CALL exec_5(\"%1\",\"%2\",%3)").arg(ui->comboBox_8->currentText()).arg(ui->comboBox_9->currentText()).arg(ui->textEdit_4->toPlainText());
    }
    else //查询到指定部门的工资信息，然后修改
    {
        sql_3=QString("select id from employee_information where department = \"%1\"").arg(ui->textEdit_4->toPlainText());
        sql=QString("update salary set %1=\"%2\" where id in(%3) and release_date between \"%4\" and \"%5\"").arg(ui->comboBox_7->currentText()).arg(ui->textEdit_10->toPlainText()).arg(sql_3).arg(ui->comboBox_8->currentText()).arg(ui->comboBox_9->currentText());
        sql_2=QString("CALL exec_7(\"%1\",\"%2\",\"%3\")").arg(ui->comboBox_8->currentText()).arg(ui->comboBox_9->currentText()).arg(ui->textEdit_4->toPlainText());

    }
    query.exec(sql);


    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_2,db);
    model->setHeaderData(0,Qt::Horizontal,tr("员工编号"));
    model->setHeaderData(1,Qt::Horizontal,tr("发放日期"));
    model->setHeaderData(2,Qt::Horizontal,tr("基础工资"));
    model->setHeaderData(3,Qt::Horizontal,tr("岗位津贴"));
    model->setHeaderData(4,Qt::Horizontal,tr("奖金"));
    model->setHeaderData(5,Qt::Horizontal,tr("扣除"));
    model->setHeaderData(6,Qt::Horizontal,tr("公积金"));
    model->setHeaderData(7,Qt::Horizontal,tr("养老金"));
    model->setHeaderData(8,Qt::Horizontal,tr("医疗保险"));
    model->setHeaderData(9,Qt::Horizontal,tr("失业保险"));
    model->setHeaderData(10,Qt::Horizontal,tr("生育保险"));
    model->setHeaderData(11,Qt::Horizontal,tr("扣税"));
    ui->tableView_2->setModel(model);

    db.close();
    ui->label_4->setText("员工工资修改结果");
}

void MainWindow::on_pushButton_18_clicked()//查询工资历史信息表
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);
    db.open();

    QSqlQueryModel *model=new QSqlQueryModel;
    QString sql=QString("CALL exec_6");
    model->setQuery(sql,db);
    model->setHeaderData(0,Qt::Horizontal,tr("员工编号"));
    model->setHeaderData(1,Qt::Horizontal,tr("发放日期"));
    model->setHeaderData(2,Qt::Horizontal,tr("基础工资"));
    model->setHeaderData(3,Qt::Horizontal,tr("岗位津贴"));
    model->setHeaderData(4,Qt::Horizontal,tr("奖金"));
    model->setHeaderData(5,Qt::Horizontal,tr("扣除"));
    model->setHeaderData(6,Qt::Horizontal,tr("公积金"));
    model->setHeaderData(7,Qt::Horizontal,tr("养老金"));
    model->setHeaderData(8,Qt::Horizontal,tr("医疗保险"));
    model->setHeaderData(9,Qt::Horizontal,tr("失业保险"));
    model->setHeaderData(10,Qt::Horizontal,tr("生育保险"));
    model->setHeaderData(11,Qt::Horizontal,tr("扣税"));
    model->setHeaderData(12,Qt::Horizontal,tr("操作类型"));
    model->setHeaderData(13,Qt::Horizontal,tr("操作时间"));
    ui->tableView_2->setModel(model);
    db.close();

    ui->label_4->setText("员工工资历史信息");
}

void MainWindow::on_radioButton_clicked(bool checked)//跳转到查询员工信息界面
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void MainWindow::on_radioButton_2_clicked(bool checked)//跳转到查询工资信息界面
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void MainWindow::on_radioButton_3_clicked(bool checked)//跳转到查询部门信息界面
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void MainWindow::on_pushButton_2_clicked()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);
    db.open();

    QSqlQueryModel *model=new QSqlQueryModel;
    QString sql=QString("select * from view_2");
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
    ui->label_2->setText("员工全部信息");
    db.close();
}


void MainWindow::on_pushButton_3_clicked()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);
    db.open();

    QSqlQueryModel *model=new QSqlQueryModel;
    QString sql=QString("select * from view_3");
    model->setQuery(sql,db);
    model->setHeaderData(0,Qt::Horizontal,tr("员工编号"));
    model->setHeaderData(1,Qt::Horizontal,tr("发放日期"));
    model->setHeaderData(2,Qt::Horizontal,tr("基础工资"));
    model->setHeaderData(3,Qt::Horizontal,tr("岗位津贴"));
    model->setHeaderData(4,Qt::Horizontal,tr("奖金"));
    model->setHeaderData(5,Qt::Horizontal,tr("扣除"));
    model->setHeaderData(6,Qt::Horizontal,tr("公积金"));
    model->setHeaderData(7,Qt::Horizontal,tr("养老金"));
    model->setHeaderData(8,Qt::Horizontal,tr("医疗保险"));
    model->setHeaderData(9,Qt::Horizontal,tr("失业保险"));
    model->setHeaderData(10,Qt::Horizontal,tr("生育保险"));
    model->setHeaderData(11,Qt::Horizontal,tr("扣税"));
    model->setHeaderData(12,Qt::Horizontal,tr("应发工资"));
    model->setHeaderData(13,Qt::Horizontal,tr("实发工资"));
    ui->tableView_2->setModel(model);
    db.close();

    ui->label_4->setText("员工工资全部信息");
}

void MainWindow::on_pushButton_4_clicked()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("account");                //设定要连接数据库的名字
    db.setPassword("root");
    db.setPort(3306);
    db.open();

    QSqlQueryModel *model=new QSqlQueryModel;
    QString sql=QString("select * from view_4");
    model->setQuery(sql,db);
    model->setHeaderData(0,Qt::Horizontal,tr("部门名称"));
    model->setHeaderData(1,Qt::Horizontal,tr("部门负责人"));
    model->setHeaderData(2,Qt::Horizontal,tr("部门人数"));


    ui->tableView_3->setModel(model);
    ui->label_5->setText("部门信息操作历史");
    db.close();
}
