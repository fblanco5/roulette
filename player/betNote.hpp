#ifndef __BET_NOTE__
#define __BET_NOTE__

#include <vector>

/**
 * @brief This class represent a paper with the bet annotations
 * 
 * This encapsulate the logic for calculate the next mount
 * 
 */
class betNote
{
public:
    /**
     * @brief Construct a new bet Note object
     * 
     */
    betNote();
    /**
     * @brief Destroy the bet Note object
     * 
     */
    ~betNote();
    /**
     * @brief Get the amount to bet
     * 
     * @return int how much is the next bet
     */
    int get_bet();
    /**
     * @brief Update the bet data in case of winning
     * 
     */
    void win();
    /**
     * @brief Update the bet data in case of lossing
     * 
     */
    void lost();

private:
    std::vector<int> bet_book;
    int bet;
};


#endif
