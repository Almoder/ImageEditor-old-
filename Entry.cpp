#include "Entry.h"

//Only "type" value.
Entry::Entry(String^ type) {
	this->type = type;
}

//Mask size (filtering).
Entry::Entry(String^ type, int mSize) {
	this->type = type;
	desc = String::Join("", "Mask size: ", mSize, "x", mSize);
}

//Type and description.
Entry::Entry(String^ type, String^ desc) {
	this->type = type;
	this->desc = desc;
}

//Linear/nonlinear brightness/contrast
Entry::Entry(String^ type, String^ tfrm, int arg) {
	this->type = String::Join(" ", type, tfrm);
	this->desc = String::Join(" ", "Argument:", arg);
}

//Binarization only!
Entry::Entry(int t, int b0, int b1) {
	type = "Binarization";
	desc = String::Join(" ",
		"Threshold:", t, "Value1:", b0, " Value2:", b1);
}

//Power only!
Entry::Entry(double c, double g) {
	type = "Power transformation";
	desc = String::Join(" ", "Multiplier:", c, "Power:", g);
}