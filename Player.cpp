#include <string>
#include "Player.h"
#include "checkML.h"
using namespace std;


string toString(const tPlayer &player){
	string aux = "", aux2 = to_string(player.points);
	aux += player.ID;
	for (int i = 0; i < 15 - player.ID.size() - aux2.size(); i++)
	{
		aux += " ";
	}
	aux += aux2;
	return aux;
}

void modifyPlayer(tPlayer & player, int score){
	player.points += score;
}

bool smaller(const tPlayer &p1, const tPlayer &p2){
	bool aux = false;
	if (p1.points <= p2.points) {
		if (p1.points==p2.points)
		{
			if (p1<p2)
			{
				aux = true;
			}
		}
		else {
			aux = true;
		}
	}
	return aux;
}

bool operator<(const tPlayer &opLeft, const tPlayer &opRight) {
	return opLeft.ID > opRight.ID;  //string comparison compliance with system
}