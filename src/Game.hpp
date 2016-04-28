/**
 * @file Game.hpp
 * @class Game
 * @brief %Game logic implementation.
 *
 * @author Frantisek Sumsal <xsumsa01@stud.fit.vutbr.cz>
 * @date 28.04.2016
 */
#ifndef __GAME_HPP_INCLUDED
#define __GAME_HPP_INCLUDED

#include <vector>
#include "Board.hpp"
#include "Player.hpp"
#include "Coordinate.hpp"
#include "History.hpp"

class Game {
public:
    /**
     * @brief Create Game object.
     * @see Board::SIZES
     * @param size %Game Board size (default: 8)
     */
    Game(int size = 8);
    /**
     * @brief Create Game object by loading previously saved data from given
     *        file.
     * @see load()
     * @see save()
     * @param filename Filename with saved Game data
     */
    Game(const std::string &filename);
    Game(const Game &) = delete;
    ~Game();
    void operator=(const Game &) = delete;

    /**
     * @brief Initialize game.
     * @details Set first iset of stones on game Board, set Player's scores
     *          to 2 and prepare first Player for their turn.
     *          Throws std::invalid_argument when current game has not both
     *          players initialized.
     * @see load()
     * @param load Set this parameter to true if initializing loaded game to
     *             prevent AI intervention during game loading.
     */
    void initGame(bool load = false);
    /**
     * @brief Add Player into game.
     * @details Throws std::range_error when both Player slots are occupied and
     *          std::runtime_error when at least one Player is not a human.
     * @see Player
     * @param name %Player name
     * @param type %Player type (default: Player::HUMAN)
     * @param score %Player score (default: 0)
     * @param color %Player color (default: -1, which means auto-select first
     *              available color)
     * @return const pointer to created Player object
     */
    const Player *addPlayer(const std::string &name, int type = Player::HUMAN,
                            int score = 0, int color = -1);
    /**
     * @brief Apply player turn to game board.
     * @details If given turn is valid, function also modifies player scores
     *          accordingly, makes a new record in game History and switches
     *          game control to the second Player.
     * @see load()
     * @param row Board x coordinate
     * @param col Board y coordinate
     * @param load Set this parameter to true if loading a game from file to
     *             correctly initialize game state
     * @return true if given turn is valid, false otherwise
     */
    bool playerTurn(int row, int col, bool load = false);
    /**
     * @brief Skip current turn.
     * @details If turn of a Player of given color can be skipped, function
     *          switches game control to the next Player.
     * @see Color::ColorTypes
     * @param color %Player color code
     * @param load Set this parameter to true if loading a game from file to
     *             correctly initialize game state
     * @return true if current turn can be skipped, false otherwise
     */
    bool skipTurn(int color = -1, bool load = false);
    /**
     * @brief Move game state one turn back in history.
     * @see History
     * @return true if previous game state exists, false otherwise
     */
    bool prevTurn();
    /**
     * @brief Move game state one turn forward in history.
     * @see History
     * @return true if next game state exists, false otherwise
     */
    bool nextTurn();

    /**
     * @return const pointer to the first player (can be nullptr)
     */
    const Player *getP1();
    /**
     * @return const pointer to the second player (can be nullptr)
     */
    const Player *getP2();
    /**
     * @return const pointer to the current player (can be nullptr)
     */
    const Player *getCurrentPlayer();
    /**
     * @return const pointer to the current opponent (can be nullptr)
     */
    const Player *getCurrentOpponent();
    /**
     * @details If getWinner() returns nullptr, game ended with a draw
     * @return const pointer to the game winner
     */
    const Player *getWinner();
    /**
     * @brief Switch game control to the next player.
     * @details If the next player is an AI, function also gets a next turn
     *          from the AI object and switches control back to human player.
     * @param history Set this parameter to true if moving around in game
     *                history to prevent AI intervention
     */
    void switchPlayers(bool history = false);

    /**
     * @return constant pointer to current game board
     */
    const Board *getBoard();
    /**
     * @brief Check if current game is over.
     * @details If current game is over, method getWinner() should return game
     *          winner.
     * @see getWinner()
     * @return true if current game is over, false otherwise
     */
    bool isGameOver();

    /**
     * @brief Load game state from a file.
     * @param filename Name of the file with saved game state
     * @param error When error occurs, appropriate error message will be copied
     *              into this parameter
     * @return true if save was successful, false otherwise
     */
    bool save(const std::string &filename, std::string &error);
    /**
     * @brief Save game state into a given file.
     * @param filename Name of the destination file
     * @param error When error occurs, appropriate error message will be copied
     *              into this parameter
     * @return true if load was successful, false otherwise
     */
    bool load(const std::string &filename, std::string &error);

private:
    /**
     * @brief Check if game is in its end state
     * @details Function checks for possible turns of both players. If neither
     *          one of them is able to make a turn, game is over, appropriate
     *          flag is set and winner variable is populated.
     * @see m_game_over
     * @see m_winnner
     * @return true if game is in its end state, false otherwise
     */
    bool checkGameEnd();
    /**
     * @brief Check if player with given color is able to make a turn.
     * @see Color::ColorTypes
     * @param color %Color code
     * @return true if player with given color is able to make a turn,
     *         false otherwise
     */
    bool checkPossibleTurn(int color);
    /**
     * @brief Get a turn coordinates from AI player and make a turn.
     */
    void getAITurn();

private:
    Player *m_p1 = nullptr;         /**< Player 1 */
    Player *m_p2 = nullptr;         /**< Player 2 */
    Player *m_curr_p = nullptr;     /**< Pointer to current player */
    Player *m_curr_op = nullptr;    /**< Pointer to current opponent */
    Player *m_winner = nullptr;     /**< Pointer to winner */
    Board *m_board = nullptr;       /**< Game board */
    History m_history;              /**< Game history */
    bool m_game_over = false;       /**< Game over flag */
};

#endif
