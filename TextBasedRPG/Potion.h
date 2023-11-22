#pragma once
# include <iostream>

class Potion
{
	friend std::ostream& operator<<(std::ostream& os, const Potion& rPotion);

protected:
	unsigned int m_heal = 25;
	Potion* m_pNext;

public:
	Potion();
	unsigned int GetHeal();
	void SetNext(Potion* pPotion);
	Potion* GetNext() const;
};