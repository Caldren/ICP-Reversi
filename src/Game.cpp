#include <iostream>
#include "Game.hpp"

Game::Game(int size)
{
    m_board = new Board(size);
    m_size = size;
    m_p1 = nullptr;
    m_p2 = nullptr;
}

Game::~Game()
{
    delete m_board;
    delete m_p1;
    delete m_p2;
    m_board = nullptr;
    m_p1 = nullptr;
    m_p2 = nullptr;
}

void Game::addPlayer(const std::string &name, int score, int color)
{
    if(m_p1 != nullptr && m_p2 != nullptr)
        throw std::range_error("All player slots are full");

    if(color == -1) {
        if(m_p1 == nullptr)
            color = Color::BLACK;
        else
            color = Color::WHITE;
    }

    Player **p = (m_p1 == nullptr) ? &m_p1 : &m_p2;

    *p = new Player(name, color, Player::HUMAN);
    (*p)->setScore(score);
}

const Player *Game::getP1()
{
    return m_p1;
}

const Player *Game::getP2()
{
    return m_p2;
}
