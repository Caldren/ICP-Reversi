/**
 * @file GUIObjects.hpp
 * @see GUI
 * @brief Helper objects for GUI game board.
 *
 * @author Frantisek Sumsal <xsumsa01@stud.fit.vutbr.cz>
 * @date 28.04.2016
 */
#include <QWidget>
#include <QObject>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QGraphicsItem>
#include <iostream>
#include "Color.hpp"

/**
 * @class BoardSquare
 * @brief Simple GUI square entity.
 */
class BoardSquare : public QWidget, public QGraphicsItem {
Q_OBJECT
public:
    /**
     * @brief Create square.
     * @details Create square of given color and width with given coordinates.
     *          Coordinates x,y are used for mapping with Board matrix.
     * @param color Square color.
     * @param w Square width.
     * @param x x axis
     * @param y y axis
     */
    BoardSquare(const QColor &color, int w, int x, int y) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->color = color;
        setAcceptedMouseButtons(Qt::LeftButton);
    }

private:
    /**
     * @brief Get square boundaries.
     */
    QRectF boundingRect() const {
        return QRectF(0, 0, w, w);
    }

    /**
     * @brief Draw square in current scene.
     * @details This function is called automatically on each scene update.
     */
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

signals:
    /**
     * @brief Signal emitted when left-mouse click occurs on the object.
     * @details Signal also carries coordinations of the object.
     */
    void mousePressed(int x, int y);

private:
    QColor color; /**< Square color */
    int w;        /**< Square width */
    int x;        /**< Internal x axis */
    int y;        /**< Internal y axis */

protected:
    /**
     * @brief Convert object's mouse left-click event to mousePressed signal.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) {
        emit mousePressed(x, y);
    }
};

/**
 * @class BoardCircle
 * @brief Simple GUI circle entity.
 */
class BoardCircle : public QGraphicsItem {
public:
    /**
     * @brief Create circle.
     * @details Create circle of given Color and width.
     * @see Color
     * @param colorCode Color code
     * @param width Circle width
     */
    BoardCircle(int colorCode, int width) : w(width) {
        if(colorCode == Color::BLACK) {
            color.setRgb(0, 0, 0);
        } else if(colorCode == Color::WHITE) {
            color.setRgb(255, 255, 255);
        } else {
            color.setRgb(255, 0, 0);
        }
    }

private:
    /**
     * @brief Get circle boundaries.
     */
    QRectF boundingRect() const {
        return QRectF(0, 0, w, w);
    }

    /**
     * @brief Draw square in current scene.
     * @details This function is called automatically on each scene update.
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
            QWidget *widget) {
        QPen p(Qt::black, 2);
        painter->setPen(p);
        painter->setBrush(color);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->drawEllipse(boundingRect());
    }

private:
    QColor color; /**< Circle color */
    int w;        /**< Circle width */
};
