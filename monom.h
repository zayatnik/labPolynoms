#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

const int p = 10;

class monom{
	int power;
	double coef;
public:
	monom(int a, int b, int c, double k1);
	monom(int d = -1, double c = 0);
	monom(string a);
	monom(const monom &a);
	string tostring();
	monom dfdx();
	monom dfdy();
	monom dfdz();
	monom operator+=(const monom);
	monom operator+(const monom);
	monom operator-=(const monom);
	monom operator-(const monom);
	monom operator-();
	monom operator*(const monom);
	monom operator*=(const monom);
	bool operator<(const monom);
	bool operator<=(const monom);
	bool operator>(const monom);
	bool operator>=(const monom);
	bool operator==(const monom);
	bool operator!=(const monom);
	bool operator<(const double a){
		return coef < a;
	}
	bool operator<=(const double a){
		return coef <= a;
	}
	bool operator>(const double a){
		return coef > a;
	}
	bool operator>=(const double a){
		return coef >= a;
	}
	bool operator==(const double a){
		return coef == a;
	}
	bool operator!=(const double a){
		return coef != a;
	}
	monom abs(){
		monom a = *this;
		if (a.coef < 0)
			a.coef = -coef;
		return a;
	}
	~monom();
};

int getpowerint(int a, int b, int c);
vector<int> getpowervec(int d);
