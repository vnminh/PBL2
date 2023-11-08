#ifndef DETAILPRODUCT_H
#define DETAILPRODUCT_H
#include <iostream>
#include "String.h"
#include "Date.h"
class Product;
class DetailProduct
{
	friend class Product;
	private:
		String ID;
		Date NN;
		Date NSX;
		Date HSD;
		int Price;
		int SL;
		Product *ptrP;
	public:
		DetailProduct(const String&, const Date&, const Date&, const Date&, const int&, const int&);
		~DetailProduct();
		String GetID() const;
		Date GetNN() const;
		Date GetNSX() const;
		Date GetHSD() const;
		int GetPrice() const;
		int GetSL() const;
};
#endif