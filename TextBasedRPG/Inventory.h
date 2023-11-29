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
	
	// getter
	int GetMaxSize() const;
	int GetCurrentSize() const;
	float GetTotalBoost();
	float GetTotalRes();
	bool isFull();
	
	Item* GetHead() const;
	Item* GetTail() const;

	// inventory management
	void AddItem(Item* pItem);
	void Clear();
	void RemoveItem(Item* pItem);
	void SwapItem(Item* toRemove, Item* toPlace);

};