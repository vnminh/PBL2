#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include "String.h"
#include "LoHang.h"
#include "DList.h"
class Product
{
	friend void InsertProduct(DList<Product> &, Product&, const LoHang&);
	friend std::ostream& operator<<(std::ostream&, const Product&);
	private:
		String ID;
		String Name;
		String XS;
		DList<LoHang> List;
	public:
		Product(const String&, const String&, const String&);
		~Product();
		void AddLo(const LoHang&);
		String GetID() const;
		String GetName() const;
		String GetXS() const;
};
#endif