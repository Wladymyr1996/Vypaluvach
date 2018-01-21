#include <QCoreApplication>
#include "mc.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MainClass w;

    return a.exec();
}
