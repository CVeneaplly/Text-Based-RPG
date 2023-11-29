#pragma once

#include <iostream>

// Base
class Item
{
	friend std::ostream& operator<<(std::ostream& os, const Item& rItem);

protected:
	float m_incDamage; // increases damage dealt by a some percentage of the original damage i.e., damage += damage * incDamage
	float m_redDamage; // decereases damage taken
	Item* m_pNext;

public:
	Item(float damageInc = 0.0, float damageRed = 0.0);
	void SetNext(Item* pItem);
	float GetDamageRes();
	float GetAttackBoost();
	Item* GetNext() const;

};

// Shield
class Shield : public Item
{
public:
	Shield(float damageInc = 0.0, float damageRed = 0.08) : Item(damageInc, damageRed) {};
};

//Armor
class Armor : public Item
{
public:
	Armor(float damageInc = 0.0, float damageRed = 0.05) : Item(damageInc, damageRed) {};
};

//Helmet
class Helmet : public Item
{
public:
	Helmet(float damageInc = 0.0, float damageRed = 0.03) : Item(damageInc, damageRed) {};
};

//Braces
class Braces : public Item
{
public:
	Braces(float damageInc = 0.04, float damageRed = 0.02) : Item(damageInc, damageRed) {};
};

//Boots
class Boots : public Item
{
public:
	Boots(float damageInc = 0.03, float damageRed = 0.02) : Item(damageInc, damageRed) {};
};

//Sword
class Sword : public Item
{
public:
	Sword(float damageInc = 0.08, float damageRed = 0.0) : Item(damageInc, damageRed) {}
};