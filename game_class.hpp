#ifndef GAME_CLASS_HPP
#define GAME_CLASS_HPP

#include <iostream>
#include <vector>
#include "player.hpp"

class game_class {
    private:
        std::vector<player> players;

        // points to
        player *current;                  // current player's turn       
        player *big_blind;                // player that is big blind
        player *small_blind;              // player that is small blind
        player *highest_bet_guy;          // player that has the highest bet
        player *starting_player;          // player that starts every round

        // initialization things
        int player_num;                   // number of players
        int start_amount;                 // starting amount for all players
        int big_blind_val;                // big blind value
        int small_blind_val;              // small blind value

        // winner
        int winner;                       // index of the winning player

        // stuff related to folds and allins
        int fold_num;                     // number of players that folded
        bool all_folded;                  // true if everyone has folded
        bool all_in;                      // true if one person all in-ed
        
        const std::string round_name[4] = {"PRE-FLOP", "FLOP", "TURN", "RIVER"};

       

        // pots
        // anticipating the need for a pot class because of all in
        int pot;

        // helper returns the address of the player in order after p
        player* increment_ptr(player *p);

        // helper functions to take_action
        // calculation simplifier
        void adjust_balance_bet(int value);

        // code that deals with fold scenarios
        void fold();

        // code that processes a bet command
        void process_bet();

        // code that processes a raise command
        void process_raise();

        // code that processes all in
        void process_all_in();

        // prints info of the current round
        void print_info();


    public:
        bool done;              // flow control
        

        game_class(int bruh);   //idk why but i have to put a parameter
        game_class(int debug, int test);

        // prints the current round being played
        void print_round(int i);

        // updates player balances after blinds are taken
        void take_blinds();

        // returns true if the round has completed
        bool agreed();

        // player_in() returns true if the current player is still in
        bool player_in();

        // returns true if everyone has folded
        bool get_folded();

        // updates the pointer that points to who starts
        void update_starter();

        // updates the current player by increasing it by one turn
        void update_current();

        // take_action() takes the player's action 
        void take_action();

        // resets various fields to the beginning of round
        void reset_round();

        // finds the winner of the round and updates winner
        void get_winner();

        // redistributes funds depending on winner
        void distribute_funds();

        // resets various fields to the beginning of game
        void reset_game();
};


#endif