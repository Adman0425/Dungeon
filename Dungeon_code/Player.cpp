#include "Player.h"

#include <iostream>
using namespace std;

Player::Player() {
}

Player::Player(string name, int hp, int attack, int de): GameCharacter(name, "pl", hp, attack, de) {/*call constructor of game character*/
	this -> currentRoom = NULL;
	this -> previousRoom = NULL;
	this -> whetherWin = false;
}

void Player::addItem(Item it) {
	this -> increaseStates(it.getHealth(), it.getAttack(), it.getDefense());/*plus the state separately*/
	this -> inventory.push_back(it);/*let item into player's bag*/
}

void Player::increaseStates(int hp, int attack, int def) {/*how to plus the state*/
	this -> setCurrentHealth(min(getCurrentHealth() + hp, getMaxHealth()));/*if the state is larger than the initial hp, then print initial hp*/
	this -> setAttack(getAttack() + attack);
	this -> setDefense(getDefense() + def);
}

bool Player::triggerEvent(Object* obj) {
	return false;
}

void Player::setPreviousRoom(Room* rom) {
	this -> previousRoom = rom;
}

void Player::setCurrentRoom(Room* now) {
	this -> setPreviousRoom(this -> currentRoom);
	this -> currentRoom = now;
}

void Player::setInventory(vector<Item> v) {/*deal with the items*/
	for (auto i : v) {
		i.triggerEvent(this);
	}
	this -> inventory = v;
}

Room* Player::getCurrentRoom() const {
	return this -> currentRoom;
}

Room* Player::getPreviousRoom() const {
	return this -> previousRoom;
}

vector<Item> Player::getInventory() const {
	return this -> inventory;
}

void Player::setwhetherWin(bool b) {
	this -> whetherWin = b;
}

bool Player::getwhetherWin() const {
	return this -> whetherWin;
}

ostream& operator<<(ostream& out, const Player& p) {/*overload operator*/
    cout << p.getName() << "'s Status:\n";
    out << "HP: " << p.getCurrentHealth() << '/' << p.getMaxHealth() << '\n' << "Attack: " << p.getAttack() << '\n' << "Defense: " << p.getDefense();

    return out;
}
