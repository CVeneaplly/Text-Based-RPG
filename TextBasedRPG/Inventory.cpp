#include "Inventory.h"

// Constructor /Destructor
Inventory::Inventory(const int maxSize = 5) :
	m_pHead(nullptr), m_pTail(nullptr), MAX_SIZE(maxSize)
{}

Inventory::~Inventory()
{
	Clear();
}

// Getter Methods
int Inventory::GetMaxSize() const
{
	return MAX_SIZE;
}

int Inventory::GetCurrentSize() const
{
	return currentSize;
}

float Inventory::GetTotalBoost()
{
	float totalBoost = 0;
	Item* invIter = m_pHead;
	if(m_pHead == nullptr)
	{
		return totalBoost;
	}
	else
	{
		while(invIter != nullptr)
		{
			totalBoost += invIter->GetAttackBoost();
			invIter = invIter->GetNext();
		}
	}
	return totalBoost;
}

float Inventory::GetTotalRes()
{
	float totalRes = 0;
	Item* invIter = m_pHead;
	if(m_pHead == nullptr)
	{
		return totalRes;
	}
	else
	{
		while(invIter != nullptr)
		{
			totalRes += invIter->GetDamageRes();
			invIter = invIter->GetNext();
		}
	}
	return totalRes;
}

bool Inventory::isFull()
{
	return MAX_SIZE == currentSize;
}

Item* Inventory::GetHead() const
{
	return m_pHead;
}

Item* Inventory::GetTail() const
{
	return m_pTail;
}

//Inventory Management
void Inventory::AddItem(Item* pItem)
{
	if(m_pHead == nullptr)
	{
		m_pHead = m_pTail = pItem;
	}
	else
	{
		m_pTail->SetNext(pItem);
		m_pTail = pItem;
	}
	currentSize++;
}

void Inventory::RemoveItem(Item* pItem)
{
	if(m_pHead == nullptr)
	{
		std::cout << "Inventory is empty" << std::endl;
	}
	else if(m_pHead == pItem)
	{
		m_pHead = m_pHead->GetNext();
		delete pItem;
		currentSize--;
	}
	else
	{
		Item* prevItem = m_pHead;
		while(prevItem != nullptr && prevItem->GetNext() != pItem)
		{
			prevItem = prevItem->GetNext();
		}
		if(prevItem != nullptr)
		{
			prevItem->SetNext(pItem->GetNext());
			delete pItem;
			currentSize--;
		}
	}
}

void Inventory::Clear()
{
	while(m_pHead != nullptr)
	{
		RemoveItem(m_pHead);
	}
	m_pTail = nullptr;
	currentSize = 0;
}

void Inventory::SwapItem(Item* toRemove, Item* toPlace)
{
	RemoveItem(toRemove);
	AddItem(toPlace);
}