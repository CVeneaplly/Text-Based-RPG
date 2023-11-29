#include "Enemy.h"

Enemy::Enemy(int health, int damage, bool isDead) :
	Person(health, damage, isDead)
{}

Enemy::~Enemy()
{}

unsigned int Enemy::DealDamage()
{
	return m_damage;
}

void Enemy::ReceiveDamage(Person* opponent)
{

	unsigned int oppDamage = opponent->DealDamage();
	unsigned int& rHealth = GetHealth();
	
	if(rHealth > oppDamage)
	{
		rHealth = rHealth - oppDamage;
		std::cout << "You dealt a damage of " << oppDamage << "\n";
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	else
	{
		rHealth = 0;
		m_isDead = true;
		std::cout << "You dealt a damage of " << oppDamage << "\n";
		std::this_thread::sleep_for(std::chrono::seconds(2));
		Dead();
	}
}

void Enemy::Dead()
{
	std::cout << "The enemy has been defeated." << std::endl;
}