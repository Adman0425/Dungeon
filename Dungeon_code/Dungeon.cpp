#include "Dungeon.h"
#include "Player.h"
#include <iostream>
#include <cctype>
#include <ctime>
using namespace std;

Dungeon::Dungeon() {
}

void Dungeon::createPlayer(string& name) {/*new a player and let the player in the first room*/
	this -> player = Player(name, 100, 10, 0);
	this -> player.setCurrentRoom(&rooms[0]);
	this -> player.setPreviousRoom(&rooms[0]);
}

void Dungeon::createMap() {/*get map ready*/
	std::ifstream file_in;
	file_in.open("Map1.txt");/*read the txt that record all rooms*/
	if (!file_in.good()) {
		cout << "Map file loads failed\n";/*if the file get any error*/
		exit(0);/*then exit*/
	}
	int maxRoom;
	file_in >> maxRoom;
	for (int i = 0; i < maxRoom; i++) {
		rooms.push_back(Room());/*new several room into the vector and set their index first*/
		rooms[i].setIndex(i + 1);
	}

	int x;
	for (int i = 0; i < maxRoom; i++) {
        file_in >> x;
        if (x != -1) rooms[i].setUpRoom(&rooms[x]);/*set up room*/
        file_in >> x;
        if (x != -1) rooms[i].setDownRoom(&rooms[x]);/*set down room*/
        file_in >> x;
        if (x != -1) rooms[i].setLeftRoom(&rooms[x]);/*set left room*/
        file_in >> x;
        if (x != -1) rooms[i].setRightRoom(&rooms[x]);/*set right room*/
	}
	file_in.close();/*close the file*/

	rooms[maxRoom - 1].pushObject(monsters[0]); /*set the boss in the last room*/
	rooms[maxRoom - 1].setIsExit(true);/*set the exit in the last room*/

	int ptrNpc = 0;
	for (int i = 1; i < maxRoom; i += rand() % 3) {
		rooms[i].pushObject(new NPC(npcs[ptrNpc++]));/*let the npcs in rooms randomly*/

		if (ptrNpc == npcs.size()) ptrNpc = 3;
	}
}

void Dungeon::handleMovement() {
	Room* rm = player.getCurrentRoom();/*get the map information and tell the player where can go*/
	Room* pm = player.getPreviousRoom();

	Room* up = (*rm).getUpRoom();
	Room* dw = (*rm).getDownRoom();
	Room* lf = (*rm).getLeftRoom();
	Room* rg = (*rm).getRightRoom();

	if (up != NULL) cout << "W:Please enter 'w' to go up room.\n";
	if (dw != NULL) cout << "S:Please enter 's' to go down room.\n";
	if (lf != NULL) cout << "A:Please enter 'a' to go left room.\n";
	if (rg != NULL) cout << "D:Please enter 'd' to go right room.\n";

	bool isExit = (*rm).getIsExit();/*check if there is exit*/
	if (isExit) cout << "F:Please enter 'f' to finished the game\n";/*if the player go to the exit*/

	string ope;
	cin >> ope;
	ope[0] = tolower(ope[0]);/*prevent the input is upper class*/
	if (ope == "w" && up != NULL) player.setCurrentRoom(up);/*move to the room player want to go*/
	if (ope == "s" && dw != NULL) player.setCurrentRoom(dw);
	if (ope == "a" && lf != NULL) player.setCurrentRoom(lf);
	if (ope == "d" && rg != NULL) player.setCurrentRoom(rg);
	if (ope == "f" && isExit && player.getwhetherWin()) {/*if the player want to finish this*/
		cout << "You have seen the catastrophe of this great stage.\n";
		cout << "And everything goes silent again. Neither weeping nor crying would be heard anymore.\n";
		exit(0);/*then exit*/
	}
	int r = rand(), tmp = RAND_MAX / 3;
	if (r < tmp && pm != player.getCurrentRoom()) {
		player.getCurrentRoom() -> pushObject(new Monster(monsters[rand() % (monsters.size() - 1) + 1]));/*reset the monster in the current room*/
	}
	r = rand(), tmp = RAND_MAX / 5;
	if (r < tmp && pm != player.getCurrentRoom()) {
		player.getCurrentRoom() -> pushObject(new NPC(npcs[rand() % (npcs.size() - 2) + 2]));/*reset the npc in the current room*/
	}
}

/* void Dungeon::handleEvent(Object* obj) {}*/
/* void Dungeon::chooseAction(vector<Object*> v) {}*/

bool Dungeon::handleAttack(string& name) {/*the movement that the player want to attack monster*/
	Room* rom = player.getCurrentRoom();

	for (auto i : (*rom).getObjects()) {
		Monster* monptr = dynamic_cast<Monster*>(i);/*turn the object into monster*/
		if (monptr == NULL) continue;/*go to output the error message*/

		if ((*i).getName() == name) {
			Object* now = monptr;

			if ((*now).triggerEvent(&player))/*call function to deal with the attack*/
				(*rom).popObject(i);
			return true;
		}
	}
	cout << "We have no such name!\n";/*if there's no monster or the input is false*/
	return false;
}

bool Dungeon::handlePurchase(string& name) {/*the movement that the player want to buy something*/
	Room* rom = player.getCurrentRoom();

	for (auto i : (*rom).getObjects()) {
		NPC* npcptr = dynamic_cast<NPC*>(i);/*turn the object into npc*/
		if (npcptr == NULL) continue;

		if ((*i).getName() == name) {
			npcptr -> listCommodity();/*output the item that player can buy*/

			if ((*npcptr).triggerEvent(&player))
				(*rom).popObject(i);
			return true;
		}
	}
	cout << "We have no such name!\n";/*if there's no npc*/
	return false;
}

