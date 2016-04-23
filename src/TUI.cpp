#include <iostream>
#include <exception>
#include <string>
#include <limits>
#include <iomanip>
#include "TUI.hpp"

TUI::~TUI()
{
    delete m_game;
    m_game = nullptr;
}

void TUI::init()
{
    int n = '\n';
    std::string str;

    std::cout << "Size of game board (6, 8, 10, 12): ";
    std::getline(std::cin, str);

    try {
        if(str.empty()) {
            n = 8;
        } else {
            std::string::size_type st;
            n = stoi(str, &st);
            if(st != str.size())
                throw std::invalid_argument("Invalid size");
        }

        m_game = new Game(n);
    } catch(const std::exception &e) {
        std::cerr << "Couldn't create game board: " << e.what() << std::endl;
        exit(1);
    }

    playerPrompt(1);
    playerPrompt(2);

    m_game->initGame();
    gameControl();
}

void TUI::playerPrompt(int id)
{
    char c;
    std::string str;

    do {
        std::cout << "Player " << id << " settings:" << std::endl
                  << "Type (h for human, a for AI): ";
        std::cin >> c;

        if(c == 'a') {
            // TODO
            throw std::invalid_argument("TODO");
        } else if(c == 'h') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();
            std::cout << "Player " << id << " name: ";
            getline(std::cin, str);

            try {
                m_game->addPlayer(str);
            } catch(const std::exception &e) {
                std::cerr << "Couldn't add player: " << e.what() << std::endl;
            }
        }
    } while(c != 'a' && c != 'h');
}

void TUI::drawUI()
{
    const Board *b = m_game->getBoard();
    const Player *p1 = m_game->getP1();
    const Player *p2 = m_game->getP2();
    char cp1 = (p1->getColor() == Color::BLACK) ? 'X' : 'O';
    char cp2 = (p2->getColor() == Color::BLACK) ? 'X' : 'O';
    int padding = (b->getSize() / 2 * 5) - 3;
    int color;

    // Clear the screen
    std::cout << std::string(100, '\n');

    // Draw player names and scores
    std::cout << std::setw(1) << "(" << cp1 << ") "
              << std::setw(15) << std::left << p1->getName();
    if(padding - 17 > 0)
        std::cout << std::string(padding - 17, ' ');
    std::cout << std::setw(15) << std::right << p2->getName()
              << std::setw(1) << " (" << cp2 << ")";
    std::cout << std::endl;

    std::cout << std::setw(15) << std::left << p1->getScore();
    if(padding - 10 > 0)
        std::cout << std::string(padding - 10, ' ');
    std::cout << std::setw(15) << std::right << p2->getScore();
    std::cout << std::endl << std::endl;

    // Draw game board
    for(int i = 0; i <= b->getSize(); i++) {
        for(int j = 0; j <= b->getSize(); j++) {
            std::cout.width(4);
            if(i == 0 && j == 0) {
                std::cout << std::setw(4) << " ";
            } else if(i == 0) {
                std::cout << std::setw(1) <<  "|" << std::setw(2) << j << " ";
            } else if(j == 0) {
                std::cout << std::right << i;
            } else {
                color = b->getField(i - 1, j - 1);
                switch(color) {
                case Color::EMPTY:
                    std::cout << "|   ";
                    break;
                case Color::BLACK:
                    std::cout << "| X ";
                    break;
                case Color::WHITE:
                    std::cout << "| O ";
                    break;
                }
            }
        }

        std::cout << std::endl << std::string((b->getSize() + 1) * 4, '-')
                  << std::endl;
    }
}

void TUI::gameControl()
{
    char c;
    int x, y;
    const Player *cp;
    std::string error = "";

    do {
        drawUI();
        cp = m_game->getCurrentPlayer();
        std::cout << "Current player: " << cp->getName() << std::endl;
        std::cout << "Options:" << std::endl
                  << "p 1 2\tPlace stone on coords <1;2>" << std::endl
                  << "s\tSkip turn" << std::endl
                  << "g\tGive up" << std::endl << std::endl;
        if(error.size() > 0) {
            std::cout << error << std::endl;
            error = "";
        }

        std::cout << "Selected option: ";
        std::cin >> c;

        switch(c) {
        case 'p':
            std::cin >> x >> y;
            if(!m_game->playerTurn(x - 1, y - 1))
                error = "Invalid turn! Try again.\n";

            break;

        case 's':
            if(!m_game->skipTurn())
                error = "Can't skip current turn - at least one valid move "
                        "is available\n";
        }
    } while(true);
}