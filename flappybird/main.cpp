#include "view.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    View* v = new View ;

    v->show();

    return a.exec();
}
