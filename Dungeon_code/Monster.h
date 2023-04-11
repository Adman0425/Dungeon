#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include "Player.h"
#include "GameCharacter.h"
#include "Player.h"
#include "Item.h"

using namespace std;

class Monster: public GameCharacter {
private:

public:
    Monster();
    Monster(const Monster*);
    Monster(string,int,int,int);

    /* Virtual function that you need to complete   */
    /* In Monster, this function should deal with   */
    /* the combat system.                           */
    bool triggerEvent(Object*);

    void checklist(ofstream&) const;
    void showlist() const;
    friend ostream& operator<<(ostream&, const Monster&);
};

ostream& operator<<(ostream& out, const Monster& mon);


#endif // ENEMY_H_INCLUDED
