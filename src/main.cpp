/**
 * @file main.cpp
 * @brief Simple main function for GUI game version.
 *
 * @author Frantisek Sumsal <xsumsa01@stud.fit.vutbr.cz>
 * @date 28.04.2016
 */
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
