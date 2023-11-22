#include "Player.h"

Player::Player(int health, int damage, bool isDead) :
	Person(health, damage, isDead), playerInventory(new Inventory(5)), playerPotions(new PotionPouch()),
	attackBoost(0.0f), damageResistance(0.0f), moveNarrative(AssignNarrative())
{
	UpdateStats();
}

Player::~Player()
{
	delete playerInventory;
	delete playerPotions;
}

Item* Player::FindItemByNumber(int itemNo)
{
	int iter = 1;
	Item* currentItem = playerInventory->GetHead();

	while(currentItem != nullptr)
	{
		if(iter == itemNo)
		{
			return currentItem;
		}
		currentItem = currentItem->GetNext();
		iter++;

	}

	return nullptr;
}

void Player::UpdateStats()
{
	attackBoost = playerInventory->GetTotalBoost();
	damageResistance = playerInventory->GetTotalRes();
}

void Player::Drop()
{
	int itemNo;
	std::cout << *playerInventory << std::endl;
	std::cout << "Enter any number in range 1 to " << playerInventory->GetCurrentSize() << " to drop an item: ";
	std::cin >> itemNo;
	while(itemNo > playerInventory->GetCurrentSize() && itemNo <= 0)
	{
		std::cout << "Input should range between 1 to " << playerInventory->GetCurrentSize() << std::endl;
		std::cout << "Enter any number in range 1 to " << playerInventory->GetCurrentSize() << " to drop an item: ";
		std::cin >> itemNo;
	}
	Item* itemDrop = FindItemByNumber(itemNo);
	playerInventory->RemoveItem(itemDrop);
	std::cout << "\n";
}

void Player::PickUp(Item* itemToPick)
{
	char pickChoice;

	// checking if there's enough space to AddItem
	if(!(playerInventory->isFull()))
	{
		std::cout << "You found a new item. Pick it up? (Y/N): ";
		std::cin >> pickChoice;
		pickChoice = std::tolower(pickChoice);
		while(pickChoice != 'y' && pickChoice != 'n')
		{
			std::cout << "Please make a valid choice...(Y or N): ";
			std::cin >> pickChoice;
			pickChoice = std::tolower(pickChoice);
		}
		if(pickChoice == 'y')
		{
			playerInventory->AddItem(itemToPick);
			UpdateStats();
			std::cout << "Item has been picked up." << std::endl;
		}
		else
		{
			delete itemToPick;
		}
	}
	// if there's no enough space, swap item with an item from the inventory.
	else
	{
		std::cout << "You found an item, but inventory is full.\nSwap with one of the items in the inventory? (Y/N): ";
		std::cin >> pickChoice;
		pickChoice = std::tolower(pickChoice);
		while(pickChoice != 'y' && pickChoice != 'n')
		{
			std::cout << "Please make a valid choice...(Y or N): ";
			std::cin >> pickChoice;
			pickChoice = std::tolower(pickChoice);
		}
		if(pickChoice == 'y') {
			int itemNo;
			std::cout << *playerInventory << std::endl;
			std::cout << "Enter any number in range 1 to " << playerInventory->GetCurrentSize() << " to choose an item to swap: ";

			while(!(std::cin >> itemNo) || itemNo > playerInventory->GetCurrentSize() || itemNo <= 0) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input. Please enter a number in range 1 to " << playerInventory->GetCurrentSize() << ": ";
			}

			Item* itemDrop = FindItemByNumber(itemNo);
			playerInventory->SwapItem(itemDrop, itemToPick);
			std::cout << "Item has been picked up." << std::endl;
			UpdateStats();
		}
		else {
			delete itemToPick;
		}
	}
}

void Player::PickPotion(Potion* potionToPick)
{
	char pickChoice;

	// checking if there's enough space to AddItem
	if(!(playerPotions->isFull()))
	{
		std::cout << "You found a new potion. Pick it up? (Y/N): ";
		std::cin >> pickChoice;
		pickChoice = std::tolower(pickChoice);
		while(pickChoice != 'y' && pickChoice != 'n')
		{
			std::cout << "Please make a valid choice...(Y or N): \n";
			std::cin >> pickChoice;
			pickChoice = std::tolower(pickChoice);
		}
		if(pickChoice == 'y')
		{
			playerPotions->AddPotion(potionToPick);
			std::cout << "Potion has been picked up." << std::endl;
		}
		else
		{
			delete potionToPick;
		}
	}
	// if there's no enough space, swap item with an item from the inventory.
	else
	{
		std::cout << "Inventroy is full" << std::endl;
		delete potionToPick;
	}
}

