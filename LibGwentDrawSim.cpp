#include "LibGwentDrawSim.h"

static int player = 0;
static int config_line = 0;
static int config_slot = 0;

static vector<string> deck[2];
static vector<string> hand[2];
static vector<string> grave[2];
static vector< vector<string> > field[2];

int gwent_set_player(int player_no)
{
	player = player_no;
	return player;
}

void gwent_clear_all()
{
	for (int i = 0; i < 2; i++)
	{
		deck[i].clear();
		hand[i].clear();
		grave[i].clear();
	}
}

int gwent_set_game(int line_cnt, int slot_cnt)
{
	config_line = line_cnt;
	config_slot = slot_cnt;
	return 0;
}

vector<string> gwent_get_hand()
{
	return hand[player];
}
vector<string> gwent_get_deck()
{
	return deck[player];
}
vector<string> gwent_get_grave()
{
	return grave[player];
}


vector<string> gwent_shuffle_deck()
{
    srand (unsigned (time(0)));
    random_shuffle(deck[player].begin(), deck[player].end());
	return deck[player];
}

vector<string> gwent_loaddeck(char * deck_path)
{
    char card[256] = {'\0',};
    char key[20] = {'\0',};
    int cnt = GetPrivateProfileInt("deck", "card_count", 0, deck_path);
    for (int i = 0; i < cnt; i++)
    {
        sprintf(key, "card%d", i);
        memset(card, '\0', 256);
        GetPrivateProfileString("deck", key, "", card, MAX_PATH, deck_path);
        string temp = string(card);
        deck[player].push_back(temp);
    }
    gwent_shuffle_deck();
	return deck[player];
}

vector<string> gwent_draw(int draw_cnt)
{
    for(int i = 0; i < draw_cnt; i++)
    {
        hand[player].push_back(deck[player].at(i));
        deck[player].erase(deck[player].begin() + i);
    }
	return deck[player];
}

vector<string> gwent_redraw()
{
	vector<string> empty_vec;
    if(deck[player].size() == 0)
        return empty_vec;

    if(hand[player].size() >= 10)
        return empty_vec;

    hand[player].push_back(deck[player].at(0));
    deck[player].erase(deck[player].begin() + 0);

    return hand[player];
}

vector<string> gwent_hand_to_grave(int card_no)
{
	vector<string> empty_vec;
    if(hand[player].size() <= card_no)
        return empty_vec;
	
	grave[player].push_back(hand[player].at(card_no));
    hand[player].erase(hand[player].begin() + card_no);
    return hand[player];
}

vector<string> gwent_mulligan(int hand_no)
{
    string temp;
	vector<string> empty_vec;
    if(hand->size() <= hand_no)
        return empty_vec;

    if(deck->size() == 0)
        return empty_vec;

    temp = hand[player].at(hand_no);
    hand[player].erase(hand[player].begin() + hand_no);
    hand[player].insert(hand[player].begin() + hand_no, deck[player].at(0));
    deck[player].erase(deck[player].begin());
    deck[player].push_back(temp);
    return hand[player];
}

