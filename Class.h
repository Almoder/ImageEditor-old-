using namespace System;
using namespace System::Drawing;

public ref class Class {
private:
	Image^ img;
	Point bl, tr;
public:
	Class();
	Class(Point, Point, Image^);
	~Class();
private:
};