#include <QCoreApplication>
#include "presentation.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // ===== BEGIN =====

    loop();

    // ===== END =====
    return a.exec();
}
