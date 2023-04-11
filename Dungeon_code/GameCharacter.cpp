#include "GameCharacter.h"

GameCharacter::GameCharacter() {

}

GameCharacter::GameCharacter(string name, string tag, int hp, int attack, int def): Object(name, tag) {/*call constructor of object*/
	this -> name = name;

	this -> maxHealth = hp;
	this -> currentHealth = hp;
	this -> attack = attack;
	this -> defense = def;
}

bool GameCharacter::checkIsDead() {/*if hp is lower than 0 then recognize that character is dead*/
	return (this -> currentHealth <= 0);
}

int GameCharacter::takeDamage(int t) {/*calculate the damage on randomly, note that t would be attack*/
	float def = rand() / RAND_MAX;
	int damageCause = min(max(rand() % 5, t - getDefense() + (int)(def * getDefense() * 0.25)), getCurrentHealth());/*get the max damage and compare it to hp, if it is bigger than hp, then print damage be hp*/
	this -> currentHealth -= damageCause;/*minus damage from hp*/
	return damageCause;
}
/*all set and get function*/
void GameCharacter::setMaxHealth(int hp) {
	this -> maxHealth = hp;
}

void GameCharacter::setCurrentHealth(int hp) {
	this -> currentHealth = min(hp, this -> maxHealth);
}

void GameCharacter::setAttack(int attack) {
	this -> attack = attack;
}

void GameCharacter::setDefense(int def) {
	this -> defense = def;
}

int GameCharacter::getMaxHealth() const {
	return this -> maxHealth;
}

int GameCharacter::getCurrentHealth() const {
	return this -> currentHealth;
}

int GameCharacter::getAttack() const {
	return this -> attack;
}

int GameCharacter::getDefense() const {
	return this -> defense;
}
