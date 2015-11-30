#include <QCoreApplication>
#include "presentation.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // ===== BEGIN =====

    loop();

    // ===== END =====
    return a.exec();
}
