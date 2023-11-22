#pragma once
#include <random>

# include "Player.h"
#include "Enemy.h"

// Game
class Game
{
private:
	Player* myPlayer = new Player(100, 20, false);
	
	int GenerateRandom(int min, int max);
	void SpawnAndFight();
	void SpawnItem();
	void SpawnPotion();
	void DisplayHealths(Player* pPlayer, Enemy* pEnemy);

public:
	Game();
	~Game();

	void Instructions();
	void Begin();
	void Battle(Player* pPlayer, Enemy* pEnemy);
};