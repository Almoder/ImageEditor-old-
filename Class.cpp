#include "Class.h"

Class::Class() {
	img = nullptr;
	bl = Point::Empty;
	tr = Point::Empty;
}

Class::Class(Point bl, Point tr, Image^ img) {
	this->bl = bl;
	this->tr = tr;
}

Class::~Class() {

}