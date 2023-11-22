#pragma once
#include <iostream>
#include <thread>
#include <chrono>

// Person
class Person
{
protected:
	unsigned int m_damage;
	unsigned int m_health;
	bool m_isDead;

public:
	Person(int health = 100, int damage = 20, bool isDead = false);
	~Person();

	unsigned int& GetHealth();
	bool isDead() const;

	virtual unsigned int DealDamage() = 0;
	virtual void ReceiveDamage(Person* opponent) = 0;
	virtual void Dead() = 0;
};