#include <windows.h>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

#define GWENT_TYPE vector<string>

using namespace std;

void shuffle_deck(vector<string> * deck, int deck_size);
void loaddeck(char * deck_path, vector<string> * deck);
void draw(vector<string> * deck, vector<string> * hand, int draw_cnt);
int redraw(vector<string> * deck, vector<string> * hand);
int remove_card(vector<string> * hand, int card_no);
int mulligan(vector<string> * deck, vector<string> * hand, int hand_no);
