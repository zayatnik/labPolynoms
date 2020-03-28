#include "stdafx.h"
#include "monom.h"
#include <iterator>

monom::monom(int a, int b, int c, double k1){
	if (a >= p || b >= p || c >= p)
		throw 1;
	power = getpowerint(a, b, c);
	coef = k1;
}

monom::monom(int d, double c){
	if (d >= p * p * p)
		throw 1;
	power = d;
	coef = c;
}

bool isCorrect(string s){
	string a = "xyzXYZ0123456789";
	for (size_t i = 0; i < a.size(); ++i){
		
		if (a.find(a[i]) == string::npos){
			return false;
		}
	}
	return true;
}

pair<int, string::iterator> getFirstNumber(string::iterator a, string::iterator b){
	string s = "0123456789";
	bool ok = false;
	int coef = 1;
	for (; a != b && s.find(*a) != string::npos; ++a){
		if (!ok){
			ok = true;
			coef = 0;
		}
		coef = 10 * coef -'0' + *a;
	}
	if (!ok && a != b)
		return pair<int, string::iterator>(coef, a++);
	return pair<int, string::iterator>(coef, a);
}

monom::monom(string s){
	int a = 0, b = 0, c = 0;
	pair<int, string::iterator> pr = getFirstNumber(s.begin(), s.end());
	coef = pr.first;
	for (string::iterator it = pr.second; it != s.end();){
		if (*it == 'x' || *it == 'X'){
			pair<int, string::iterator> p = getFirstNumber(it + 1, s.end());
			a += p.first;
			it = p.second;
		}
		else if (*it == 'y' || *it == 'Y'){
			pair<int, string::iterator> p = getFirstNumber(it + 1, s.end());
			b += p.first;
			it = p.second;
		}
		else if (*it == 'z' || *it == 'Z'){
			pair<int, string::iterator> p = getFirstNumber(it + 1, s.end());
			c += p.first;
			it = p.second;
		}
		else
			throw 1;
	}
	power = getpowerint(a, b, c);
}

monom::monom(const monom &a){
	power = a.power;
	coef = a.coef;
}

string monom::tostring(){
	vector<int> kof = getpowervec(power);
	stringstream ans;
	ans << "";
	string vars = "xyz";
	if (coef == 0)
		return ans.str();
	stringstream out;
	if (coef != 1){
		out << coef;
		ans << out.str();
	}
	for (size_t i = 0; i < 3; ++i){
		if (kof[i] != 0){
			if (kof[i] == 1){
				ans << vars[i];
			}
			else{
				ans << vars[i];
				ans << kof[i];
			}
		}
	}
	return ans.str();
}

monom monom::dfdx(){
	monom a(0, 0);
	if (power / p * p < 1){
		return a;
	}
	int n = power / p / p;
	a.coef = coef * n;
	a.power = power - p * p;
	return a;
}

monom monom::dfdy(){
	monom a(0, 0);
	if ((power / p) % p < 1){
		return a;
	}
	int n = (power / p) % p;
	a.coef = coef * n;
	a.power = power - p;
	return a;
}

monom monom::dfdz(){
	monom a(0, 0);
	if (power % p < 1){
		return a;
	}
	int n = power % p;
	a.coef = coef * n;
	a.power = power - 1;
	return a;
}

monom monom::operator+=(const monom a){
	if (*this == a){
		coef += a.coef;
	}
	else
	{
		throw 1;
	}
	return *this;
}

monom monom::operator+(const monom a){
	monom b(power, coef);
	b += a;
	return b;
}

monom monom::operator-=(const monom a){
	if (*this != a)
		throw 1;
	coef -= a.coef;
	return *this;
}

monom monom::operator-(const monom a){
	monom b(*this);
	b -= a;
	return b;
}

monom monom::operator-(){
	coef = -coef;
	return *this;
}

monom monom::operator*(const monom a){
	monom b(*this);
	b *= a;
	return b;
}

monom monom::operator*=(const monom a){
	if (a.power % p + power % p >= p || a.power / p % p + power / p % p >= p || a.power / p / p % p + power / p / p % p >= p)
		throw 1;
	power += a.power;
	coef *= a.coef;
	return *this;
}

bool monom::operator<(const monom a){
	if (power < a.power)
		return true;
	return false;
}

bool monom::operator<=(const monom a){
	if (power <= a.power)
		return true;
	return false;
}

bool monom::operator>(const monom a){
	if (power > a.power)
		return true;
	return false;
}

bool monom::operator>=(const monom a){
	if (power >= a.power)
		return true;
	return false;
}

bool monom::operator==(const monom a){
	if (power == a.power)
		return true;
	return false;
}

bool monom::operator!=(const monom a){
	if (power != a.power)
		return true;
	return false;
}


monom::~monom(){
}

int getpowerint(int a, int b, int c){
	int ans = a;
	ans = ans * p + b;
	ans = ans * p + c;
	return ans;
}

vector<int> getpowervec(int d){
	vector<int> ans(3);
	for (int i = 2; i >= 0; --i){
		ans[i] = d % p;
		d /= p;
	}
	return ans;
}
