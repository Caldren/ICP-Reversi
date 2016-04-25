#include <iostream>
#include <exception>
#include <string>
#include <limits>
#include <iomanip>
#include "AI.hpp"
#include "TUI.hpp"

TUI::~TUI()
{
    delete m_game;
    m_game = nullptr;
}

void TUI::init()
{
    int n = '\n';
    char c;
    std::string str;

    do {
        std::cout << "Do you wan't to start a new game (n) or load an "
                  << "existing one (l)? ";
        std::cin >> c;

        if(c == 'n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();
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
                std::cerr << "Couldn't create game board: " << e.what()
                          << std::endl;
                exit(1);
            }

            playerPrompt(1);
            playerPrompt(2);
            m_game->initGame();
        } else if(c == 'l') {
            loadGame();
        }
    } while(c != 'l' && c != 'n');

    gameControl();
}

void TUI::loadGame()
{
    std::string file, error;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();
    std::cout << "Enter filename: ";
    std::getline(std::cin, file);

    try {
        m_game = new Game(file);
    } catch(const std::exception &e) {
        std::cerr << "Failed to load saved game: " << e.what() << std::endl;
        exit(1);
    }
}

void TUI::playerPrompt(int id)
{
    char c;
    int algo, range;
    std::string str;
    const Player *p;

    do {
        std::cout << "Player " << id << " settings:" << std::endl
                  << "Type (h for human, a for AI): ";
        std::cin >> c;

        if(c == 'h' || c == 'a') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();
            std::cout << "Player " << id << " name: ";
            getline(std::cin, str);

            try {
                if(c == 'h') {
                    m_game->addPlayer(str);
                } else {
                    p = m_game->addPlayer(str, Player::AI);
                    range = ((AI*)p)->getAlgorithmCount() - 1;
                    if(range < 0) {
                        throw std::runtime_error("No AI algorithms available");
                    }

                    do {
                        std::cout << "Choose AI algorithm (0 - "
                                  << range << "): ";
                        std::cin >> algo;
                        try {
                            ((AI*)p)->setAlgorithm(algo);
                            break;
                        } catch(const std::exception &e) {
                            std::cerr << e.what() << std::endl;
                        }
                    } while(true);
                }
            } catch(const std::exception &e) {
                std::cerr << "Couldn't add player: " << e.what() << std::endl;
                c = '\0';
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
    std::string state = "";
    std::string file;

    do {
        if(m_game->isGameOver()) {
            const Player *p = m_game->getWinner();
            if(p == nullptr)
                state = "*** GAME END - DRAW! ***\n";
            else
                state = "*** GAME END - WINNER: " + p->getName() + " ***\n";
        }

        drawUI();
        cp = m_game->getCurrentPlayer();
        std::cout << "Current player: " << cp->getName() << std::endl;
        std::cout << "Options:" << std::endl
                  << "p 1 2\tPlace stone on coords <1;2>" << std::endl
                  << "s\tSkip turn" << std::endl
                  << "b\tPrevious turn from history" << std::endl
                  << "f\tNext turn from history" << std::endl
                  << "v\tSave current game" << std::endl
                  << "q\tQuit" << std::endl << std::endl;
        if(state.size() > 0) {
            std::cout << state << std::endl;
            state = "";
        }

        std::cout << "Selected option: ";
        std::cin >> c;

        switch(c) {
        case 'p':
            std::cin >> x >> y;
            if(!m_game->playerTurn(x - 1, y - 1))
                state= "Invalid turn! Try again.\n";

            break;

        case 's':
            if(!m_game->skipTurn())
                state = "Can't skip current turn - at least one valid move "
                        "is available\n";
            break;
        case 'b':
            if(!m_game->prevTurn())
                state = "No previous turn available in history buffer\n";
            break;
        case 'f':
            if(!m_game->nextTurn())
                state = "No next turn available in history buffer\n";
            break;
        case 'v':
            std::cout << "Enter filename: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();
            std::getline(std::cin, file);
            if(m_game->save(file, state))
                state = "Game was successfully saved";
            break;
        case 'q':
            return;
            break; // Just in case
        default:
            state = "Invalid option, try again\n";
        }
    } while(std::cin.good());
}
