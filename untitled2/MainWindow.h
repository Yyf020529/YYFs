#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();//按钮点击发送信号  自己隐藏



signals:
    void showMain();            //自定义信号  是一个信号不需要定义
private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
