#include <windows.h>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

#define GWENT_TYPE vector<string>

using namespace std;

// game setup 
int gwent_set_game(int line_cnt, int slot_cnt);

// set player 1 or player 2
int gwent_set_player(int player_no);

// Card on field
int gwent_set_field(vector<string> card, int line_no, int slot_no);

// deck, grave, hand, field clear
void gwent_clear_all();

// get objects 
vector< vector<string> > gwent_get_field();
vector<string> gwent_pop_field();

vector<string> gwent_get_hand();
vector<string> gwent_get_deck();
vector<string> gwent_get_grave();

// return deck
vector<string> gwent_loaddeck(char * deck_path);

// return deck
vector<string> gwent_shuffle_deck();

// return hand
vector<string> gwent_draw(int draw_cnt);

// return hand
vector<string> gwent_redraw();

/* *************************
	Src		->	Dist
	deck		deck
	hand		hand
	grave		grave
	field		field
************************** */
// hand -> grave 
vector<string> gwent_hand_to_grave(int card_no);

// return hand
vector<string> gwent_mulligan(int hand_no);