void Player::SetForceQuit()
{

	clearScreen();

	char choice;
	std::cout << "Do you want to quit? (Y/N):";
	std::cin >> choice;
	choice = std::tolower(choice);
	if(choice == 'y')
	{
		this->forceQuit = true;
	}
	else if(choice == 'n')
	{
	}
	else
	{
		while(choice != 'y' && choice != 'n')
		{
			std::cout << "Enter a valid input\n";
			std::cin >> choice;
		}
	}
}

bool Player::IsForceQuit() const
{
	return forceQuit;
}

char Player::AskMoveInput()
{
	char move;
	std::cout << "Which direction do you want to move in?" << std::endl;
	std::cout << "Press 'W' to move North\nPress 'S' to move South\nPress 'A' to move West\nPress 'D' to move East" << std::endl;
	std::cout << "You can also:\nR - To drop an item\nH - To heal\nI - To lookup Inventory\nQ - Quit Game" << std::endl;
	std::cout << "Your Input: ";
	std::cin >> move;
	move = std::tolower(move);

	return move;
}

void Player::Move()
{
	char move = AskMoveInput();

	if(move == 'w' || move == 's' || move == 'a' || move == 'd')
	{
		std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
		std::shuffle(std::begin(moveNarrative), std::end(moveNarrative), rng);
		std::string dialogue = moveNarrative[0];
		clearScreen();
		std::this_thread::sleep_for(std::chrono::seconds(2));
		dialogueAnim(dialogue, 70);
		std::this_thread::sleep_for(std::chrono::seconds(4));
		std::cout << "\n";
	}
	else if(move == 'q')
	{
		SetForceQuit();
		if(forceQuit == false)
		{
			Move();
		}
	}
	else if(move == 'r')
	{
		if(playerInventory->GetCurrentSize() == 0)
		{
			std::cout << "Empty Inventory...\n" << std::endl;
			Move();
		}
		else
		{
			Drop();
			Move();
		}
	}
	else if(move == 'h')
	{
		Heal();
		std::cout << "\n";
		Move();
	}
	else if(move == 'i')
	{
		std::cout << *playerInventory;
		std::cout << "\n";
		Move();
	}
	else
	{
		std::cout << "Invalid Input...\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		clearScreen();
		Move();
	}
}

void Player::Heal()
{
	if(playerPotions->GetCurrentSize() > 0)
	{
		unsigned int& playerHealth = GetHealth();
		if(playerHealth <= 75 && playerHealth >= 1)
		{
			playerHealth += 25;
			std::cout << "Health increased by 25 points\n";
			playerPotions->RemovePotion();
		}
		else if(playerHealth > 75 and playerHealth < 100)
		{
			std::cout << "Health increased by " << 100 - playerHealth << " points\n";
			playerHealth = 100;
			playerPotions->RemovePotion();
		}
		else
		{
			std::cout << "Health is already full." << std::endl;
		}
	}
	else
	{
		std::cout << "No potions available\n";
	}

}

unsigned int Player::DealDamage()
{
	float damage = static_cast<float>(m_damage);
	if(attackBoost > 0)
	{
		damage += attackBoost * damage;
	}
	return static_cast<unsigned int>(damage);
}

void Player::ReceiveDamage(Person* opponent)
{
	unsigned int& health = GetHealth();
	float oppDamage = static_cast<float>(opponent->DealDamage());

	if(damageResistance > 0)
	{
		oppDamage -= oppDamage * damageResistance;
		if(health > oppDamage)
		{
			health -= static_cast<unsigned int>(oppDamage);
			std::cout << "Enemy has dealt a damage of " << oppDamage << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
		else
		{
			health = 0;
			std::cout << "Enemy has dealt a damage of " << oppDamage << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));
			m_isDead = true;
		}
	}
	else
	{
		if(health > oppDamage)
		{
			health -= static_cast<unsigned int>(oppDamage);
			std::cout << "Enemy has dealt a damage of " << oppDamage << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
		else
		{
			health = 0;
			std::cout << "Enemy has dealt a damage of " << oppDamage << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));
			m_isDead = true;
		}
	}
}

void Player::Dead()
{
	clearScreen();
	std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t";
	dialogueAnim("You have been killed...", 400);
}
