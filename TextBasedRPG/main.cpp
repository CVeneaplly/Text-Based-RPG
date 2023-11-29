#include <string>
#include <fstream>

// Classes
#include "Item.h"
#include "Inventory.h"
#include "Potion.h"
#include "PotionPouch.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"

//Global
void dialogueAnim(const std::string& dialogue, int delay)
{
	for(char letter : dialogue)
	{
		std::cout << letter;
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}
	std::cout << std::endl;
}

void clearScreen() {
#ifdef _WIN32
	// For Windows
	system("cls");
#else
	// For Linux and macOS
	system("clear");
#endif
}

std::vector<std::string> AssignNarrative()
{
	std::vector<std::string> narrative;
	std::ifstream file("dialogues.txt");
	std::string line;
	

	if(file.is_open())
	{
		while(std::getline(file, line))
		{
			narrative.push_back(line);
		}
		file.close();
	}
	else
	{
		std::cerr << "Unable to open the file" << std::endl;
	}

	return narrative;
}

int main()
{
	char gameOn = 'y';
	while(gameOn == 'y')
	{
		Game* theGame = new Game();
		std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t";
		dialogueAnim("TextSouls", 400);
		std::this_thread::sleep_for(std::chrono::seconds(3));
		
		clearScreen();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		dialogueAnim("Welcome to TextSouls!\n", 50);
		
		theGame->Instructions();
		std::this_thread::sleep_for(std::chrono::seconds(3));
		
		clearScreen();
		std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t";
		dialogueAnim("Let the game begin...", 100);
		std::this_thread::sleep_for(std::chrono::seconds(3));
		
		clearScreen();
		theGame->Begin();
		std::cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t";
		std::cout << "Replay(Y/N)?: ";
		std::cin >> gameOn;
		gameOn = std::tolower(gameOn);

		while(gameOn != 'y' && gameOn != 'n')
		{
			std::cout << "Invalid input..." << std::endl;
			std::cin >> gameOn;
		}
	delete theGame;
	}
	return 0;
}

//Operator Overloading
std::ostream& operator<<(std::ostream& os, const Item& rItem)
{
	os << "Damage Boost: " << rItem.m_incDamage << std::endl;
	os << "Damage Resistance: " << rItem.m_redDamage << std::endl;

	return os;
}

std::ostream& operator<<(std::ostream& os, const Inventory& rInventory)
{

	Item* invIter = rInventory.m_pHead;
	if(rInventory.m_pHead == nullptr)
	{
		os << "There is nothing to display!" << std::endl;
	}
	else
	{
		while(invIter != nullptr)
		{
			os << *(invIter) << std::endl;
			invIter = invIter->GetNext();
		}
	}

	return os;
}

std::ostream& operator<<(std::ostream& os, const Potion& rPotion)
{
	os << "Increases health by " << rPotion.m_heal * 100 << "%." << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, const PotionPouch& rPouch)
{
	Potion* pouchIter = rPouch.m_pHead;
	if(rPouch.m_pHead == nullptr)
	{
		os << "There is nothing to display!" << std::endl;
	}
	else
	{
		while(pouchIter != nullptr)
		{
			os << *(pouchIter) << std::endl;
			pouchIter = pouchIter->GetNext();
		}
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const Player& rPlayer)
{
	os << "Health: " << rPlayer.m_health << std::endl;
	os << "Damage: " << rPlayer.m_damage << std::endl;
	os << "Inventory Items: " << rPlayer.playerInventory << std::endl;
	os << "Damage Resistance: " << rPlayer.damageResistance << std::endl;
	os << "Attack Boost: " << rPlayer.attackBoost << std::endl;
	os << rPlayer.playerInventory << std::endl;

	return os;
}