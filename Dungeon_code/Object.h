#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

class Object {

private:
    string name;
    string tag;

public:
    Object();
    Object(string,string);

    /* pure virtual function */
    virtual bool triggerEvent(Object*) = 0;

    /* Set & Get function*/
    void setName(string);
    void setTag(string);
    string getName() const;
    string getTag() const;

    virtual void checklist(ofstream&) const;
    friend ostream& operator<<(ostream&, const Object&);
};

ostream& operator<<(ostream& out, const Object& obj);

#endif // OBJECT_H_INCLUDED