vector<Monster*> getMonster() {/*get the monsters be ready*/
	vector<Monster*> v;/*new a vector to keep the monsters' information*/
	v.clear();/*clear it just for ensure it's empty*/

	std::ifstream file_in;
	file_in.open("Monsters1.txt");/*read the information in a txt that record all monsters*/
	if (!file_in.good()) {
		cout << "Monster file loads failed\n";/*if the file get any error then we'll know*/
		exit(0);/*then exit*/
	}

	string name;
	int hp, attack, def;
	while (file_in >> name) {/*get each monster into the vector*/
		file_in >> hp >> attack >> def;
		v.push_back(new Monster(name, hp, attack, def));/*write all information and after let it into the vector*/
	}
	file_in.close();/*close the file*/
	return v;
}

vector<NPC*> getNpc() {/*get the npcs be ready*/
	vector<NPC*> v;/*new a vector to keep the npcs' information*/
	v.clear();/*clear it*/

	std::ifstream file_in;
	file_in.open("NPCs1.txt");/*read the information in a txt that record all npcs*/
	if (!file_in.good()) {
		cout << "NPC file loads failed\n";/*if the file doesn't work*/
		exit(0);/*then exit*/
	}

	vector<Item> commodity;
	string name, scr, itnam;
	int n, hp, attack, def;
	while (file_in >> name) {/*get each npc into the vector*/
		file_in.ignore();
		getline(file_in, scr);/*read the script to check if the npc still exists*/

		file_in >> n;/*the number of commodity*/
		commodity.clear();
		while (n--) {
			file_in >> itnam >> hp >> attack >> def;
			commodity.push_back(Item(itnam, hp, attack, def));/*get item that are commodities into the commodity vector*/
		}
		v.push_back(new NPC(name, scr, commodity));/*let all information into the npc vector*/
	}
	file_in.close();/*close the file*/
	return v;
}

void Dungeon::startGame() {
	srand(time(NULL));/*set random seed*/

	string name;
	Record rec;/*new a record to prepare for save file*/

	cout << "\nWaiting for the stage...\n";
	this -> monsters = getMonster();/*load the monsters and npc*/
	this -> npcs = getNpc();
	cout << "The ticket of journey is in your hand.\n\n";
	sleep(1);


	cout << "Dedicate your name to:";
	cin >> name;/*get the player's name*/
	if (rec.checkFile(name)) {/*if the player has already existed*/
		cout << "\nThere is something haven't dissipated in eternity...\n";
		rec.loadFromFile(name, &player, rooms);/*read the files*/
		sleep(1);
	}
	else {
		cout << "\nHere would have an obtuse guest again...\n";
		this -> createMap();/*new the map*/
		this -> createPlayer(name);/*new the player*/
		cout << "It seems somebody has prepared for entertaining our new guest.\n";
		sleep(1);
	}
	this -> runDungeon();/*call the function that will check game logic and print all the movement that player can do*/
}

bool Dungeon::checkGameLogic() {/*function to check if the player still alive.*/
	if ((this -> player).checkIsDead()) return false;

	return true;
}

void listMovement() {/*function to tell the player what can they do.*/
	cout << "\nOperations:\n";
	cout << "M:Please enter 'm' to move\n";
	cout << "A:Please enter 'a' to attack\n";
	cout << "P:Please enter 'p' to pursue something you want\n";
	cout << "L:Please enter 'l' to list the item you have\n";
	cout << "E:Please enter 'e' to exit the game and save records\n";
}

bool isMovement(string& s) {/*function to check if the input is a legal operation.*/
	if (s.length() != 1) return false;

	if (s == "e") return true;
	if (s == "l") return true;
	if (s == "m") return true;
	if (s == "a") return true;
	if (s == "p") return true;

	return false;
}

void Dungeon::runDungeon() {/*function that deal with the player's movement and check if it's legal*/
	string ope;
	while (checkGameLogic()) {/*check the player still alive*/
		cout << "\n\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
		cout << "       Next Movement\n";
		cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n";

		cout << player << "\n\n";
		cout << *(player.getCurrentRoom()) << '\n';

		listMovement();/*tell the player they can do something to console the character.*/

		cin >> ope;/*get the player's movement*/
		ope[0] = tolower(ope[0]);
		while (!isMovement(ope)) {
			cout << "Illegal input! Please check it again.\n";
			cin >> ope;/*you can input it again if you enter a wrong word not on purpose.*/
		}

		if (ope == "e") {/*exit the game.*/
			Record rec;
			rec.saveToFile(&player, rooms);/*save all files*/
			break;
		}

		if (ope == "l") {/*list the player's items*/
			vector<Item> v = player.getInventory();
			for (auto i : v) cout << i << '\n';/*print all items if there are*/
			if (v.size() == 0) cout << "You are all alone in this world.\n";
		}

		if (ope == "m") this -> handleMovement();/*move to other rooms*/

		if (ope == "a") {/*attack monsters.*/
			(*(player.getCurrentRoom())).listAttack();/*get all targets that the player can attack*/
			string s;
			do {
				cout << "Choose the unlucky wretch or just enter 'e' to flee for your life: ";
				cin >> s;
				if (s == "e") break;/*if the player wants to exit*/
			} while (!(this -> handleAttack(s)));
		}

		if (ope == "p") {/*buy item from npc*/
			(*(player.getCurrentRoom())).listNPC();/*print all things that in the npc file*/
			string s;
			do {
				cout << "Choose the lucky guy you want get something from him or just enter 'e' to express your depression of all worthless commodities: ";
				cin >> s;
				if (s == "e") break;/*if the player wants to exit*/
			} while (!(this -> handlePurchase(s)));
		}
		sleep(2);/*lag for some time to stop it*/
	}
}
