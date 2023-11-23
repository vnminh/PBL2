#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include "String.h"
#include "DList.h"
class DetailProduct;
class Product
{
	friend void OutputProductFile(const String &, const DList<Product*>&);
	friend DList<DetailProduct*>* OutOfExpiration(const DList<Product*>&, const int&);
	friend void OutputTable(const DList<Product *> &, std::ostream&);
	friend void OutputDetail(const Product *, std::ostream&);
	friend void InsertProduct(DList<Product *> &, const String &, const String &, const String&, DetailProduct *);
	friend void OutputDetailProduct(const DList<DetailProduct *>&, std::ostream&);
	private:
		String ID;
		String Name;
		String XS;
		int SL;
		bool isDeleted;
		DList<DetailProduct*> List;
	public:
		Product(const String&, const String&, const String&);
		~Product();
		void AddDetailProduct(DetailProduct*);
		DetailProduct* FindDetailProduct(const String&) const;
		int GetSL() const;
		String GetID() const;
		String GetName() const;
		String GetXS() const;
		bool Deleted() const;
		void Deduct(const int);
};
#endif