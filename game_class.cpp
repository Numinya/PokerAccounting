#include "game_class.hpp"
#include <iostream>


// initialize game
game_class::game_class(int bruh) {   //idk why but i have to put a parameter
    // initialize players
    std::cout << "Welcome to Poker!" << std::endl;
    std::cout << "Number of Players: ";           // number of players
    std::cin >> player_num;

    std::cout << "Starting amount: $";            // starting amount
    std::cin >> start_amount;

    // initialize players of the game
    std::cout << "Enter names of Players:";
    std::cout << std::endl;
    std::string temp;

    for(int i = 0; i < player_num; i++) {
        std::cin >> temp;
        players.push_back(player(temp, start_amount, i));
    }
    
    // initialize blinds
    std::cout << "Big blind amount: $";           // big blind amount
    std::cin >> big_blind_val;

    std:: cout << "Small blind amount: $";        // small blind amount
    std::cin >> small_blind_val;

    small_blind = &players[0];
    big_blind = &players[1];
    current = &players[2];
    starting_player = small_blind;
    pot = 0;
}


game_class::game_class(int debug, int test)
{
    player_num = 6;
    start_amount = 2000;
    players.push_back(player("Leo", start_amount, 0));
    players.push_back(player("Dino", start_amount, 1));
    players.push_back(player("Bage", start_amount, 2));
    players.push_back(player("Kevin", start_amount, 3));
    players.push_back(player("Dog", start_amount, 4));
    players.push_back(player("Leapedman", start_amount, 5));

    big_blind_val = 50;
    small_blind_val = 20;

    small_blind = &players[0];
    big_blind = &players[1];
    current = &players[2];
    starting_player = small_blind;

    pot = 0;
    fold_num = 0;
    all_folded = false;
}

void game_class::print_round(int i) {
    std::cout << round_name[i] << std::endl;
}


void game_class::take_blinds() {
    // update balance
    small_blind->balance -= small_blind_val;
    big_blind->balance -= big_blind_val;

    // update roundbets
    small_blind->round_bet += small_blind_val;
    big_blind->round_bet += big_blind_val;

    // update totalbets
    small_blind->total_bet += small_blind_val;
    big_blind->total_bet += big_blind_val; 

    // update who owns the highest bet
    highest_bet_guy = big_blind;     

    //update pot contents
    pot += small_blind_val + big_blind_val;    
}


bool game_class::agreed() {
    return (highest_bet_guy == current);
}


bool game_class::player_in() {
    return current->in();
}

// get_folded 
bool game_class::get_folded() {
    return all_folded;
}

void game_class::update_starter() {
    for (int i = 0; i < player_num; i++) {
        int position = (starting_player->index + i) % player_num;
        if (!players[position].folded) {
            starting_player = &players[position];
            break;
        }
    }

    current = starting_player;
}

player* game_class::increment_ptr(player *p) {
    return &players[(p->index + 1) % player_num];
}

void game_class::update_current() {
    current = increment_ptr(current);
}


//--------------------- main code -----------------------------------
void game_class::adjust_balance_bet(int value) {
    current->balance -= value;    // subtract bet money from balance
    current->round_bet += value;  // update roundbet
    current->total_bet += value;  // update totalbet

    pot += value;                 // add money to po
}

void game_class::fold() {
    current->folded = true;                // change folded to true
    pot += current->round_bet;             // add money to pot
    fold_num++;
    if (fold_num == player_num - 1) {
        all_folded = true;
    }
}

void game_class::process_bet() {
    int value;
    std::cin >> value;
    adjust_balance_bet(value - current->round_bet);

    highest_bet_guy = current;    // current is now highest bet guy
}

void game_class::process_raise() {
    int value;
    std::cin >> value;
    adjust_balance_bet(value + highest_bet_guy->round_bet);
    highest_bet_guy = current;
}

void game_class::process_all_in() {

}

void game_class::print_info() {
    std::cout << "------------------------------" << std::endl;
    std::cout << "current turn: " << current->name << std::endl;
    std::cout << "balance: " << current->balance << std::endl;
    std::cout << "bet to play in: " << highest_bet_guy->round_bet << std::endl;
    std::cout << "total pot: " << pot << std::endl;
    std::cout << "------------------------------" << std::endl;
}

void game_class::take_action() {
    std::string action;
    bool done = false;

    while (!done) {
        std::cout << current->name << "'s move: ";
        std::cin >> action;

        if (action == "fold") {
            fold();
            done = true;
        }

        else if (action == "bet") {
            process_bet();
            done = true;
        }

        else if (action == "call") {
            adjust_balance_bet(highest_bet_guy->round_bet - current->round_bet);
            done = true;
        }

        else if (action == "raise") {
            process_raise();
            done = true;
        }

        else if (action == "all in") {             
            process_all_in();
            done = true;
        } 

        else if (action == "quit") {
            exit(EXIT_SUCCESS);
        }

        else if (action == "info") {
            print_info();
        }

        else {
            // assumption value is check
            // do nothing
            done = true;
        }
    }
    
}


void game_class::reset_round() {
    current = starting_player;

    // reset everyone's round bet
    for (int i = 0; i < player_num; i++) {
        players[i].round_bet = 0;
    }

    highest_bet_guy = current;
}

void game_class::get_winner() {
    if(!all_folded) {
        std::string winner_name;
        std::cout << "Winner of round: ";
        std::cin >> winner_name;

        for(int i = 0; i < player_num; i++) {
            if (players[i].name == winner_name) {
                winner = i;
            }
        }
    } 
}

void game_class::distribute_funds() {
    // two modes: all-in and regular
    if (all_in) {
        //something
    } 

    else {  // regular win
        players[winner].balance += pot;
    }

}

void game_class::reset_game() {
    // move pointers one space;
    small_blind = increment_ptr(small_blind);
    big_blind = increment_ptr(big_blind);
    starting_player = small_blind;
    current = increment_ptr(big_blind);
    

    // reset the pots
    pot = 0;

    // reset total bets, in 
    for (int i = 0; i < player_num; i++) {
        players[i].folded = false;
        players[i].all_in = false;
        players[i].total_bet = 0;
    } 

    all_in = false;
}