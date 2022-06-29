#include "widget.h"
#include <QApplication>
#include<qfile.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/style.qss");
     qss.open(QFile::ReadOnly);
     QString style = QLatin1String(qss.readAll());
     a.setStyleSheet(style);



    Widget w;
    w.show();
    return a.exec();

}
