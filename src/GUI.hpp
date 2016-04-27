#ifndef __GUI_HPP_INCLUDED
#define __GUI_HPP_INCLUDED

#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QRadioButton>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <vector>
#include "GUIObjects.hpp"
#include "Game.hpp"

class BoardSquare;

class GUI : public QMainWindow {
Q_OBJECT
public:
    GUI();
    ~GUI();

private:
    void initView();
    void createMenus();
    void drawBoard();
    void updateBoard();
    void enableHistory();
    void updateStatusBar();

    class PlayerObjects {
    public:
        PlayerObjects(QLineEdit *n, QRadioButton *h, QRadioButton *a) :
            name(n), human(h), ai(a) {}
        QLineEdit *name;
        QRadioButton *human;
        QRadioButton *ai;
    };

private slots:
    void sHandleBoardEvent(int x, int y);
    void sNewGame();
    void sSaveGame();
    void sLoadGame();
    void sQuit();
    void sTurnSkip();
    void sTurnPrev();
    void sTurnNext();
    void sCheckAIButtons(bool checked);

private:
    const int sqSize = 60;
    Game *game = nullptr;
    QGraphicsScene *qscene;
    QGraphicsView *qview;
    std::vector<PlayerObjects> pobj;
    std::vector<BoardSquare*> bitems;
    QComboBox *algoList;
    QAction *saveGame;
    QAction *turnSkip;
    QAction *turnPrev;
    QAction *turnNext;
    QLabel *statusLeft;
    QLabel *statusMiddle;
    QLabel *statusRight;
};

#endif
