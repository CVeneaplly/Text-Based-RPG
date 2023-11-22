#pragma once
#include "Item.h"

class Inventory
{
	friend std::ostream& operator<<(std::ostream& os, const Inventory& rInventory);
protected:
	Item* m_pHead;
	Item* m_pTail;
	const int MAX_SIZE;
	int currentSize = 0;

public:

	Inventory(const int maxSize);
	~Inventory();
	int GetMaxSize() const;
	int GetCurrentSize() const;
	void AddItem(Item* pItem);
	void Clear();
	void RemoveItem(Item* pItem);
	void SwapItem(Item* toRemove, Item* toPlace);
	bool isFull();
	float GetTotalBoost();
	float GetTotalRes();
	Item* GetHead() const;
	Item* GetTail() const;
};