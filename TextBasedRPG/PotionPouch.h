#pragma once
#include "Potion.h"

class PotionPouch
{
	// friend
	friend std::ostream& operator<<(std::ostream& os, const PotionPouch& rPouch);

protected:
	Potion* m_pHead;
	Potion* m_pTail;
	int currentSize = 0;
	const int MAX_SIZE;

public:
	// constructor / destructor
	PotionPouch(const int maxSize = 5);
	~PotionPouch();

	// Getter
	int GetMaxSize() const;
	int GetCurrentSize() const;
	bool isFull();
	Potion* GetHead() const;
	Potion* GetTail() const;

	// Pouch Management
	void AddPotion(Potion* pPotion);
	void Clear();
	void RemovePotion();
};