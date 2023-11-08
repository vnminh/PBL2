#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include "String.h"
#include "DetailProduct.h"
#include "DList.h"
class Product
{
	friend void OutputTable(const DList<DNode<Product>*> &, const int &);
	friend void OutputDetail(const Product &);
	friend void InsertProduct(DList<Product> &, const Product &, const DetailProduct &);
	private:
		String ID;
		String Name;
		String XS;
		DList<DetailProduct> List;
	public:
		Product(const String&, const String&, const String&);
		~Product();
		void AddDP(const DetailProduct&);
		String GetID() const;
		String GetName() const;
		String GetXS() const;
};
#endif