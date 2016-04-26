#ifndef __GUI_HPP_INCLUDED
#define __GUI_HPP_INCLUDED

#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QRadioButton>
#include <QLineEdit>
#include <QComboBox>
#include <vector>
#include "Game.hpp"

class GUI : public QMainWindow {
Q_OBJECT
public:
    GUI();
    ~GUI();
    void createMenus();

private:
    class PlayerObjects {
    public:
        PlayerObjects(QLineEdit *n, QRadioButton *h, QRadioButton *a) :
            name(n), human(h), ai(a) {}
        QLineEdit *name;
        QRadioButton *human;
        QRadioButton *ai;
    };
private slots:
    void sNewGame();
    void sSaveGame();
    void sLoadGame();
    void sQuit();
    void sTurnSkip();
    void sTurnPrev();
    void sTurnNext();
    void sCheckAIButtons(bool checked);

private:
    Game *game = nullptr;
    std::vector<PlayerObjects> pobj;
    QComboBox *algoList;
    QLabel *bg;
    QAction *saveGame;
    QAction *turnSkip;
    QAction *turnPrev;
    QAction *turnNext;
};

#endif
