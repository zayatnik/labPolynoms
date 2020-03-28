#pragma once
#include "monom.h"
#include <algorithm>

struct Node{
	monom data;
	Node* next;
};

class Polynom{
	Node *first;
public:
	Polynom();
	Polynom(string s);
	Polynom(vector<monom> a);
	Polynom(Node *p);
	Polynom(const Polynom& a);
	Polynom& operator=(const Polynom& a);
	void delzeros();
	Polynom& merge(Polynom& a);
	Polynom merge(vector<Polynom>a);
	Polynom operator-();
	Polynom operator+=(Polynom  &a);
	Polynom operator+(Polynom a);
	Polynom operator-=(Polynom &a);
	Polynom operator-(Polynom a);
	Polynom operator*= (monom a);
	Polynom operator*(monom a);
	Polynom operator*=(Polynom &a);
	Polynom operator*(Polynom a);
	Polynom dfdx();
	Polynom dfdy();
	Polynom dfdz();
	string Tostring();
	~Polynom();
};

Polynom dfdx(Polynom a);
Polynom dfdy(Polynom a);
Polynom dfdz(Polynom a);
