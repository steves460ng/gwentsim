#include "LibGwentDrawSim.h"

void shuffle_deck(vector<string>* deck, int deck_size)
{
    srand (unsigned (time(0)));
    random_shuffle(deck->begin(), deck->end());
}

void loaddeck(char * deck_path, GWENT_TYPE * deck)
{
    char card[256] = {NULL,};
    char key[20] = {NULL,};
    int cnt = GetPrivateProfileInt("deck", "card_count", 0, deck_path);
    for (int i = 0; i < cnt; i++)
    {
        sprintf(key, "card%d", i);
        memset(card, NULL, 256);
        GetPrivateProfileString("deck", key, "", card, MAX_PATH, deck_path);
        string temp = string(card);
        deck->push_back(temp);
    }
    shuffle_deck(deck, deck->size());
}

void draw(vector<string> * deck, vector<string> * hand, int draw_cnt)
{
    for(int i = 0; i < draw_cnt; i++)
    {
        hand->push_back(deck->at(i));
        deck->erase(deck->begin() + i);
    }
}

int redraw(vector<string> * deck, vector<string> * hand)
{
    if(deck->size() == 0)
        return -1;

    if(hand->size() >= 10)
        return -1;

    hand->push_back(deck->at(0));
    deck->erase(deck->begin() + 0);

    return 0;
}

int remove_card(vector<string> * hand, int card_no)
{
    if(hand->size() <= card_no)
        return -1;

    hand->erase(hand->begin() + card_no);
    return 0;
}

int mulligan(vector<string> * deck, vector<string> * hand, int hand_no)
{
    string temp;

    if(hand->size() <= hand_no)
        return -1;

    if(deck->size() == 0)
        return -2;

    temp = hand->at(hand_no);
    hand->erase(hand->begin() + hand_no);
    hand->insert(hand->begin() + hand_no, deck->at(0));
    deck->erase(deck->begin());
    deck->push_back(temp);
    return 0;
}

