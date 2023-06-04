
#pragma once
#include <iostream>
#include "stdio.h"
#include "fstream"
#include "mono.h"

#include <string>


class polinom {
	monom* start;
	monom* end;

	void purge() {
		if (isempty())return;
		monom* tmp = start;
		while (tmp->next != nullptr) {
			monom* del = tmp;
			tmp = tmp->next;
			delete del;
		}
		delete tmp;

		start = nullptr;

	}


	void push_end(monom _m) {

		if (isempty()) {
			push(_m);
			return;
		}
		monom* val = new monom(_m.c, _m.pow);
		monom* tmp = end;
		end = val;
		tmp->next = val;
	}
public:
		 void clean() {

			 polinom res;
			 monom* tmp = start;
			 while (tmp != nullptr) {
				 if (tmp->c != 0)res.push_end(*tmp);
				 tmp = tmp->next;
			 }
			 *this = res;
		}
	bool isempty() {
		if (start == nullptr) {
			return 1;
		}
		return 0;
	}
	polinom() {
		start = nullptr;
		end = nullptr;
	}

	~polinom() {
		purge();
		delete start;
	}
	polinom(const polinom& poli) {
		start = nullptr;
		if (&poli == this) { return; }

		if (poli.start == nullptr) { purge(); return; }

		monom* tmp = poli.start;
		while (tmp->next != nullptr) {
			monom n(tmp->c, tmp->pow);
			push(n);
			tmp = tmp->next;
		};
		monom n(tmp->c, tmp->pow);
		push(n);
	}
	void push(monom _m) {

		if (_m.getc() == 0) { return; }
		monom* val = new monom(_m.c, _m.pow);
		if (isempty()) {
			start = val;
			end = val;
			return;
		}
		if (start->getpow() > _m.getpow()) {
			val->next = start;
			start = val;
			return;
		}
		monom* tmp = start;
		monom* prev = tmp;
		while (tmp->next != nullptr) {
			if (tmp->getpow() == _m.getpow()) {
				tmp->setc(tmp->getc() + _m.getc());
				if (tmp->getc() == 0) {
					if (tmp == start) {
						monom* del = tmp;
						tmp = tmp->next;
						start = tmp;
						delete del;
					}
					else {
						monom* del = tmp;
						tmp = tmp->next;
						prev->next = tmp;
						delete del;
					}
				}
				return;
			}
			if (tmp->next->getpow() > _m.getpow()) {
				val->next = tmp->next;
				tmp->next = val;
				//clean();
				return;
			}
			prev = tmp;
			tmp = tmp->next;

		}
		if (tmp->getpow() == _m.getpow()) {
			tmp->setc(tmp->getc() + _m.getc());
			if (tmp->getc() == 0) {
				if (tmp == start) {
					monom* del = tmp;
					tmp = tmp->next;
					start = tmp;
					delete del;
				}
				else {
					monom* del = tmp;
					tmp = tmp->next;
					prev->next = tmp;
					delete del;
				}
			}
			return;
		}
		val->next = tmp->next;
		tmp->next = val;
		end = val;


	}

	friend ostream& operator <<(ostream& out, const polinom& m) {
		
		monom* tmp = m.start;

		if (tmp == nullptr) { out << "0" << endl; return out; }

		while (tmp->next != nullptr) {
			//if(tmp->c!=0)
			out << *tmp << "+";
			tmp = tmp->next;
		}
		//if (tmp->c != 0)
		out << *tmp;
		return out;

	}
	void save(string filename) {
		std::ofstream out;
		out.open(filename);
		if (out.is_open())
		{
			out << *this;
		}
	}
	bool operator==(polinom poli) {
		monom* tmp1 = start;
		monom* tmp2 = poli.start;
		while ((tmp1->next != nullptr) && (tmp2->next != nullptr)) {
			if (*tmp1 != *tmp2) { return false; }
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
		if (*tmp1 != *tmp2) { return false; }
		return true;
	}

	polinom & operator=(const polinom &poli) {
		if (&poli == this) { return *this; }
		if (poli.start == nullptr) { purge(); return *this; }
		purge();
		monom* tmp = poli.start;
		while (tmp->next != nullptr) {
			monom n(tmp->c, tmp->pow);
			if(tmp->c!=0)
			this->push(n);
			tmp = tmp->next;
		}
		monom n(tmp->c, tmp->pow);
		this->push(n);
		return *this;
	}
	polinom operator+(polinom poli) {
		polinom res;
		monom* tmp1 = this->start;
		monom* tmp2 = poli.start;
		
		if (this->isempty()) { return poli; }
		if (poli.isempty()) { return *this; }
		bool f1 = 1, f2 = 1;
		while (f2 || f1) {
			if ((tmp1->pow == tmp2->pow)) {
				monom n(tmp1->c + tmp2->c, tmp1->pow);
				if (n.getc() != 0)res.push_end(n);
				if (tmp1->next != nullptr) tmp1 = tmp1->next; else f1 = 0;
				if (tmp2->next != nullptr) tmp2 = tmp2->next; else f2 = 0;
			}
			else {
				if ((tmp1->pow < tmp2->pow) && (f1 == 1)) {
					monom n(tmp1->c, tmp1->pow);
					res.push_end(n);
					if (tmp1->next != nullptr) tmp1 = tmp1->next;else f1 = 0;
				}
				else {
					if (f2 == 1) {
						monom n(tmp2->c, tmp2->pow);
						res.push_end(n);
						if (tmp2->next != nullptr) tmp2 = tmp2->next;else f2 = 0;
					}
					else {
						monom n(tmp1->c, tmp1->pow);
						res.push_end(n);
						if (tmp1->next != nullptr) tmp1 = tmp1->next;else f1 = 0;
					}
				}
			}


		}
		res.clean();
		return res;
	}

	polinom operator* (const polinom poli) {
		polinom res;
		monom* tmp = poli.start;
		while (tmp != nullptr) {
			monom* tmp2 = start;
			while (tmp2 != nullptr) {
				monom n = *tmp * *tmp2;
				res.push(n);

				tmp2 = tmp2->next;
			}
			tmp = tmp->next;
		}
		return res;
	}
	friend istream& operator>>(istream& istr, polinom& poli)
	{
		poli.purge();
		string tmp;
		istr >> tmp;
		char const sep = '+';
		int size = tmp.size();
		string elem = "";
		for (int i = 0;i < size;i++) {
			if (tmp[i] == sep) {
				monom m(elem);
				poli.push(m);
				elem = "";
			}
			else {
				elem += tmp[i];
			}
		}
		monom m(elem);
		poli.push(m);
		return istr;
	}
};