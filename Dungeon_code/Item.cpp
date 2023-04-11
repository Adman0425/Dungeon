#include "Item.h"

Item::Item(): Object("", "item"){
}

Item::Item(string name, int hp, int attack, int def): Object(name, "item") {/*call constructor of object*/
	this -> health = hp;
	this -> attack = attack;
	this -> defense = def;
}

void Item::checklist(ofstream& out) const {
	Object::checklist(out);/*call the function that belonged to object*/
	out << health << ' ' << attack << ' ' << defense << '\n';
}

bool Item::triggerEvent(Object* obj) {/*when the item be bought by the player*/
	Player *player = dynamic_cast<Player*>(obj);
    if (player == NULL) return false;/*the player must exist*/

    (*player).addItem(*this);/*buy item from a npc*/

	return true;
}

/*all set and get functions*/
int Item::getHealth() const {
	return this -> health;
}

int Item::getAttack() const {
	return this -> attack;
}

int Item::getDefense() const {
	return this -> defense;
}

void Item::setHealth(int hp) {
	this -> health = hp;
}

void Item::setAttack(int attack) {
	this -> attack = attack;
}

void Item::setDefense(int def) {
	this -> defense = def;
}

/*overload operator out*/
ostream& operator<<(ostream& out, const Item& t) {/*would be called if the player want to check what items had*/
	out << "Item: " << t.getName() << " : ";
	out << t.getHealth() << ' ' << t.getAttack() << ' ' << t.getDefense();
	out << "  (health/attack/defense)";

	return out;
}
