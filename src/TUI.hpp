/**
 * @file TUI.hpp
 * @class TUI
 * @brief Simple text user interface for Game engine.
 *
 * @author Frantisek Sumsal <xsumsa01@stud.fit.vutbr.cz>
 * @date 28.04.2016
 */
#ifndef __TUI_HPP_INCLUDED
#define __TUI_HPP_INCLUDED

#include "Game.hpp"

class TUI {
public:
    ~TUI();
    /**
     * @brief Initialize %TUI.
     * @details %TUI asks user to enter information about a new game and then
     *          constructs and initializes necessary entities.
     */
    void init();

private:
    /**
     * @brief Prompt user for information about saved game file and try to
     *        load it.
     */
    void loadGame();
    /**
     * @brief Prompt user for information about a new player.
     * @param id ID of a new player.
     */
    void playerPrompt(int id);
    /**
     * @brief Draw elements of text user interface.
     */
    void drawUI();
    /**
     * @brief %Game control loop for user input.
     */
    void gameControl();

private:
    Game *m_game = nullptr; /**< Current game */
};

#endif
