#include "gtest.h"
#include "monom.cpp"
#include "polynom.cpp"

TEST(TestCaseName, TestName){
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(monom, Test1){
	vector<int>a = getpowervec(11001001);
	vector<int> b = { 11, 1 ,1 };
	EXPECT_EQ(b, a);
}

TEST(monom, Test2){
	int a = getpowerint(1, 2, 3);
	EXPECT_EQ(1002003, a);
}

TEST(monom, Test3){
	monom a(1, 2, 3, 4);
	EXPECT_EQ(a.tostring(), "4xy2z3");
}

TEST(monom, Test4){
	monom a(0, 0, 0, 4);
	EXPECT_EQ(a.tostring(), "4");
}

TEST(monom, Test5){
	monom a(1, 2, 3, 0);
	EXPECT_EQ(a.tostring(), "");

}

TEST(monom, Test6){
	monom a(1, 2, 3, 4);
	monom b(1, 2, 3, 5);
	EXPECT_EQ(a == b, true);
}

TEST(monom, Test7){
	monom a("4y2z6x");
	EXPECT_EQ(a.tostring(), "4xy2z6");
}

TEST(monom, Test8){
	monom a("0");
	EXPECT_EQ(a.tostring(), "");
}

TEST(monom, Test9){
	monom a("123xzyxxxxx");
	EXPECT_EQ(a.tostring(), "123x6yz");
}

TEST(monom, Test10){
	monom a(1, 2, 3, 4);
	monom b(1, 2, 3, 5);
	EXPECT_EQ((a + b).tostring(), "9xy2z3");
}

TEST(monom, Test11){
	monom a(1, 2, 3, 4);
	monom b(2, 3, 4, 1);
	EXPECT_ANY_THROW(a + b);
}

TEST(monom, Test12){
	monom a(1, 1, 2, 4);
	monom b(2, 3, 4, 1);
	EXPECT_EQ((a*b).tostring(), "4x3y4z6");
}

TEST(monom, Test13){
	monom a(1, 1, 2, 4);
	monom b(2, 3, 4, 0);
	EXPECT_EQ((a*b).tostring(), "");
}

TEST(monom, Test14){
	monom a(1, 2, 3, 4);
	monom b(2, 3, 4, 1);
	EXPECT_ANY_THROW(a - b);
}

TEST(monom, Test15){
	monom a(1, 2, 3, 4);
	monom b(1, 2, 3, 1);
	EXPECT_EQ((a - b).tostring(), "3xy2z3");
}

TEST(monom, Test16){
	monom a(1, 2, 3, 4);
	monom b(2, 2, 3, 1);
	EXPECT_EQ(a != b, true);
}

TEST(monom, Test17){
	monom a(1, 2, 3, 4);
	monom b(2, 2, 3, 1);
	EXPECT_EQ(a < b, true);
}

TEST(monom, Test18){
	monom a(1, 2, 3, 4);
	monom b(2, 0, 0, 1);
	EXPECT_EQ(b > a, true);
}

TEST(monom, Test19){
	monom a(1, 2, 3, 4);
	monom b(1, 2, 3, 1);
	EXPECT_EQ(a <= b, true);
}

TEST(monom, Test20){
	monom a(1, 2, 3, 4);
	monom b(1, 2, 3, 1);
	EXPECT_EQ(a >= b, true);
}

TEST(monom, Test21){
	monom a(1, 2, 3, 99);
	EXPECT_EQ(a.tostring(), "99xy2z3");
}

TEST(monom, Test22){
	monom a(1, 2, 3, 99);
	EXPECT_EQ(a.dfdx().tostring(), "99y2z3");
}

TEST(monom, Test23){
	monom a(1, 2, 3, 99);
	EXPECT_EQ(a.dfdy().tostring(), "198xyz3");
}

TEST(monom, Test24){
	monom a(1, 2, 3, 99);
	EXPECT_EQ(a.dfdz().tostring(), "297xy2z2");
}


TEST(monom, Test25){
	monom a(0, 0, 0, 24);
	EXPECT_EQ(a.dfdx().tostring(), "");
	EXPECT_EQ(a.dfdy().tostring(), "");
	EXPECT_EQ(a.dfdz().tostring(), "");
}

TEST(monom, Test26){
	ASSERT_ANY_THROW(monom a(0, p, 0, 0));
}

TEST(monom, Test27){
	ASSERT_ANY_THROW(monom a(p * p * p, 0));
}

TEST(monom, Test28){
	monom a(p / 2 + 1, 0, 0, 1);
	monom b(p / 2, 0, 0, 1);
	ASSERT_ANY_THROW(a * b);
}

TEST(Polynom, Test1){
	Polynom a("xyz + x2 + z2");
	EXPECT_EQ(a.Tostring(), "x2 + xyz + z2");
}

TEST(Polynom, Test2){
	Polynom a("x99 + xy2z + z2 + 6 + xy");
	EXPECT_EQ(a.Tostring(), "x99 + xy2z + xy + z2 + 6");
}

TEST(Polynom, Test3){
	Polynom a("x2 - x2");
	EXPECT_EQ(a.Tostring(), "0");
}

TEST(Polynom, Test4){
	Polynom a("12355x12 - x12 + zyx7");
	EXPECT_EQ(a.Tostring(), "12354x12 + x7yz");
}

TEST(Polynom, Test5){
	Polynom a("12355x12 - x12 + zyx7");
	Polynom b = a;
	EXPECT_EQ(b.Tostring(), "12354x12 + x7yz");
}

TEST(Polynom, Test6){
	Polynom a("12355x12 - x12 + zyx7");
	Polynom b("x71");
	b = a;
	EXPECT_EQ(b.Tostring(), "12354x12 + x7yz");
}

TEST(Polynom, Test7){
	Polynom a("12355x12 - x12 + zyx7");
	Polynom b("x12 + z7xy - 12355x12 - x7yz");
	b.merge(a);
	EXPECT_EQ(b.Tostring(), "xyz7");
	EXPECT_EQ(a.Tostring(), "0");
}

TEST(Polynom, Test8){
	Polynom a("12355x12 - x12 + zyx7");
	Polynom b("x12 + z7xy - 12355x12 - x7yz");
	string c = b.Tostring();
	a += b;
	EXPECT_EQ(b.Tostring(), "-12354x12 - x7yz + xyz7");
	EXPECT_EQ(a.Tostring(), "xyz7");
}

TEST(Polynom, Test9){
	Polynom b("x12 + z7xy - 12355x12 - x7yz");
	Polynom a = -b;
	EXPECT_EQ(b.Tostring(), "-12354x12 - x7yz + xyz7");
	EXPECT_EQ(a.Tostring(), "12354x12 + x7yz - xyz7");
}

TEST(Polynom, Test10){
	Polynom a("x2 + z2");
	Polynom b("y2");
	a -= b;
	EXPECT_EQ(a.Tostring(), "x2 - y2 + z2");
	EXPECT_EQ(b.Tostring(), "y2");
}

TEST(Polynom, Test11){
	Polynom a("x2 + z2");
	Polynom b("y2");
	EXPECT_EQ((a + b).Tostring(), "x2 + y2 + z2");
	EXPECT_EQ(a.Tostring(), "x2 + z2");
	EXPECT_EQ(b.Tostring(), "y2");
}

TEST(Polynom, Test12){
	Polynom a("x2 + y2");
	Polynom b("y2 + x2");
	EXPECT_EQ((a - b).Tostring(), "0");
	EXPECT_EQ(a.Tostring(), "x2 + y2");
}

TEST(Polynom, Test13){
	Polynom a("x2 + y2");
	Polynom b("y2 + x2");
	a *= b;
	EXPECT_EQ(a.Tostring(), "x4 + 2x2y2 + y4");
	EXPECT_EQ(b.Tostring(), "x2 + y2");
}

TEST(Polynom, Test14){
	Polynom a("x2 + y2 + z2");
	Polynom b("x");
	a *= b;
	EXPECT_EQ(a.Tostring(), "x3 + xy2 + xz2");
	EXPECT_EQ(b.Tostring(), "x");
}

TEST(Polynom, Test15){
	Polynom a("x2 + y2 + z2");
	Polynom b("x + 6");
	Polynom c = a * b;
	EXPECT_EQ(c.Tostring(), "x3 + 6x2 + xy2 + xz2 + 6y2 + 6z2");
	EXPECT_EQ(a.Tostring(), "x2 + y2 + z2");
	EXPECT_EQ(b.Tostring(), "x + 6");
}
