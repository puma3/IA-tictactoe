#include "mainwindow.h"
#include <QApplication>
#include <util.h>

int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/

    Game gm(0);

    Position pos(0,0);
    gm.play(pos);
    pos.x = 2; pos.y = 0;
    gm.play(pos);
    pos.x = 0; pos.y = 1;
    gm.play(pos);
    pos.x = 2; pos.y = 1;
    gm.play(pos);
    pos.x = 0; pos.y = 2;
    gm.play(pos);

    return 0;
}
