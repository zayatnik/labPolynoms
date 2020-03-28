#include "stdafx.h"
#include "polynom.h"

int main(){
	setlocale(LC_ALL, "russian");
	string p1, p2;
	cout << "Введите первый полином p1: ";
	getline(cin, p1);
	cout << "Введите второй полином p2: ";
	getline(cin, p2);
	Polynom poly1(p1);
	Polynom poly2(p2);
	cout << "p1 + p2 = " << (poly1 + poly2).Tostring() << endl;
	cout << "p1 - p2 = " << (poly1 - poly2).Tostring() << endl;
	cout << "p1 * p2 = " << (poly1 * poly2).Tostring() << endl;
	cout << "df/dx от p1 = " << dfdx(poly1).Tostring() << endl;
	cout << "df/dy от p1 = " << dfdy(poly1).Tostring() << endl;
	cout << "df/dz от p1 = " << dfdz(poly1).Tostring() << endl;
}
