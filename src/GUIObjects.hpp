#include <QWidget>
#include <QObject>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QGraphicsItem>
#include <iostream>
#include "Color.hpp"

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
        QPen p(QColor::fromRgb(0, 0, 0));
        p.setWidth(2);
        painter->setBrush(color);
        painter->setPen(p);
        painter->drawRect(boundingRect());
        painter->setBrush(b);
    }

    void setColor(QColor &color) {
        this->color = color;
        QGraphicsItem::update();
    }

signals:
    void mousePressed(int x, int y);

public:
    QColor color;

private:
    int w;
    int x;
    int y;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) {
        emit mousePressed(x, y);
    }
};

class BoardCircle : public QGraphicsItem {
public:
    BoardCircle(int colorCode, int width) : w(width) {
        if(colorCode == Color::BLACK) {
            color.setRgb(0, 0, 0);
        } else if(colorCode == Color::WHITE) {
            color.setRgb(255, 255, 255);
        } else {
            color.setRgb(255, 0, 0);
        }
    }

    QRectF boundingRect() const {
        return QRectF(0, 0, w, w);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
            QWidget *widget) {
        QPen p(Qt::black, 2);
        painter->setPen(p);
        painter->setBrush(color);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->drawEllipse(boundingRect());
    }

public:
    QColor color;

private:
    int w;
};
