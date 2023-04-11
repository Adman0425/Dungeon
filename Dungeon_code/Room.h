#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Monster.h"
#include "NPC.h"
#include "Item.h"

using namespace std;

class Room {
private:
    Room* upRoom;
    Room* downRoom;
    Room* leftRoom;
    Room* rightRoom;
    bool isExit;
    int index;
    vector<Object*> objects; /*contain 1 or multiple objects, including monster, npc, etc*/

public:
    Room();
    Room(bool, int, vector<Object*>);
    bool popObject(Object*); /*pop out the specific object, used when the interaction is done*/
    void pushObject(Object*);

    /* Set & Get function*/
    void setUpRoom(Room*);
    void setDownRoom(Room*);
    void setLeftRoom(Room*);
    void setRightRoom(Room*);
    void setIsExit(bool);
    void setIndex(int);
    void setObjects(vector<Object*>);
    bool getIsExit() const;
    int getIndex() const;
    vector<Object*> getObjects() const;
    Room* getUpRoom() const;
    Room* getDownRoom() const;
    Room* getLeftRoom() const;
    Room* getRightRoom() const;

    void listAttack() const;
    void listNPC() const;
    friend ostream& operator<<(ostream&, const Room&);
};


ostream& operator<<(ostream& out, const Room& rom);

#endif // ROOM_H_INCLUDED
