#ifndef __ROULETTE__
#define __ROULETTE__

#include "../player/player.hpp"

#include <vector>
#include <memory>

/**
 * @brief This class represent a roulette
 * 
 * This class is used in Observe pattern as Publisher
 * 
 */
class Roulette
{
public:
    /**
     * @brief Construct a new Roulette object
     * 
     */
    Roulette();
    /**
     * @brief Destroy the Roulette object
     * 
     */
    ~Roulette() = default;
    /**
     * @brief Simulate a spin of roulette
     * 
     */
    void spin();
    /**
     * @brief Subscribe to see the result of spin
     * 
     */
    void subscribe(std::shared_ptr<Player>& new_sub);
private:
    std::vector<std::shared_ptr<Player>> subs;

};

#endif
