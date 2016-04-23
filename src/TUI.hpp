#ifndef __TUI_HPP_INCLUDED
#define __TUI_HPP_INCLUDED

#include "Game.hpp"

class TUI {
public:
    ~TUI();
    void init();
    void playerPrompt(int id);
    void drawUI();
    void gameControl();

private:
    Game *m_game = nullptr;
    int m_nplayers;
};

#endif
