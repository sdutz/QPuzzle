#include "puzzlewnd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv) ;

    QCoreApplication::setOrganizationName( "Sdutz") ;
    QCoreApplication::setOrganizationDomain( "https://github.com/sdutz/") ;
    QCoreApplication::setApplicationName( "QPuzzle") ;

    PuzzleWnd w ;
    w.show();

    return a.exec();
}
