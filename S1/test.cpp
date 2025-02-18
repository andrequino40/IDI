#include <QApplication>
#include <QPushButton>

int main(int argc, char **argv)
{
    QApplication a(argc,argv);
    QPushButton hello("FIB!",0);
    hello.resize(1000,300);
    hello.show();
    return a.exec();
}