#include "name_search.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Name_search w;
    w.show();

    return a.exec();
}
