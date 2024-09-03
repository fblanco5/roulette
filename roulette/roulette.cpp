#include "roulette.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

Roulette::Roulette()
{
   std::srand(time(NULL));
}
void 
Roulette::spin()
{
    int result = std::rand() % 37;

    std::cout << "The number on the roulette is: " << result << std::endl;
    for(auto s : this->subs){
        s->update(result);
    }
}

void
Roulette::subscribe(std::shared_ptr<Player>& new_sub)
{
    this->subs.push_back(new_sub);
}
