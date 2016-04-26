#include <QApplication>
#include "GUI.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(GUI::tr("ICP - Reversi"));
    GUI g;

    g.show();

    return app.exec();
}
