#include "PotionPouch.h"

//Constructor / Destructor
PotionPouch::PotionPouch(const int maxSize) :
	m_pHead(nullptr), m_pTail(nullptr), MAX_SIZE(maxSize)
{}

PotionPouch::~PotionPouch()
{}

// Getter Methods
int PotionPouch::GetMaxSize() const
{
	return MAX_SIZE;
}

int PotionPouch::GetCurrentSize() const
{
	return currentSize;
}

bool PotionPouch::isFull()
{
	return currentSize == MAX_SIZE;
}

Potion* PotionPouch::GetHead() const
{
	return m_pHead;
}

Potion* PotionPouch::GetTail() const
{
	return m_pTail;
}
// Pouch Management

void PotionPouch::AddPotion(Potion* pPotion)
{
	if(m_pHead == nullptr)
	{
		m_pHead = m_pTail = pPotion;
	}
	else
	{
		m_pTail->SetNext(pPotion);
		m_pTail = pPotion;
	}
	currentSize++;
}

void  PotionPouch::RemovePotion() // removes first item
{
	if(m_pHead == nullptr)
	{
		std::cout << "Nothing to remove..." << std::endl;
	}
	else
	{
		Potion* pTemp = m_pHead;
		m_pHead = m_pHead->GetNext();
		delete pTemp;
		currentSize--;
	}
}

void PotionPouch::Clear()
{
	while(m_pHead != nullptr)
	{
		RemovePotion();
	}
	m_pTail = nullptr;
	currentSize--;
}
