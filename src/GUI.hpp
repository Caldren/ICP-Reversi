/**
 * @file GUI.hpp
 * @class GUI
 * @brief GUI for Game engine written in Qt.
 *
 * @author Frantisek Sumsal <xsumsa01@stud.fit.vutbr.cz>
 * @date 28.04.2016
 */
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

class GUI : public QMainWindow {
Q_OBJECT
public:
    /**
     * @brief Create GUI object and draw all necessary elements.
     */
    GUI();
    GUI(const GUI &) = delete;
    ~GUI();
    void operator=(const GUI &) = delete;

private:
    /**
     * @brief Create game menus and hook appropriate signals to them.
     */
    void createMenus();
    /**
     * @brief Initialize game scene & view and set create view as the
     *        central widget of current window.
     */
    void initView();
    /**
     * @brief Draw game board using BoardSquare and BoardCircle objects.
     * @details Also, each BoardSquare's mouse event is hooked to
     *          sHandleBoardEvent slot to be able to handle user input.
     * @see BoardSquare
     * @see BoardCircle
     * @see sHandleBoardEvent()
     */
    void drawBoard();
    /**
     * @brief Updates game board according to Board matrix of current Game.
     * @see Board
     * @see Game
     */
    void updateBoard();
    /**
     * @brief Enable previously disabled history-related menu options and
     *        save game options.
     */
    void enableHistory();
    /**
     * @brief Update status bar according to current game state and players'
     *        score.
     * @see Player
     */
    void updateStatusBar();

    /**
     * @class PlayerObjects
     * @brief Helper class to save objects related to a new game dialog, so we
     *        can easily access them later during new game creation.
     */
    class PlayerObjects {
    public:
        /**
         * @brief Create a new PlayerObjects object.
         * @param n Pointer to QLineEdit a object with player's name
         * @param h Pointer to QRadioButton a object indicating that current
         *          player is a human
         * @param a Pointer to QRadioButton a object indicating that current
         *          player is an AI
         */
        PlayerObjects(QLineEdit *n, QRadioButton *h, QRadioButton *a) :
            name(n), human(h), ai(a) {}
        /**
         * @brief Pointer to QLineEdit object with player's name.
         */
        QLineEdit *name;
        /**
         * @brief Pointer to a QRadioButton indicating that current player
         *        is a human.
         */
        QRadioButton *human;
        /**
         * @brief Pointer to a QRadioButton indicating that current player
         *        is an AI.
         */
        QRadioButton *ai;
    };

private slots:
    /**
     * @brief Handler for left-mouse clickis on BoardSquare objects in current
     *        scene.
     */
    void sHandleBoardEvent(int x, int y);
    /**
     * @brief Handler for New game option in game menu.
     */
    void sNewGame();
    /**
     * @brief Handler for Save game option in game menu.
     */
    void sSaveGame();
    /**
     * @brief Handler for Load game option in game menu.
     */
    void sLoadGame();
    /**
     * @brief Handler for Quit game option in game menu.
     */
    void sQuit();
    /**
     * @brief Handler for Skip turn option in game menu.
     */
    void sTurnSkip();
    /**
     * @brief Handler for Previous turn option in game menu.
     */
    void sTurnPrev();
    /**
     * @brief Handler for Next turn option in game menu.
     */
    void sTurnNext();
    /**
     * @brief Handler for QRadioButton objects in New game dialog to make sure
     *        that only one AI can be selected at the same time. Also, if
     *        an AI player is selected, this handler enables Algorithm
     *        QComboBox item to allow player to choose AI's algorithm.
     */
    void sCheckAIButtons(bool checked);

private:
    const int sqSize = 60;            /**< BoardSquare object size */
    Game *game = nullptr;             /**< Current Game */
    QGraphicsScene *qscene;           /**< Current scene */
    QGraphicsView *qview;             /**< Current view */
    std::vector<PlayerObjects> pobj;  /**< Objects from New game dialog */
    std::vector<BoardSquare*> bitems; /**< Currently drawn BoardSquares */
    QComboBox *algoList;              /**< Algorithm list in New game dialog */
    QAction *saveGame;                /**< Save game menu item */
    QAction *turnSkip;                /**< Skip turn menu item */
    QAction *turnPrev;                /**< Previous turn menu item */
    QAction *turnNext;                /**< Next turn menu item */
    QLabel *statusLeft;               /**< Left part of the status bar */
    QLabel *statusMiddle;             /**< Middle part of the status bar */
    QLabel *statusRight;              /**< Right part of the status bar */
};

#endif
