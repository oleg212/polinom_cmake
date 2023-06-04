
#pragma once
#include <iostream>
#include "stdio.h"
#include "fstream"
//#include "gtest/gtest.h"
#include <string>
#define powint  20
using namespace std;

string str_pars(string tmp, int _i) {
	string elem = "";
	char const sep = '|';
	int i = _i;
	while (tmp[i] != sep) {

		elem += tmp[i];
		i++;

	}
	return elem;
}

struct monom {
	int pow;
	int c;

	monom* next;

public:
	monom(int _c = 0, int _pow = 0) {
		pow = (_pow);
		c = _c;
		next = nullptr;
	}
	monom(int _c, int s1, int s2, int s3) {
		if ((s1 > (powint / 2)) || (s2 > (powint / 2)) || (s3 > (powint / 2))) { throw - 1; }

		pow = (s1 + powint / 2) * powint * powint + (s2 + powint / 2) * powint + (s3 + powint / 2);
		c = _c;
		next = nullptr;
	}
	int gets1()
	{
		int s1 = pow / (powint * powint) - powint / 2;
		return s1;
	}
	int gets2()
	{
		int s2 = (pow % (powint * powint) - powint / 2) / powint - powint / 2;
		return s2;
	}
	int gets3()
	{
		int s3 = (pow % powint) - powint / 2;
		return s3;
	}
	void operator=(monom m) {
		c = m.getc();
		pow = m.getpow();
	}
	bool operator==(monom m) {
		if((c == m.getc())&&(pow == m.getpow()))return true;
		return false;
	}
	bool operator!=(monom m) {
		if ((c == m.getc()) && (pow == m.getpow()))return false;
		return true;
	}
	monom operator*(monom m) {
		monom res;
 		res.c = m.c * c;
		int s1 = m.gets1() + gets1();
		int s2 = m.gets2() + gets2();
		int s3 = m.gets3() + gets3();
		res.pow = (s1 + powint / 2) * powint * powint + (s2 + powint / 2) * powint + (s3 + powint / 2);
		return res;
	}
	void setpow(int _pow) {
		if (_pow > powint * powint * powint + powint * powint + powint) { throw - 1; }
		pow = _pow;
	}
	void setc(int _c) {
		c = _c;
	}
	void setpow(int s1, int s2, int s3) {
		pow = (s1 + powint / 2) * powint * powint + (s2 + powint / 2) * powint + (s3 + powint / 2);
	}



	int getpow() { return pow; }
	int getc() { return c; }
	friend ostream& operator <<(ostream& out, const monom& m) {
		int s3 = (m.pow % powint) - powint / 2;
		int s2 = (m.pow % (powint * powint) - powint / 2) / powint - powint / 2;
		int s1 = m.pow / (powint * powint) - powint / 2;
		out << m.c << "|x^" << s1 << "|y^" << s2 << "|z^" << s3 << "|";
		return out;
	}

	monom(string tmp)
	{
		char const sep = '|';
		int size = tmp.size();
		string elem = "";
		int i = 0;
		int s1, s2, s3;
		string s;
		s = str_pars(tmp, i);
		c = atoi(s.c_str());
		i += s.length() + 3;

		s = str_pars(tmp, i);
		s1 = atoi(s.c_str());
		i += s.length() + 3;

		s = str_pars(tmp, i);
		s2 = atoi(s.c_str());
		i += s.length() + 3;

		s = str_pars(tmp, i);
		s3 = atoi(s.c_str());

		pow = (s1 + powint / 2) * powint * powint + (s2 + powint / 2) * powint + (s3 + powint / 2);
		next = nullptr;
	}
};