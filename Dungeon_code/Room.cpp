#include "Room.h"

Room::Room() {/*default constructor*/
	isExit = false;
	upRoom = downRoom = leftRoom = rightRoom = NULL;
	objects.clear();
	index = -1;
}

Room::Room(bool isExit, int index, vector<Object*> v) {
	upRoom = downRoom = leftRoom = rightRoom = NULL;
	this -> isExit = isExit;
	this -> index = index;
	this -> objects = v;
}

bool Room::popObject(Object* obj) {/*pop out the specific object, used when the interaction is done*/
	bool ok = false;
	vector<Object*> tmp;
	tmp.clear();/*ensure*/
	for (auto i : objects) {
		if (obj == i) {
			ok = true;
			continue;
		}
		tmp.push_back(i);/*let i be recorded in the tmp*/
	}
	this -> setObjects(tmp);

	return ok;
}

void Room::pushObject(Object* obj) {
	(this -> objects).push_back(obj);
}

void Room::setUpRoom(Room* now) {
	this -> upRoom = now;
}

void Room::setDownRoom(Room* now) {
	this -> downRoom = now;
}

void Room::setLeftRoom(Room* now) {
	this -> leftRoom = now;
}

void Room::setRightRoom(Room* now) {
	this -> rightRoom = now;
}

void Room::setIsExit(bool bl) {
	this -> isExit = bl;
}

void Room::setIndex(int index) {
	this -> index = index;
}

void Room::setObjects(vector<Object*> v) {
	this -> objects = v;
}

bool Room::getIsExit() const {
	return this -> isExit;
}

int Room::getIndex() const {
	return this -> index;
}

vector<Object*> Room::getObjects() const {
	return this -> objects;
}

Room* Room::getUpRoom() const {
	return this -> upRoom;
}

Room* Room::getDownRoom() const {
	return this -> downRoom;
}

Room* Room::getLeftRoom() const {
	return this -> leftRoom;
}

Room* Room::getRightRoom() const {
	return this -> rightRoom;
}

void Room::listAttack() const {/*print all the monsters in this room*/
	bool ok = false;
	for (auto i : objects) {
		Monster* monptr = dynamic_cast<Monster*>(i);/*object turns into monster*/

		if (monptr != NULL) {/*there still is monster*/
			ok = 1;
			cout << *monptr << '\n';/*output their name*/
		}
	}
	if (!ok) cout << "There seems peace and no enemies.\n";
}

void Room::listNPC() const {/*print all the npcs in this room*/
	bool ok = false;
	for (auto i : objects) {
		NPC* npcptr = dynamic_cast<NPC*>(i);/*object turns into npc*/

		if (npcptr != NULL) {/*there still is npc*/
			ok = 1;
			cout << *npcptr << '\n';/*output their name*/
		}
	}
	if (!ok) cout << "Here is absolutely silent and no one here.\n";
}

ostream& operator<<(ostream& out, const Room& rom) {/*overload operator*/
	out << "Room state:\n";
	if (rom.getIsExit()) out << "You notice a beam of light...\n";/*note here is exit and boss*/

	vector<Object*> v = rom.getObjects();
	if (v.size())/*there still is object*/
		for (auto i : v) {
			Monster* monptr = dynamic_cast<Monster*>(i);/*remember to change their type*/
			NPC* npcptr = dynamic_cast<NPC*>(i);
			Item* itmptr = dynamic_cast<Item*>(i);

			if (monptr != NULL) out << *monptr << '\n';/*output all*/
			if (npcptr != NULL) out << *npcptr << '\n';
			if (itmptr != NULL) out << *itmptr << '\n';
		}
	else
		out << "The room is too empty to make any normal person stay.";

	return out;
}
