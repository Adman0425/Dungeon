#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"

using namespace std;

class Item;
class Room;

class Player: public GameCharacter {
private:
    Room* currentRoom;
    Room* previousRoom;
    vector<Item> inventory;
    bool whetherWin;

public:
    Player();
    Player(string,int,int,int);
    void addItem(Item);
    void increaseStates(int,int,int);

    /* Virtual function that you need to complete   */
    /* In Player, this function should show the     */
    /* status of player.                            */
    bool triggerEvent(Object*);

    /* Set & Get function*/
    void setCurrentRoom(Room*);
    void setPreviousRoom(Room*);
    void setInventory(vector<Item>);
    void setwhetherWin(bool);
    Room* getCurrentRoom() const;
    Room* getPreviousRoom() const ;
    vector<Item> getInventory() const;
    bool getwhetherWin() const;

    friend ostream& operator<<(ostream&, const Player&);
};

ostream& operator<<(ostream& out, const Player& p);

#endif // PLAYER_H_INCLUDED
