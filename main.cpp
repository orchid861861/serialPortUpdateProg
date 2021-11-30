#include "dialog.h"
#include "mynativeeventfilter.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myNativeEventFilter myFilter;
    qApp->installNativeEventFilter(&myFilter);
    Dialog w;
    QObject::connect(&myFilter,&myNativeEventFilter::addPort,&w,&Dialog::addSerialPorts);
    QObject::connect(&myFilter,&myNativeEventFilter::removePort,&w,&Dialog::removeSerialPorts);
    w.show();
    return a.exec();
}
