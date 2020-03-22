#include "gameplay.h"
#include <QApplication>
#include <QPushButton>
#include <QCoreApplication>
#include <QImage>




int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    gameplay gp;
    gp.show();

    GameBoard *game = new GameBoard; // places a gameBoard struct object on the heap.
    gp.gb = game;

    return app.exec();
}
