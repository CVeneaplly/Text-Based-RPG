#include "Game.h"

Game::Game()
{}

Game::~Game()
{
	delete myPlayer;
}

int Game::GenerateRandom(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	int random = dis(gen);

	return random;
}

void Game::SpawnAndFight()
{
	Enemy* newEnemy = new Enemy();

	char choice;
	int fightProb = GenerateRandom(1, 3);

	dialogueAnim("You have encountered an enemy...", 30);

	std::cout << "Fight him? (Y/N): ";
	std::cin >> choice;
	choice = std::tolower(choice);
	while(choice != 'y' && choice != 'n')
	{
		std::cout << "Invalid input...\n";
		std::cin >> choice;
	}
	if(choice == 'n')
	{
		if(fightProb == 1)
		{
			std::cout << "You fled.." << std::endl;
			delete newEnemy;
		}
		else
		{
			std::cout << "Enemy: ";
			dialogueAnim("You cannot avoid this fight. BWAHAHAHA!!!!\n", 20);
			Battle(myPlayer, newEnemy);
			delete newEnemy;
		}
	}
	else
	{
		Battle(myPlayer, newEnemy);
		delete newEnemy;
	}
}

void Game::SpawnItem()
{
	int spawnNum = GenerateRandom(1, 6);
	Item* newItem = nullptr;
	switch(spawnNum)
	{
		case 1:
			newItem = new Shield();
			break;
		case 2:
			newItem = new Sword();
			break;
		case 3:
			newItem = new Armor();
			break;
		case 4:
			newItem = new Boots();
			break;
		case 5:
			newItem = new Braces();
			break;
		case 6:
			newItem = new Helmet();
			break;
	}
	if(newItem == nullptr)
	{
		std::cout << "Nothing to pick up" << std::endl;
	}
	else
	{
		myPlayer->PickUp(newItem);
	}

}

void Game::SpawnPotion()
{
	Potion* newPotion = new Potion();
	myPlayer->PickPotion(newPotion);
}

void Game::DisplayHealths(Player* pPlayer, Enemy* pEnemy)
{
	clearScreen();
	std::cout << "Player\t\t\t\tEnemy\n";
	std::cout << "Health: " << pPlayer->GetHealth() << "\t\t\t" << "Health: " << pEnemy->GetHealth() << std::endl;

}

void Game::Instructions()
{
	std::string instructions = "The game is simple. Select a move you want to make by pressing the inputs displayed.\n\nThe inputs(Will be displayed again in the game):\n\n"
		"During Narrative:\nW - Move North\nS - Move South\nA - Move East\nD - Move West \nR - Manage Inventory\nH - Heal\n\n"
		"During Battle:\nE - To attack\nH - To Heal\n\nYou can press 'q' to quit at any time\n";
	dialogueAnim(instructions, 20);
}

void Game::Battle(Player* pPlayer, Enemy* pEnemy)
{
	
	while(pEnemy->GetHealth() != 0 && pPlayer->GetHealth() != 0 && !(pPlayer->IsForceQuit()))
	{
		DisplayHealths(pPlayer, pEnemy);
		// player's move
		char move;
		std::cout << "\nControls: \nE - To attack\nH - To Heal\n\nYou press 'q' to quit at any time\n";
		std::cout << "\nYour move?: ";
		std::cin >> move;
		move = std::tolower(move);
		while(move != 'e' && move != 'h' && move != 'q')
		{
			std::cout << "Invalid move..." << std::endl;
			std::cin >> move;
		}
		if(move == 'e')
		{
			pEnemy->ReceiveDamage(pPlayer);
			DisplayHealths(pPlayer, pEnemy);
			if(pEnemy->isDead())
			{
				std::this_thread::sleep_for(std::chrono::seconds(2));
				pEnemy->Dead();
				break;
			}
		}
		else if(move == 'q')
		{
			pPlayer->SetForceQuit();
			if(!(pPlayer->IsForceQuit()))
				continue;
			else
				break;
		}
		else if(move == 'h')
		{
			pPlayer->Heal();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		DisplayHealths(pPlayer, pEnemy);

		// enemy's move
		pPlayer->ReceiveDamage(pEnemy);
		DisplayHealths(pPlayer, pEnemy);
		if(pPlayer->isDead())
		{
			std::this_thread::sleep_for(std::chrono::seconds(2));
			pPlayer->Dead();
			break;
		}

		clearScreen();
	}
}

void Game::Begin()
{
	while(!(myPlayer->isDead()) && !(myPlayer->IsForceQuit()))
	{
		myPlayer->Move();
		int random = GenerateRandom(1, 12);

		if(myPlayer->IsForceQuit())
		{
			break;
		}
		else
		{
			switch(random)
			{
				case 1:
				case 2:
				case 3:
					SpawnAndFight(); // spawns enemy. Player and enemy might end up killing each other.
					clearScreen();
					break;
				case 4:
				case 5:
					SpawnItem();
					std::this_thread::sleep_for(std::chrono::seconds(2));
					clearScreen();
					break;
				case 6:
				case 7:
					SpawnPotion();
					std::this_thread::sleep_for(std::chrono::seconds(2));
					clearScreen();
					break;
				case 8:
					SpawnAndFight();
					if(myPlayer->isDead())
						break;
					SpawnItem();
					std::this_thread::sleep_for(std::chrono::seconds(2));
					clearScreen();
					break;
				case 9:
					SpawnAndFight();
					if(myPlayer->isDead())
						break;
					SpawnPotion();
					std::this_thread::sleep_for(std::chrono::seconds(2));
					clearScreen();
					break;
				default:
					clearScreen();
					std::this_thread::sleep_for(std::chrono::seconds(3));
					dialogueAnim("A new path awaits...", 60);
					std::this_thread::sleep_for(std::chrono::seconds(3));
					clearScreen();
					break;
			}
		}

	}
}
