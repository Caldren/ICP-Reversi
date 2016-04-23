#include <iostream>
#include <algorithm>
#include <vector>
#include "Game.hpp"
#include "Coordinate.hpp"

Game::Game(int size)
{
    m_board = new Board(size);
    m_size = size;
    m_p1 = nullptr;
    m_p2 = nullptr;
    m_curr_p = nullptr;
}

Game::~Game()
{
    delete m_board;
    delete m_p1;
    delete m_p2;
    m_board = nullptr;
    m_p1 = nullptr;
    m_p2 = nullptr;
    m_curr_p = nullptr;
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

    if(m_curr_p == nullptr)
        m_curr_p = *p;
}

bool Game::playerTurn(int row, int col)
{
    std::vector<Coordinate> coords;
    int player_color = getCurrentPlayer()->getColor();

    if(!checkTurn(row, col, coords))
        return false;

    // Set all taken stones to player's color
    for(auto coord : coords)
        m_board->setField(coord.x, coord.y, player_color);

    // Set the placed stone to player's color
    m_board->setField(row, col, player_color);

    // TODO: Remove
    std::cout << *m_board << std::endl;

    return true;
}

const Player *Game::getP1()
{
    return m_p1;
}

const Player *Game::getP2()
{
    return m_p2;
}

const Player *Game::getCurrentPlayer()
{
    return (m_curr_p == m_p1) ? m_p1 : m_p2;
}

const Player *Game::getCurrentOpponent()
{
    return (m_curr_p == m_p1) ? m_p2 : m_p1;
}

bool Game::checkTurn(int row, int col, std::vector<Coordinate> &coords)
{
    std::vector<Coordinate> temp;
    int player_color = getCurrentPlayer()->getColor();
    int opponent_color = getCurrentOpponent()->getColor();
    int color;

    // Can't place a stone on a non-empty field
    // getField() also throws an exception on invalid coords
    try {
        if(m_board->getField(row, col) != Color::EMPTY)
            return false;
    } catch(...) {
        return false;
    }

    // horizontal, left
    for(int i = col - 1; i >= 0; i--) {
        color = m_board->getField(row, i);
        if(color == player_color) {
            coords.insert(coords.end(), temp.begin(), temp.end());
            break;
        }

        if(color != opponent_color)
            break;

        temp.push_back(Coordinate(row, i));
    }

    temp.clear();
    // horizontal, right
    for(int i = col + 1; i < m_board->getSize(); i++) {
        color = m_board->getField(row, i);
        if(color == player_color) {
            coords.insert(coords.end(), temp.begin(), temp.end());
            break;
        }

        if(color != opponent_color)
            break;

        temp.push_back(Coordinate(row, i));
    }

    temp.clear();
    // vertical, up
    for(int i = row - 1; i >= 0; i--) {
        color = m_board->getField(i, col);
        if(color == player_color) {
            coords.insert(coords.end(), temp.begin(), temp.end());
            break;
        }

        if(color != opponent_color)
            break;

        temp.push_back(Coordinate(i, col));
    }

    temp.clear();
    // vertical, down
    for(int i = row + 1; i < m_board->getSize(); i++) {
        color = m_board->getField(i, col);
        if(color == player_color) {
            coords.insert(coords.end(), temp.begin(), temp.end());
            break;
        }

        if(color != opponent_color)
            break;

        temp.push_back(Coordinate(i, col));
    }

    temp.clear();
    // left diagonal, up
    for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        color = m_board->getField(i, j);
        if(color == player_color) {
            coords.insert(coords.end(), temp.begin(), temp.end());
            break;
        }

        if(color != opponent_color)
            break;

        temp.push_back(Coordinate(i, j));
    }

    temp.clear();
    // left diagonal, down
    for(int i = row + 1, j = col + 1; i < m_board->getSize() &&
            j < m_board->getSize(); i++, j++) {
        color = m_board->getField(i, j);
        if(color == player_color) {
            coords.insert(coords.end(), temp.begin(), temp.end());
            break;
        }

        if(color != opponent_color)
            break;

        temp.push_back(Coordinate(i, j));
    }

    temp.clear();
    // right diagonal, up
    for(int i = row - 1, j = col + 1; i >= 0 && j < m_board->getSize();
            i--, j++) {
        color = m_board->getField(i, j);
        if(color == player_color) {
            coords.insert(coords.end(), temp.begin(), temp.end());
            break;
        }

        if(color != opponent_color)
            break;

        temp.push_back(Coordinate(i, j));
    }

    temp.clear();
    // right diagonal, down
    for(int i = row + 1, j = col - 1; i < m_board->getSize() && j >= 0;
            i++, j--) {
        color = m_board->getField(i, j);
        if(color == player_color) {
            coords.insert(coords.end(), temp.begin(), temp.end());
            break;
        }

        if(color != opponent_color)
            break;

        temp.push_back(Coordinate(i, j));
    }

    // Player has to take at least one opponent's stone
    if(coords.size() == 0)
        return false;

    // Sort coords vector and remove duplicates
    std::vector<Coordinate>::iterator it;
    std::sort(coords.begin(), coords.end(), Coordinate::comp);
    it = std::unique(coords.begin(), coords.end(), Coordinate::comp);
    coords.resize(std::distance(coords.begin(), it));

    return true;
}
