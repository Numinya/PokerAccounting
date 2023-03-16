#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>

//forward declaration
class game_class;

class player
{
    friend game_class;

    private:
        std::string name;
        int balance;
        bool folded;                // has the player folded
        bool all_in;                // is the player allin
        int round_bet;              // money player put in this round
        int total_bet;              // money player put in this game
        int index;

        void bet();
        


    public:
        player(std::string s, int starting, int i) {
            name = s;
            balance = starting;
            folded = false;
            all_in = false;
            round_bet = 0;
            total_bet = 0;
            index = i;
        }

        // in() returns true if the player is still in the round
        bool in() {
            return !(all_in || folded);
        }
};

#endif