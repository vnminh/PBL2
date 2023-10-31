#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include "String.h"
#include "LoHang.h"
#include "DList.h"
class Product
{
	friend std::ostream& operator<<(std::ostream&, const Product&);
	private:
		String ID;
		String Name;
		String NCC;
		DList<LoHang> List;
	public:
		Product(const String&, const String&, const String&);
		~Product();
		void AddLo(const LoHang&);
};
#endif