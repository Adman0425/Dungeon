
#include "Object.h"

Object::Object() {
	this -> name = "NULL";
	this -> name = "NULL";
}

Object::Object(string name, string tag) {
	this -> name = name;
	this -> tag = tag;
}

void Object::setName(string name) {
	this -> name = name;
}

void Object::setTag(string tag) {
	this -> tag = tag;
}

string Object::getName() const {
	return this -> name;
}

string Object::getTag() const {
	return this -> tag;
}

void Object::checklist(ofstream& out) const {/*record*/
	out << getTag() << ' ' << getName() << '\n';
}

ostream& operator<<(ostream& out, const Object& obj) {/*overload operator*/
	out << obj.getName();
	return out;
}
