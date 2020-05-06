#include "player.h"

/* Initialize player */
Player* initPlayer(const char* _name, int _hp, int _strength, int _portion_count) {
		Player* newPlayer = malloc(sizeof(newPlayer));

		strcpy(newPlayer->name, _name);
		newPlayer->hp = _hp;
		newPlayer->strength = _strength;
		newPlayer->portion_count = _portion_count;

		return newPlayer;
}

/* Free resource for player */
void destroyPlayer(Player* _player) {
		free(_player);
}

/* Get NAME from PLAYER */
char* getName(Player* _player) {
		return _player->name;
}

/* Get HP from PLAYER */
int getHp(Player* _player) {
		return _player->hp;
}

/* Get STRENGTH from PLAYER */
int getStrength(Player* _player) {
		return _player->strength;
}

/* Get PORTION_COUNT from PLAYER */
int getPortionCount(Player* _player) {
		return _player->portion_count;
}

