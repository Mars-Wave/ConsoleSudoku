#ifndef Player_h
#define Player_h
#include <string>

typedef struct {
	std::string ID;
	int points;
}tPlayer;

typedef tPlayer *tPlayerPtr;

std::string toString(const tPlayer &player);
void modifyPlayer(tPlayer & player, int score);
bool smaller(const tPlayer &p1, const tPlayer &p2);
bool operator<(const tPlayer &opLeft, const tPlayer &opRight);
#endif