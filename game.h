#pragma once

#define HAND_SIZE 6
#define DECK_SIZE 108

#define d_bool char

struct s_player
{
    char * hand;
    int bet;
    int score;
};

typedef struct s_player t_player;

struct s_game
{
    char * cards;
    d_bool end;
    int indeck;
    int broker;
    int bet;
    t_player * player;
};

typedef struct s_game t_game;

void game_loop(t_game * g);

t_game * game_init();

t_player * player_init();

void game_cards_shuffle(char * cards, int n);

void game_cards_fill(char * cards, int n);

void game_cards_dump(char * cards, int n);

void print_player_coins(t_player * p);

void broker_new_hand(t_game * g);

void player_new_hand(t_game * g);

void print_player_hand(t_player * p);

void broker_place_bet(t_game * g);

void player_place_bet(t_game * g);

int player_ask_cards(t_game * g);

int ask_V_value();

int sum_player_hand(t_player * p);

void print_turn_results(t_game * g, int p_hand);

void player_jackpot(t_game * g);

void player_breakthrough(t_game * g);

void player_lost(t_game * g);

void player_win(t_game * g);

d_bool is_game_finished(t_game * g);

void game_end(t_game * g);
