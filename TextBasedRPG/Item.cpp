#include "Item.h"

// Base class functions
Item::Item(float damageInc, float damageRed) :
	m_incDamage(damageInc), m_redDamage(damageRed), m_pNext(0)
{}

void Item::SetNext(Item* pItem)
{
	m_pNext = pItem;
}

Item* Item::GetNext() const
{
	return m_pNext;
}

// Child: Shield
float Shield::GetAttackBoost()
{
	return m_incDamage;
}

float Shield::GetDamageRes()
{
	return m_redDamage;
}

//Child: Armor
float Armor::GetAttackBoost()
{
	return m_incDamage;
}

float Armor::GetDamageRes()
{
	return m_redDamage;
}

//Child: Helmet
float Helmet::GetAttackBoost()
{
	return m_incDamage;
}

float Helmet::GetDamageRes()
{
	return m_redDamage;
}

// Child: Braces
float Braces::GetAttackBoost()
{
	return m_incDamage;
}

float Braces::GetDamageRes()
{
	return m_redDamage;
}

//Child: Boots
float Boots::GetAttackBoost()
{
	return m_incDamage;
}

float Boots::GetDamageRes()
{
	return m_redDamage;
}

//Child: Sword
float Sword::GetAttackBoost()
{
	return m_incDamage;
}

float Sword::GetDamageRes()
{
	return m_redDamage;
}