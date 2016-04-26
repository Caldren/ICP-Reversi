#ifndef __GUI_HPP_INCLUDED
#define __GUI_HPP_INCLUDED

#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include "Game.hpp"

class GUI : public QMainWindow {
Q_OBJECT
public:
    GUI();
    void createMenus();

private:

private slots:
    void sNewGame();
    void sSaveGame();
    void sLoadGame();
    void sQuit();
    void sTurnSkip();
    void sTurnPrev();
    void sTurnNext();

private:
    QLabel *bg;

    QAction *saveGame;
    QAction *turnSkip;
    QAction *turnPrev;
    QAction *turnNext;
};

#endif
