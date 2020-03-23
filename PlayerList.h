#ifndef PlayerList_h
#define PlayerList_h
#include "Player.h"

const int MAX_PLAYERS = 10;
const int init_NUM = 5;

typedef struct {
	tPlayerPtr *playerArr;
	int size, count;
}tPlayerList;

void create(tPlayerList &list);
bool load(tPlayerList &list);
void display(const tPlayerList &list);
bool save(const tPlayerList &list); 
void playerScore(tPlayerList &list, int score); 
bool find(const tPlayerList &list, std::string id, int &pos);
tPlayerList rankSort(const tPlayerList &list);			
void sortByID(tPlayerList &list);
void resize(tPlayerList &list);
void free(tPlayerList &list);
int binarySearch(const tPlayerList &list, std::string id, int beg, int end);
#endif