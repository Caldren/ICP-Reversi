/**
 * @file Game.cpp
 * @brief Implementation file of Game class.
 *
 * @author Frantisek Sumsal <xsumsa01@stud.fit.vutbr.cz>
 * @date 28.04.2016
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Game.hpp"
#include "Coordinate.hpp"
#include "AI.hpp"

Game::Game(int size)
{
    m_board = new Board(size);
}

Game::Game(const std::string &filename)
{
    std::string error;

    if(!load(filename, error))
        throw std::runtime_error(error);
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
    m_curr_op = nullptr;
    m_winner = nullptr;
}

void Game::initGame(bool load)
{
    int x = m_board->getSize() / 2;

    if(m_p1 == nullptr || m_p2 == nullptr)
        throw std::invalid_argument("Both players must be set before "
                                    "game initialization");

    // Initial stone placement
    m_board->setField(x, x, Color::WHITE);
    m_board->setField(x - 1, x - 1, Color::WHITE);
    m_board->setField(x, x - 1, Color::BLACK);
    m_board->setField(x - 1, x, Color::BLACK);

    // Don't ovewrite score if it was loaded from a file
    if(m_p1->getScore() == 0)
        m_p1->addToScore(2);
    if(m_p2->getScore() == 0)
        m_p2->addToScore(2);

    if(!load && m_curr_p->getType() == Player::AI)
        getAITurn();
}

const Player *Game::addPlayer(const std::string &name, int type, int score,
                              int color)
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

    if(type == Player::HUMAN) {
        *p = new Player(name, color);
    } else if(type == Player::AI) {
        if(m_p1 != nullptr && m_p1->getType() == Player::AI)
            throw std::runtime_error("At least one player must be a human");

        *p = new AI(name, color);
    }

    (*p)->setScore(score);

    if(m_curr_p == nullptr)
        m_curr_p = *p;
    else if(m_curr_op == nullptr)
        m_curr_op = *p;

    return *p;
}

bool Game::playerTurn(int row, int col, bool load)
{
    std::vector<Coordinate> coords;
    int player_color = getCurrentPlayer()->getColor();

    if(!m_board->checkTurn(row, col, coords, player_color))
        return false;

    // Set all taken stones to player's color
    for(auto coord : coords)
        m_board->setField(coord.x, coord.y, player_color);

    // Set the placed stone to player's color
    m_board->setField(row, col, player_color);

    // Add taken stones to player's score and
    // subtract them from opponent's score
    int score = coords.size();
    m_curr_p->addToScore(score + 1);
    m_curr_op->subFromScore(score);

    // Add current turn into history
    m_history.add(row, col, getCurrentPlayer()->getColor(), coords);

    // Make the opponent current player
    switchPlayers(load);

    return true;
}

bool Game::skipTurn(int color, bool load)
{
    int player_color = (color == -1) ? getCurrentPlayer()->getColor() : color;

    if(!checkPossibleTurn(player_color))
        return false;

    // No possible moves
    // Add current turn into history
    m_history.add(-1, -1, getCurrentPlayer()->getColor(), {});

    // Make the opponent current player
    switchPlayers(load);

    return true;
}

bool Game::prevTurn()
{
    const HistoryItem *h = m_history.moveBack();

    if(h == nullptr)
        return false;

    if(h->x != -1 && h->y != -1) {
        m_board->setField(h->x, h->y, Color::EMPTY);
        m_curr_op->subFromScore(1);
    }

    int op_color = (h->color == Color::BLACK) ? Color::WHITE : Color::BLACK;
    for(auto coord : h->stones) {
        m_board->setField(coord.x, coord.y, op_color);
    }

    m_curr_p->addToScore(h->stones.size());
    m_curr_op->subFromScore(h->stones.size());

    switchPlayers(true);
    if(m_curr_p->getType() == Player::AI) {
        // If AI took the first turn, move back to former turn,
        // so player can't modify AI's logic
        if(!prevTurn())
            nextTurn();
    }

    return true;
}

bool Game::nextTurn()
{
    const HistoryItem *h = m_history.moveForward();

    if(h == nullptr)
        return false;

    if(h->x != -1 && h->y != -1) {
        m_board->setField(h->x, h->y, h->color);
        m_curr_p->addToScore(1);
    }

    for(auto coord : h->stones) {
        m_board->setField(coord.x, coord.y, h->color);
    }

    m_curr_p->addToScore(h->stones.size());
    m_curr_op->subFromScore(h->stones.size());

    switchPlayers(true);
    if(m_curr_p->getType() == Player::AI)
        nextTurn();

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
    return m_curr_p;
}

const Player *Game::getCurrentOpponent()
{
    return m_curr_op;
}

const Player *Game::getWinner()
{
    return m_winner;
}

void Game::switchPlayers(bool history)
{
    Player *p = m_curr_p;
    m_curr_p = m_curr_op;
    m_curr_op = p;

    if(checkGameEnd())
        return;

    if(m_curr_p->getType() == Player::AI && !history)
        getAITurn();
}

const Board *Game::getBoard()
{
    return m_board;
}

bool Game::isGameOver()
{
    return m_game_over;
}

bool Game::save(const std::string &filename, std::string &error)
{
    std::ofstream out;

    if(m_p1 == nullptr || m_p2 == nullptr) {
        error = "Can't save uninitialized game";
        return false;
    }

    try {
        out.open(filename.c_str());
    } catch(const std::exception &e) {
        error = e.what();
        return false;
    }

    out << m_board->getSize() << '\n';
    for(auto p : std::vector<Player*>{m_p1, m_p2}) {
        out << p->getType() << '\t' << p->getName();
        if(p->getType() == Player::AI)
            out << '\t' << ((AI*)p)->getAlgorithm();
        out << '\n';
    }

    const std::vector<HistoryItem> h = m_history.getData(true);
    for(auto item : h) {
        out << item.x << '\t' << item.y << '\t' << item.color << "\n";
    }

    out.close();

    return true;
}

bool Game::load(const std::string &filename, std::string &error)
{
    std::ifstream in;
    std::string input, name;
    int type, color, size;
    int x, y;

    if(m_p1 != nullptr || m_p2 != nullptr) {
        error = "Can't overwrite current game";
        return false;
    }

    try {
        in.open(filename.c_str());

        std::getline(in, input);
        size = stoi(input);

        m_board = new Board(size);

        for(unsigned int i = 0; i < 2; i++) {
            std::getline(in, input, '\t');
            type = std::stoi(input);

            if(type == Player::HUMAN) {
                std::getline(in, input, '\n');
                name = input;
                addPlayer(name);
            } else if(type == Player::AI) {
                int idx = -1;
                std::getline(in, input, '\t');
                name = input;
                std::getline(in, input, '\n');
                idx = std::stoi(input);
                const Player *p = addPlayer(name, Player::AI);
                ((AI*)p)->setAlgorithm(idx);
            } else {
                throw std::runtime_error("Invalid player type");
            }
        }

        initGame(true);

        while(std::getline(in, input)) {
            std::vector<Coordinate> coords;
            std::istringstream is(input);
            is >> x >> y >> color;

            if(x == -1 && y == -1) {
                if(!skipTurn(-1, true)) {
                    throw std::runtime_error("Invalid turn skip");
                }
            } else {
                if(!playerTurn(x, y, true)) {
                    std::ostringstream os;
                    os << "Invalid turn coords <" << x << ";" << y << ">";
                    throw std::runtime_error(os.str());
                }
            }
        }

        if(getCurrentPlayer()->getType() == Player::AI && !checkGameEnd())
            throw std::runtime_error("Invalid save file (no coords for AI");

    } catch(const std::exception &e) {
        error = e.what();
        if(error == "stoi")
            error = "Invalid data";

        return false;
    }

    in.close();

    return true;
}

bool Game::checkGameEnd()
{
    m_game_over = false;
    m_winner = nullptr;

    if(checkPossibleTurn(getP1()->getColor()) &&
       checkPossibleTurn(getP2()->getColor())) {
        m_game_over = true;

        int p1c = getP1()->getColor();
        int p2c = getP2()->getColor();
        int p1s = 0, p2s = 0, es = 0;
        int color;

        for(int i = 0; i < m_board->getSize(); i++) {
            for(int j = 0; j < m_board->getSize(); j++) {
                color = m_board->getField(i, j);

                if(color == p1c)
                    p1s++;
                else if(color == p2c)
                    p2s++;
                else
                    es++;
            }
        }

        if(p1s > p2s) {
            m_winner = m_p1;
            m_p1->setScore(p1s + es);
            m_p2->setScore(p2s);
        } else if(p2s > p1s) {
            m_winner = m_p2;
            m_p1->setScore(p1s);
            m_p2->setScore(p2s + es);
        } else {
            m_winner = nullptr;
            m_p1->setScore(p1s);
            m_p2->setScore(p2s);
        }
    }

    return m_game_over;
}

bool Game::checkPossibleTurn(int color)
{
    std::vector<Coordinate> coords;

    for(int i = 0; i < m_board->getSize(); i++) {
        for(int j = 0; j < m_board->getSize(); j++) {
            if(m_board->getField(i, j) == Color::EMPTY) {
                // Check for possible moves on current coords
                if(m_board->checkTurn(i, j, coords, color))
                    return false;
            }
        }
    }

    return true;
}

void Game::getAITurn()
{
    Coordinate coord;
    coord = m_curr_p->makeTurn(m_board);
    if(coord.x == -1 || coord.y == -1) {
        if(!skipTurn())
            throw std::runtime_error("AI algorithm error - invalid coords");
    } else {
        playerTurn(coord.x, coord.y);
    }
}
