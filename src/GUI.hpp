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
#include "Game.hpp"

class GUI : public QMainWindow {
Q_OBJECT
public:
    GUI();
    ~GUI();

private:
    void initView();
    void createMenus();
    void drawBoard();

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
    QGraphicsScene *qscene;
    QGraphicsView *qview;
    std::vector<PlayerObjects> pobj;
    QComboBox *algoList;
    QAction *saveGame;
    QAction *turnSkip;
    QAction *turnPrev;
    QAction *turnNext;
};

class BoardSquare : public QWidget, public QGraphicsItem {
Q_OBJECT
public:
    BoardSquare(const QColor &color, int w, int x, int y) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->color = color;
        setAcceptedMouseButtons(Qt::LeftButton);
    }

    QRectF boundingRect() const {
        return QRectF(0, 0, w, w);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, 
            QWidget *widget) {
        QBrush b = painter->brush();
        painter->setBrush(color);
        painter->drawRect(0, 0, w, w);
        painter->fillRect(this->boundingRect(), color);
        painter->setBrush(b);
    }

public:
    QColor color;

private:
    int w;
    int x;
    int y;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) {
        QGraphicsItem::mouseMoveEvent(event);
        this->color = QColor::fromRgb(255, 0, 0);
        QGraphicsItem::update();
        std::cout << "EVENT <" << x << ";" << y << ">" << std::endl << std::endl;
    }
};

#endif
