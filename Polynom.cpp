#include "stdafx.h"
#include "Polynom.h"


Polynom::Polynom(){
	monom a;
	first = new Node;
	first->data = a;
	first->next = first;
}

Polynom::Polynom(string s){
	stringstream ss;
	ss << s;
	string word, lastword = "+";
	monom data(-1, 0);
	vector<monom> v;
	while (ss >> word){
		if ((lastword == "+" || lastword == "-") && (word == "+" || word == "-") || 
			(lastword != "+" && lastword != "-") && (word != "+" && word != "-")){
			throw 1;
		}
		else{
			if (word != "+" && word != "-"){
				monom a(word);
				if (lastword == "-"){
					a = -a;
				}
				v.push_back(a);
			}
			lastword = word;
		}
	}
	sort(v.rbegin(), v.rend());
	first = new Node;
	Node *p = first;
	for (size_t i = 0; i < v.size(); ++i){
		if (v[i] != p->data){

			Node*cur = new Node;
			cur->data = v[i];
			p->next = cur;
			p = p->next;
		}
		else{
			p->data += v[i];
		}

	}
	p->next= first;
	delzeros();
}

Polynom::Polynom(vector<monom> a){
}

Polynom::Polynom(Node * p){
	first = p;
}

Polynom::Polynom(const Polynom & a){
	first = new Node;
	Node *p1 = first, *p2 = a.first->next;
	while (p2 != a.first){
		Node *cur = new Node;;
		cur->data = p2->data;
		p1->next = cur;
		p1 = p1->next;
		p2=p2->next;
	}
	p1->next = first;
}

Polynom& Polynom::operator=(const Polynom& a){
	if (first == a.first)
		return *this;
	while (first->next != first){
		Node *tmp = first->next;
		first->next = first->next->next;
		delete tmp;
	}

	Node *p = a.first->next, *p1 = first;
	while (p!= a.first){
		Node* cur = new Node;
		cur->data = p->data;
		p1->next = cur;
		p1 = p1->next;
		p = p->next;
	}
	p1->next = first;
	return *this;
}

void Polynom::delzeros(){
	Node*p = first;
	while (p->next != first){
		if (p->next->data == 0){
			Node *tmp = p->next;
			p ->next = p->next->next;
			delete tmp;
		}
		else{
			p = p->next;
		}
	}
}

Polynom & Polynom::merge(Polynom & a){
	Node *pFirst0 = new Node;
	Node *p1 = first->next, *p2 = a.first->next, *p = pFirst0;
	while (p1 != first || p2 != a.first){
		if (p1->data <= p2->data){
			if (p2->data == p->data){
				p->data += p2->data;
				Node *tmp = p2;
				p2 = p2->next;
				delete tmp;
			}
			else{
				p->next = p2;
				p = p2;
				p2 = p2->next;
			}
		}
		else{
			if (p1->data == p->data){
				p->data += p1->data;
				Node *tmp = p1;
				p1 = p1->next;
				delete tmp;
			}
			else{
				p->next = p1;
				p = p1;
				p1 = p1->next;
				
			}
		}
	}
	first = pFirst0;
	p->next = first;
	a.first->next = a.first;
	delzeros();
	return *this;
}

Polynom Polynom::merge(vector<Polynom> a){	
	vector<Polynom> b = a;
	while (b.size() > 1){
		a = {};
		for (int i = 0; i < b.size(); i+=2){
			if (i + 1 < b.size())
				a.push_back(b[i].merge(b[i + 1]));
			else
				a.push_back(b[i]);
		}
		b = a;
	}
	return b[0];
}

Polynom Polynom::operator-(){
	Polynom a(*this);
	Node*p = a.first->next;
	while (p != a.first){
		p->data = -(p->data);
		p = p->next;
	}
	return a;
}

Polynom Polynom::operator+=(Polynom & a){
	Polynom b = a;
	return *this = merge(b);
}

Polynom Polynom::operator+(Polynom a){
	Polynom b(*this);
	return b += a;
}

Polynom Polynom::operator-=(Polynom & a){
	Polynom b = -a;
	return *this += b;
}

Polynom Polynom::operator-(Polynom a){
	Polynom b(*this);
	return b -= a;
}

Polynom Polynom::operator*=(monom a){
	Node*p = first->next;
	while (p != first){
		p->data *= a;
		p = p->next;
	}
	return *this;
}

Polynom Polynom::operator*(monom a){
	Polynom c(*this);
	c *= a;
	return c;
}

Polynom Polynom::operator*=(Polynom & a){
	vector<Polynom>b;
	Node *p = first->next;
	Polynom c(a);
	while (p != first){
		
		b.push_back(c * (p->data));
		p = p->next;
	}
	if (b.size() == 0){
		Polynom h;
		return h;
	}
	return *this = merge(b);
}

Polynom Polynom::operator*(Polynom a){
	Polynom c(*this);
	c *= a;
	return c;
}

Polynom Polynom::dfdx(){
	Node *p = first->next;
	while (p != first){
		p->data = p->data.dfdx();
		p = p->next;
	}
	delzeros();
	return *this;
}

Polynom Polynom::dfdy(){
	Node *p = first->next;
	while (p != first){
		p->data = p->data.dfdy();
		p = p->next;
	}
	delzeros();
	return *this;
}

Polynom Polynom::dfdz(){
	Node *p = first->next;
	while (p != first){
		p->data = p->data.dfdz();
		p = p->next;
	}
	delzeros();
	return *this;
}

string Polynom::Tostring(){
	Node *p = first;
	string ans = "";
	if (p->next == first)
		return "0";
	if (p->next->data > 0)
		ans += p->next->data.tostring();
	else
		ans += "-" + p->next->data.abs().tostring();
	p = p->next;
	while (p->next != first){
		if (p->next->data < 0)
			ans += " - ";
		else
			ans += " + ";
		ans += (p->next->data).abs().tostring();
		p=p->next;
	}
	return ans;
}

Polynom::~Polynom(){
	Node*p = first->next;
	while (p != first){
		Node* tmp = p;
		p = p->next;
		delete tmp;
	}
	delete first;
}

Polynom dfdx(Polynom a){
	Polynom b(a);
	b.dfdx();
	return b;
}

Polynom dfdy(Polynom a){
	Polynom b(a);
	b.dfdy();
	return b;
}

Polynom dfdz(Polynom a){
	Polynom b(a);
	b.dfdz();
	return b;
}
