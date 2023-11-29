#include "Person.h"

Person::Person(int health, int damage, bool isDead) :
	m_health(health), m_damage(damage), m_isDead(isDead)
{}

Person::~Person() {}

unsigned int& Person::GetHealth()
{
	return m_health;
}

bool Person::isDead() const
{
	return m_isDead;
}
