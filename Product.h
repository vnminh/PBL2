#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include "String.h"
#include "DList.h"
class DetailProduct;
class Product
{
	friend void OutputTable(const DList<Product *> &, const int &);
	friend void OutputDetail(const Product *);
	friend void InsertProduct(DList<Product *> &, const String &, const String &, const String&, DetailProduct *);
	private:
		String ID;
		String Name;
		String XS;
		DList<DetailProduct*> List;
	public:
		Product(const String&, const String&, const String&);
		~Product();
		void AddDetailProduct(DetailProduct*);
		DetailProduct* FindDetailProduct(const String&) const;
		String GetID() const;
		String GetName() const;
		String GetXS() const;
};
#endif