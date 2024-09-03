#ifndef __PLAYER__
#define __PLAYER__

#include "betNote.hpp"

#include <string>
// Represent a bet to the roulette
using Bet = bool(*)(int);

/**
 * @brief This class represent a player on the roulette game
 * 
 * This class is used in Observe pattern as Subcriber
 */
class Player
{
public:
    /**
     * @brief Construct a new Player object
     * 
     * @param name player name
     */
    Player(std::string name);
    /**
     * @brief Destroy the Player object
     * 
     */
    ~Player() = default;
    /**
     * @brief Make a new bet
     * 
     * @param new_bet what the player bets
     */
    void bet(Bet new_bet);
    /**
     * @brief update with the result of roulette
     * 
     * @param result number in the roulette
     */
    void update(int result);
    /**
     * @brief Get the player gain
     * 
     * @return int current player gain
     */
    int get_gain();
private:
    Bet current_bet;
    int gain;
    std::string my_name;
    betNote book;
};

#endif
