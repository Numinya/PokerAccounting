#include <iostream>
#include <vector>
#include <string>
#include "game_class.hpp"

int main() {    
    game_class game(5, 6); // debugger constructor used

    // start of game
    while (!(game.done)) {
        game.take_blinds();

        // start of round
        for (int i = 0; i < 4 && !game.get_folded(); i++) {   
            game.print_round(i);
            

            do {
                if (game.player_in()) {
                    game.take_action();
                }

                game.update_current();

            } while(!game.agreed() && !game.get_folded());

            game.update_starter();
            game.reset_round();
        }

        game.get_winner();
        game.distribute_funds();
        game.reset_game();
    }   


    return 0;
}