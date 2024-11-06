#include "Fourth_Demo_notepad.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Fourth_Demo_notepad w;
    w.show();
    return a.exec();
}
