#pragma once

#include "Person.h"
#include "Inventory.h"
#include "PotionPouch.h"

#include <vector>
#include <random>

// extern functions
extern void clearScreen();
extern void dialogueAnim(const std::string& dialogue, int delay = 40);
extern std::vector<std::string> AssignNarrative();

//Player
class Player : public Person
{

	friend std::ostream& operator<<(std::ostream& os, const Player& rPLayer);

private:

	// Private members
	Inventory* playerInventory;
	PotionPouch* playerPotions;
	float attackBoost;
	float damageResistance;
	std::vector<std::string> moveNarrative;
	bool forceQuit = false;

	// Private Methods
	Item* FindItemByNumber(int itemNo);
	char AskMoveInput();
	void UpdateStats();

public:

	// Constructor / Destructor
	Player(int health = 100, int damage = 20, bool isDead = false);
	~Player();

	// player exclusive functions
	void PickUp(Item* itemToPick);
	void PickPotion(Potion* potionToPick);
	void Move();
	void Heal();
	void Drop();
	void SetForceQuit();
	bool IsForceQuit() const;

	// inherited functions
	virtual unsigned int DealDamage();
	virtual void ReceiveDamage(Person* opponent);
	virtual void Dead();

};