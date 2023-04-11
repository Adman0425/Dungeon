#include "NPC.h"

NPC::NPC(): GameCharacter("", "npc", 1, 1, 1){
}

NPC::NPC(string name, string scr, vector<Item> v): GameCharacter(name, "npc", 1, 1, 1) {/*call the constructor of gamecharacter*/
	this -> script = scr;/*to prevent npc be regarded as dead*/
	this -> commodity = v;
}

NPC::NPC(const NPC* now) {
	this -> setName(now -> getName());
    this -> setTag(now -> getTag());
    this -> setMaxHealth(now -> getMaxHealth());
    this -> setCurrentHealth(now -> getCurrentHealth());
    this -> setAttack(now -> getAttack());
    this -> setDefense(now -> getDefense());
    this -> setCommodity(now -> getCommodity());
}

void NPC::listCommodity() {/*print all items that can be bought*/
	cout << getScript() << endl;
	cout << "Here are " << commodity.size() << " kinds for you to choose. Maybe one of them can let you know the secret of this journey.\n\n";

	for (auto i : commodity) {
		cout << i.getName() << endl;/*print the items to choose*/
	}
	cout << endl;
}

bool NPC::triggerEvent(Object* obj) {/*to handle buy items from npc*/
	Player* player = dynamic_cast<Player*>(obj);
	if (player == NULL) return false;/*the player must exist*/

	cout << "Choose the one that you pursued but remember you can only get one thing: ";
	string name;
	cin >> name;

	vector<Item> tmp;
	tmp.clear();/*ensure*/
	bool ok = false;/*set bool to false*/
	for (auto i : commodity) {
		if (i.getName() == name) {
			player -> addItem(i);/*call additem to let player buy that item*/
			cout << "You have " << name << " now.\n";
			ok = 1;/*set bool to true*/
			continue;
		}
		tmp.push_back(i);/*let the item into the player's bag*/
	}
	if (ok) {/*buy item successfully*/
		this -> setCommodity(tmp);
		return (this -> commodity.size() == 0);/*check if the npc has no more items to sell*/
	}

	cout << "You should check your wish carefully.\n";
	return false;
}

/*all set and get functions*/
void NPC::setScript(string src) {
	this -> script = src;
}

void NPC::setCommodity(vector<Item> v) {
	this -> commodity = v;
}

string NPC::getScript() const {
	return this -> script;
}

vector<Item> NPC::getCommodity() const {
	return this -> commodity;
}


void NPC::checklist(ofstream& out) const {
	Object::checklist(out);/*call the function that belonged to object*/
	out << script << '\n' << commodity.size() << '\n';
	for (auto i : commodity) {
		cout << "    ";
		i.checklist(out);
	}
}

ostream& operator<<(ostream& out, const NPC& npc) {/*overload operator out*/
	out << "NPC: " << npc.getName();
	return out;
}

