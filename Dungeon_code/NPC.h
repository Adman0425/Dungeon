#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"
#include "Item.h"

using namespace std;

class Item;

class NPC: public GameCharacter {
private:
    string script;
    vector<Item> commodity;
public:
    NPC();
    NPC(const NPC*);
    NPC(string, string, vector<Item>);
    void listCommodity(); /*print all the item in this NPC*/

    /* Virtual function that you need to complete   */
    /* In NPC, this function should deal with the   */
    /* transaction in easy implementation           */
    bool triggerEvent(Object*);

    /* Set & Get function*/
    void setScript(string);
    void setCommodity(vector<Item>);
    string getScript() const;
    vector<Item> getCommodity() const;

    void checklist(ofstream&) const;
    friend ostream& operator<<(ostream&, const NPC&);
};

ostream& operator<<(ostream& out, const NPC& npc);


#endif // NPC_H_INCLUDED
