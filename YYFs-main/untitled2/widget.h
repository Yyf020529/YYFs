#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"MainWindow.h"
#include"zhuce.h"


//********************登陆界面**************************
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    MainWindow son;
    zhuce mun;

private slots:
    void on_pushButton_clicked();
    void show_myself();
    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
