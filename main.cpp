#include "puzzlewnd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PuzzleWnd w;
    w.show();

    return a.exec();
}
