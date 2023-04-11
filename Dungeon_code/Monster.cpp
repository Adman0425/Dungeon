#include "Monster.h"

Monster::Monster(): GameCharacter("", "monster", 0, 0, 0) {
}

Monster::Monster(string name, int hp, int attack, int def): GameCharacter(name, "monster", hp, attack, def) {/*call the constructor of game character*/
}

Monster::Monster(const Monster* mon) {
    this -> setName(mon -> getName());
    this -> setTag(mon -> getTag());
    this -> setMaxHealth(mon -> getMaxHealth());
    this -> setCurrentHealth(mon -> getCurrentHealth());
    this -> setAttack(mon -> getAttack());
    this -> setDefense(mon -> getDefense());
}

void Monster::checklist(ofstream& out) const {
    Object::checklist(out);/*call the function that belonged to object*/
    out << getCurrentHealth() << ' ' << getMaxHealth() << '\n' << getAttack() << ' ' << getDefense() << '\n';
}

bool Monster::triggerEvent(Object* obj) {/*monsters would combat if player attack them*/
    Player *player = dynamic_cast<Player*>(obj);
    if (player == NULL) return false;/*the player must exist*/

    while (1) {
        cout << "\nNow against " << *this << '\n';
        cout << "Please enter 'c' to confirm attack.\n";
        cout << "Please enter 'r' to retreat.\n";

        string c;
        cin >> c;/*get the player's next movement*/
        c[0] = tolower(c[0]);

        if (c != "r" and c != "c") {
            cout << "There are no other choices.\n";
            continue;
        }
        if (c == "r") {/*player to retreat*/
            cout << "Flee for your life is not always a coward.\n";
            break;
        }
        if (c == "c") {
            int dg = this -> takeDamage((*player).getAttack());/*calculate the damage that player caused*/
            cout << "Total damage:" << dg << endl;

            if (this -> checkIsDead()) { /*check if monster dead*/
                cout << "All that can't kill you would make you stronger.\n";

                if (this -> getName() == "Phantom") {/*if encounter the boss and player kill it*/
                    player -> setwhetherWin(true);/*then the player win*/
                }
                /*calculate buff from every monster the player fight with*/
                int hp = this -> getAttack() * 0.5;
                int def = this -> getDefense() * 0.8;
                int attack = this -> getAttack() * 1.0;

                Item buff(this -> getName() + " Blessing ", hp, attack, def);/*that the buff be a kind of item*/
                cout << buff << '\n';

                buff.triggerEvent(player);/*plus the buff on the player's state by call additem*/
                return true;
            }

            dg = player -> takeDamage(this -> getAttack());/*calculate the damage that monster caused*/
            cout << "Be-damaged total:" << dg << endl;

            if ((*player).checkIsDead()) { /*if player is dead*/
                cout << "Stray lambs would wander in the dark-side of this stage.";
                sleep(10);/*sleep*/
                break;
            }

            sleep(2);/*sleep*/

            cout << *player << endl;
        }
    }
	return false;
}

void Monster::showlist() const {/*show the monster's state*/
    cout << this -> getName() << '\n';

    int hp =  this -> getCurrentHealth();
    cout << "HP: " << hp << " ";

    int attack = this -> getAttack();
    cout << "Attack: " << attack << " ";

    int def = this -> getDefense();
    cout << "Defense: " << def << '\n';
}

ostream& operator<<(ostream& out, const Monster& mon) {/*overload operator out*/
	out << "Enemy: " << mon.getName() << endl;

    int hp = mon.getCurrentHealth();
    out << "HP: " << hp << endl;

    int attack = mon.getAttack();
    out << "Attack: " << attack << endl;

    int def = mon.getDefense();
    out << "Defense: " << def << endl;

	return out;
}
