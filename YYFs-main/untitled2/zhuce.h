#ifndef ZHUCE_H
#define ZHUCE_H

#include <QWidget>

namespace Ui {
class zhuce;
}

class zhuce : public QWidget
{
    Q_OBJECT

public:
    explicit zhuce(QWidget *parent = nullptr);
    ~zhuce();

private slots:
    void on_pushButton_clicked();

    void on_back_clicked();

signals:
    void showMain_1();

private:
    Ui::zhuce *ui;
};

#endif // ZHUCE_H
