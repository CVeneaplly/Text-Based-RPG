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

float Item::GetAttackBoost()
{
	return m_incDamage;
}

float Item::GetDamageRes()
{
	return m_redDamage;
}