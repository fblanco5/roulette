# Roulette Game

This program is part of a job interview process.

The program simulates 6 people playing roulette. It consist of 10000 rounds where each player makes their bet and then lets the roulette spin to finally allocate the winnings accordingly.

At the final is shown the total gain.

## Compilation

For compilate this program you only should run make, this will create the binary called `roulette_game` in the diretory `bin`.
To execute the program run 

    ./bin/roulette_game

## Desing

The program is implemented with a observer pattern, where the roulette is the publisher and each player is a subscriber.

The roulette publish a number and each player updates his gain. 

The next mount is encapsulate in the class betNote where is the logic for this.

The player expose a bet method where the bet is settings. A bet is a function where given a number return a bool indicate if the player won or lost.

The main file simulates the process of 10000 rounds managing concurrency between the players and a croupier.
