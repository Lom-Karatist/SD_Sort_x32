#include "widget.h"
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget main_window;
    main_window.show();

    return a.exec();
}
