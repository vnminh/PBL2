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
	friend bool InsertProduct(DList<Product *> &, Product *, DetailProduct *);
	friend void OutputDetailProduct(const DList<DetailProduct *>&, std::ostream&);
	private:
		String ID;
		String Name;
		String XS;
		int NumDP;
		bool isDeleted;
		DList<DetailProduct*> List;
	public:
		Product(const String&, const String&, const String&);
		~Product();
		void AddDetailProduct(DetailProduct*);
		DetailProduct* FindDetailProduct(const String&) const;
		int GetNumDP() const;
		String GetID() const;
		String GetName() const;
		String GetXS() const;
		const DList<DetailProduct*>& GetDPList() const;
		void Delete();
		bool Deleted() const;
		void DeleteDP();
};
#endif