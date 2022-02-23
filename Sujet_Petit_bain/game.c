#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "game.h"

/*
** Initialize the game values
** Calls both card fill & card shuffle
** Init the player struct with the right structure
*/
t_game *game_init()
{
    t_game *ret = malloc(sizeof(t_game));

    srand(time(NULL));
    ret->cards = malloc(DECK_SIZE);
    game_cards_fill(ret->cards, DECK_SIZE);
    game_cards_shuffle(ret->cards, DECK_SIZE);
    ret->end = 0;
    ret->indeck = 0;
    ret->broker = 0;
    ret->bet = 0;
    ret->player = player_init();
    return ret;
}

/*
** Initialize base values for the player
** The hand is a HAND_SIZE sized array of chars each representing a card
** The score is the number of coins held by the player
** The score starts at 15 because it allows the player to either loose or progress a mesurable amount
*/
t_player *player_init()
{
    t_player *ret = malloc(sizeof(t_player));

    ret->hand = malloc(HAND_SIZE);
    memset(ret->hand, 0, HAND_SIZE);
    ret->score = 0;
    ret->score = 15;
    return ret;
}


/*
** This functions shuffles the cards from the deck it needs the number of cards
*/
void game_cards_shuffle(char *cards, int n)
{
    int j;
    int i;
    char t;

    if (n <= 1)
        return;
    for (i = 0; i < n - 1; i++)
    {
        j = i + rand() / (RAND_MAX / (n - i) + 1);
        t = cards[j];
        cards[j] = cards[i];
        cards[i] = t;
    }
}

/*
** Fills the deck with the right amount of each card
*/
void game_cards_fill(char *cards, int n)
{
    char *possibility = "1234569DV";
    for (int i = 0; i < n; ++i)
    {
        cards[i] = possibility[i%9];
    }
}

/*
** Prints all the cards for debug
*/
void game_cards_dump(char * cards, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%c ", cards[i]);
    }
    printf("\n");
}

void print_player_coins(t_player * p)
{
    printf("You have %i coins\n", p->score);
}

void broker_new_hand(t_game * g)
{
    g->broker = 14 + (rand() % 8);
}

void player_new_hand(t_game * g)
{
    memset(g->player->hand, 0, 6);
    strncpy(g->player->hand, g->cards + g->indeck, 2);
    g->indeck += 2;
}

/*
** Prints the player's hand
*/
void print_player_hand(t_player *p)
{
    int i = 0;
    printf("Your hand : ");
    while (p->hand[i+1] != 0)
    {
        printf("%c, ", p->hand[i]);
        ++i;
    }
    printf("%c\n", p->hand[i]);
}

void broker_place_bet(t_game *g)
{
    int r = rand()%5 - 2;
    g->bet = (g->broker - 11);
    if (!(g->bet + r < 0 || g->bet + r > 10))
        g->bet += r;
    printf("Broker bet : %i\n", g->bet);
}

void player_place_bet(t_game *g)
{
    int valid = 0;
    while(!valid)
    {
        printf("Place your bet (5-10)\n");
        scanf("%i%*c", &(g->player->bet));
        if (g->player->bet >= 5 && g->player->bet <= 10)
            valid = 1;
        else
            printf("Invalid bet.\n");
    }
    printf("Your bet : %i\n", g->player->bet);
}

int player_ask_cards(t_game *g)
{
    char ans[100];
    int valid = 0;
    int inhand = 2;
    while (strcmp(ans, "no"))
    {
        while (!valid)
        {
            printf("Do you want a card ? (yes/no)\n");
            scanf("%[^\n]%*c", ans);
            if (!strcmp(ans, "yes") || !strcmp(ans, "no"))
                valid = 1;
            else
                printf("Invalid answer please use 'yes' or 'no'\n");
        }
        valid = 0;
        if (!strcmp(ans, "yes") && inhand < 7)
        {
            g->player->hand[inhand++] = g->cards[g->indeck++];
            print_player_hand(g->player);
        }
        if (inhand >= 6)
            return 6;
    }
    return inhand;
}

int ask_V_value()
{
    int ans;
    int valid = 0;
    while(!valid)
    {
        printf("What Value do you want this V to be ? (1/11)\n");
        scanf("%i%*c", &ans);
        if (ans == 1 || ans == 11)
            valid = 1;
        else
            printf("Invalid value.\n");
    }
    return ans;
}

int sum_player_hand(t_player *p)
{
    int res = 0;
    char * hand = p->hand;
    char card[2] = "\0\0";

    for (int i = 0; hand[i] != 0; ++i)
    {
        card[0] = hand[i];
        if (hand[i] == 'D') {
            res += 10;
        } else if (hand[i] == 'V') {
            res += ask_V_value();
        } else {
            res += atoi(card);
        }
    }
    return res;
}

void print_turn_results(t_game *g, int p_hand)
{
    printf("Broker score is : %i; your score is : %i\n", g->broker, p_hand);
}

void player_jackpot(t_game *g)
{
    printf("Jackpot !\n");
    g->player->score += g->player->bet + g->bet*2;
}

void player_breakthrough(t_game *g)
{
    printf("Oops ! You broke through 21 !\n");
    g->player->score -= g->player->bet;
}

void player_lost(t_game *g)
{
    printf("Oh no the broker wins\n");
    g->player->score -= g->player->bet;
}

void player_win(t_game *g)
{
    printf("Good call ! You win\n");
    g->player->score += g->bet;
}

d_bool is_game_finished(t_game *g)
{
    return g->end;
}

void game_end(t_game *g)
{
    g->end = 1;
}
