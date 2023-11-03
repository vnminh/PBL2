#ifndef LOHANG_H
#define LOHANG_H
#include <iostream>
#include "String.h"
#include "Date.h"
class LoHang
{
	friend std::ostream& operator<<(std::ostream&, const LoHang &);
	private:
		String ID;
		Date NN;
		Date NSX;
		Date HSD;
		int Price;
		int SL;
	public:
		LoHang(const String&, const Date&, const Date&, const Date&, const int&, const int&);
		~LoHang();
		String GetID() const;
		Date GetNN() const;
		Date GetNSX() const;
		Date GetHSD() const;
		int GetPrice() const;
		int GetSL() const;
};
#endif