#include "player.hpp"

#include <iostream>

Player::Player(std::string name) : current_bet(nullptr), gain(0), my_name(name)
{
    this->book = betNote();
}

void
Player::bet(Bet new_bet){
    this->current_bet = new_bet;
    std::cout << "I am " << this->my_name << " and i bet $" << this->book.get_bet() << std::endl;
}

void
Player::update(int result)
{
    if(this->current_bet == nullptr){
	std::cout << "I am " << this->my_name << " and i didn't bet" << std::endl;
        return;
    }

    if(this->current_bet(result)){
	std::cout << "I am " << this->my_name << " and i won" << std::endl;
	
        this->gain += this->book.get_bet();
        this->book.win();
    }
    else{
	    std::cout << "I am " << this->my_name << " and i lost" << std::endl;
        this->gain -= this->book.get_bet();
        this->book.lost();
    }
    
    this->current_bet = nullptr;

}

int
Player::get_gain()
{
    return this->gain;
}
