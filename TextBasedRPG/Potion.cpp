#include "Potion.h"

// constructor
Potion::Potion() : m_pNext(nullptr) {}

// Getter
unsigned int Potion::GetHeal()
{
	return m_heal;
}

Potion* Potion::GetNext() const
{
	return m_pNext;
}

// Setter
void Potion::SetNext(Potion* pPotion)
{
	m_pNext = pPotion;
}