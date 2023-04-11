#include "Record.h"
#include <unistd.h>  /*library to sleep*/

Record::Record() {
}

void Record::loadFromFile(string& name, Player* now, vector<Room>& v) {/*open file and prepare to read it*/
	std::ifstream file_in;

	cout << "Tracing your step...\n";
	file_in.open(name + "_map.txt");
	loadRooms(v, file_in);/*read map*/
	file_in.close();/*close the file*/
	sleep(1);

	cout << "Prepared.\n";


	cout << "Checking your soul...\n";

	file_in.open(name + "_player.txt");
	loadPlayer(now, file_in, v);/*get information of player*/
	file_in.close();/*close the file*/
	sleep(1);

	cout << "Prepared.\n";
}


void Record::saveToFile(Player* now, vector<Room>& v) {/*save all records.*/
	string name = (*now).getName();/*the player's name*/
	std::ofstream out;

	out.open(name + "_map.txt");/*open a new file or it might have existed*/
	this -> saveRooms(v, out);/*write the rooms' information*/
	out.close();

	out.open(name + "_player.txt");/*open a new file or it might have existed*/
	this -> savePlayer(now, out);/*write the player's state and items*/
	out.close();

	cout << "\nRecord saved.\n";
}

bool Record::checkFile(string name) {/*function just to check file to prevent it has any wrong*/
	std::ifstream file_in;

	string file_name = name + "_player.txt";
	file_in.open(file_name);
	if (!file_in.good()) return false;/*for sure it can be opened*/
	file_in.close();

	file_name = name + "_map.txt";
	file_in.open(file_name);
	if (!file_in.good()) return false;/*for sure it can be opened*/
	file_in.close();

	return true;
}

void Record::savePlayer(Player* now, ofstream& out) {/*save the player's record*/
	now -> checklist(out);/*give a place to write the record*/

	out << now -> getMaxHealth() << ' ' << now -> getCurrentHealth() << ' ' << now -> getAttack() << ' ' << now -> getDefense() << endl;/*write the player's state into the record*/

	Room* cur = now -> getCurrentRoom();/*write the room which the player is in*/
	Room* prv = now -> getPreviousRoom();/*write the room which the player just passed by*/

	out << cur -> getIndex() << ' ';/*write both rooms' number*/
	out << prv -> getIndex() << endl;

	vector<Item> inventory = (*now).getInventory();/*get the player's all items*/
	out << inventory.size() << endl;/*get the number of items*/
	for (auto i : inventory) {/*loop to write all the items*/
		i.checklist(out);
	}
}

void Record::loadPlayer(Player* now, ifstream& in, vector<Room>& rooms) {/*read information from the file*/
	string tag, name;
	in >> tag >> name;

	int maxhp, curhp, attack, def;
	in >> maxhp >> curhp >> attack >> def;

	*now = *(new Player(name, maxhp, attack, def));
	now -> setCurrentHealth(curhp);

	int curRoomid;
	in >> curRoomid;
	int prvRoomid;
	in >> prvRoomid;

	now -> setCurrentRoom(&rooms[curRoomid - 1]);/*remember that the index is larger than its address 1, so minus 1*/
	now -> setPreviousRoom(&rooms[prvRoomid - 1]);

	vector<Item> inventory;
	int t;
	in >> t;/*get the number of items*/
	while (t--) {/*when there is item*/
		in >> tag >> name;
		int hp, attack, def;
		in >> hp >> attack >> def;
		inventory.push_back(Item(name, hp, attack, def));/*let items into the bag*/
	}
	now -> setInventory(inventory);
}


void Record::saveRooms(vector<Room>& v, ofstream& out) {/*save the map*/
	out << v.size() << '\n';
	for (auto i : v) {
		out << (i.getIsExit() ? 1 : 0) << '\n';/*check if the player has already got to the exit*/
		out << (i.getUpRoom()    == NULL ? -1 : (*(i.getUpRoom())).getIndex()) << ' ';/*write the room's index*/
		out << (i.getDownRoom()  == NULL ? -1 : (*(i.getDownRoom())).getIndex()) << ' ';
		out << (i.getLeftRoom()  == NULL ? -1 : (*(i.getLeftRoom())).getIndex()) << ' ';
		out << (i.getRightRoom() == NULL ? -1 : (*(i.getRightRoom())).getIndex()) << '\n';

		vector<Object*> v = i.getObjects();/*check what object is in the room*/
		out << v.size() << '\n';
		for (auto j : v) {
			j -> checklist(out);/*write it into this*/
		}
	}
}

void Record::loadRooms(vector<Room>& v, ifstream& in) {/*read information from the file*/
	int n;
	in >> n;
	for (int i = 0; i < n; i++) {
		v.push_back(Room());/*push room into the vector*/
		v[i].setIndex(i + 1);/*remember index must plus 1*/
	}
	for (int i = 0; i < n; i++) {/*check exit*/
		int isExit;
		in >> isExit;
		v[i].setIsExit((isExit == 1 ? true : false));

		int up, dw, lf, rg;
		in >> up >> dw >> lf >> rg;
		if (up != -1) v[i].setUpRoom(&v[up - 1]);/*note the relation between index and its address*/
		if (dw != -1) v[i].setDownRoom(&v[dw - 1]);
		if (lf != -1) v[i].setLeftRoom(&v[lf - 1]);
		if (rg != -1) v[i].setRightRoom(&v[rg - 1]);


		int objsize;
		in >> objsize;/*get the number of objects*/
		vector<Object*> objs;
		objs.clear();/*ensure*/
		while (objsize--) {/*if there is object*/
			string tag, name;
			in >> tag >> name;

			if (tag == "monster") {/*monster*/
				int cth, maxhp, attack, def;
				in >> cth >> maxhp >> attack >> def;
				objs.push_back(new Monster(name, maxhp, attack, def));

				Monster* mos = dynamic_cast<Monster*>(objs.back());/*down casting*/
				(*mos).setCurrentHealth(cth);
			}
			if (tag == "npc") {/*npc but to record the item*/
				in.ignore();
				string scr;
				getline(in, scr);
				int sz; in >> sz;

				vector<Item> comm;
				comm.clear();/*ensure*/
				for (int j = 1; j <= sz; j++) {
					string itnam, ittag;
					in >> ittag >> itnam;
					int hp, attack, def;
					in >> hp >> attack >> def;
					comm.push_back(Item(itnam, hp, attack, def));
				}
				objs.push_back(new NPC(name, scr, comm));/*whole npc including items*/
			}
			if (tag == "item") {/*item but here would be blessing*/
				int hp, attack, def;
				in >> hp >> attack >> def;
				objs.push_back(new Item(name, hp, attack, def));
			}
		}
		v[i].setObjects(objs);
	}
}
