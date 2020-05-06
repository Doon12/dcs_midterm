#ifndef _PLAYER_HEADER
#define _PLAYER_HEADER

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define	MSG_NAME	0
#define	MSG_HP	1
#define	MSG_STRENGTH	2
#define	MSG_PORTION_COUNT	3
#define	MSG_TERMINATE	4

typedef struct Player
{
	int64_t id;
	char name[20];
	int hp; /* health power. zero to hundred */
	int strength; /* attack power */
	int portion_count; /* number of portion. 30 hp for one portion. */
} Player;

Player* initPlayer(const char* _name, int _hp, int _strength, int _portion_count);
void destroyPlayer(Player* _player);
char* getName(Player* _player);
int getHp(Player* _player);
int getStrength(Player* _player);
int getPortionCount(Player* _player);

#endif
