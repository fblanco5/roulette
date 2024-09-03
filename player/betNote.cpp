#include "betNote.hpp"

betNote::betNote()
{
    this->bet_book = {1,2,3,4};
    this->bet = 0;
}

betNote::~betNote()
{
    this->bet_book.clear();
}

int
betNote::get_bet()
{
    this->bet = this->bet_book.front() + this->bet_book.back();
    return this->bet;
}

void
betNote::win()
{
    if(this->bet == 0){
        // No bet yet
        return;
    }

    if(this->bet_book.front() + bet > 4000){
        this->bet_book = {1,2,3,4};
    }
    else{
        this->bet_book.push_back(bet);
    }

    this->bet = 0;

}

void
betNote::lost()
{
    if(this->bet == 0){
        // No bet yet
        return;
    }
    this->bet = 0;

    if(this->bet_book.size() <= 2){
        this->bet_book = {1,2,3,4};
        return;
    }

    this->bet_book.erase(this->bet_book.begin());
    this->bet_book.pop_back();

}