#include "roulette/roulette.hpp"
#include "player/player.hpp"

#include <thread>
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <unordered_set>
#include <memory>


std::mutex round_mtx, bet_mtx;
std::condition_variable round_cv, bet_cv;
int players_bet_readys = 0;
int round_counter = 0;
bool start_bet = false;
bool players_ready = false;
bool players_beted = false;

const int rounds = 10000;


/**
 * @brief Simulate a player in the game.
 * The player wait the bet signal and then he bet, 
 * finally announces that he already bet.
 * 
 * @param player player to simulate
 * @param player_bet bet from the player
 */
void player_rounds(std::shared_ptr<Player> player, Bet player_bet){
    int last_round = rounds+1; // Init to evaluate in true
    while (round_counter < rounds)
    {
        std::unique_lock<std::mutex> lck(round_mtx);
        // Wait to bet
        bet_cv.wait(lck, [&last_round](){return start_bet && last_round != round_counter;});
        last_round = round_counter;
        
        // Bet
        player->bet(player_bet);
        players_bet_readys++;
        round_cv.notify_all();

    }
}

/**
 * @brief Simulate a croupier.
 * The croupier indicate when the player can bet,
 * awaits for them, and spin the roulette.
 * 
 * @param roulette The roulette to spin
 */
void croupier_rounds(Roulette& roulette){
    while (round_counter < rounds)
    {
        std::unique_lock<std::mutex> lck(round_mtx);
        round_counter++;
        std::cout << "Starting round " << round_counter << std::endl;

        // Wait the bets
        start_bet = true;
        bet_cv.notify_all();

        round_cv.wait(lck,[](){ return players_bet_readys == 6; });
        players_bet_readys = 0;

        // Spin the roulette
        std::cout << " *** The roulette start to spin *** " << std::endl;
        roulette.spin();
    }
}

const std::unordered_set<int> red = {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};

int main()
{
    std::shared_ptr<Player> A = std::make_shared<Player>("Juan Carlos Bodoque");
    std::shared_ptr<Player> B = std::make_shared<Player>("Tulio Trivino");
    std::shared_ptr<Player> C = std::make_shared<Player>("Felipe Mario Hugo");
    std::shared_ptr<Player> D = std::make_shared<Player>("Juanin Juan Harry");
    std::shared_ptr<Player> E = std::make_shared<Player>("Policarpo Avedano");
    std::shared_ptr<Player> F = std::make_shared<Player>("Guaripolo");

    Roulette roulette;

    roulette.subscribe(A);
    roulette.subscribe(B);
    roulette.subscribe(C);
    roulette.subscribe(D);
    roulette.subscribe(E);
    roulette.subscribe(F);
    
    // Player A bet for red numbers
    std::thread player_a(player_rounds, A, [](int n){return red.find(n) != red.end();});
    // Player B bet for black numbers
    std::thread player_b(player_rounds, B, [](int n){return n != 0 && red.find(n) == red.end();});
    // Player C bet for over 18
    std::thread player_c(player_rounds, C, [](int n){return n > 18;});
    // Player D bet for under 18
    std::thread player_d(player_rounds, D, [](int n){return n != 0 && n <= 18;});
    // Player E bet for even
    std::thread player_e(player_rounds, E, [](int n){return n != 0 && n%2 == 0;});
    // Player F bet for odd
    std::thread player_f(player_rounds, F, [](int n){return n%2 == 1;});

    // Init croupier
    std::thread croupier(croupier_rounds, std::ref(roulette));

    // Wait all threads
    player_a.join();
    player_b.join();
    player_c.join();
    player_d.join();
    player_e.join();
    player_f.join();
    croupier.join();

    // Get total gain
    int total_gain = A->get_gain();
    total_gain += B->get_gain();
    total_gain += C->get_gain();
    total_gain += D->get_gain();
    total_gain += E->get_gain();
    total_gain += F->get_gain();

    std::cout << "The final gain is: " << total_gain << std::endl;

    return 0;
}
