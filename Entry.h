using namespace System;

public ref struct Entry {
private:
	String^ type;
	String^ desc;
public:
	Entry(String^);
	Entry(String^, int);
	Entry(String^, String^);
	Entry(String^, String^, int);
	Entry(int, int, int);
	Entry(double, double);
	String^ Type() { return this->type; };
	String^ Desc() { return this->desc; };
};