#ifndef DETAILPRODUCT_H
#define DETAILPRODUCT_H
#include <iostream>
#include "String.h"
#include "Date.h"
#include "DList.h"
class Product;
class DetailBill;
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
		bool isDeleted;
		Product *ptrP;
		DList<DetailBill*> List;
		void ConnectProduct(Product *);
	public:
		DetailProduct(const String&, const Date&, const Date&, const Date&, const int&, const int&);
		~DetailProduct();
		void AddDetailBill(DetailBill *);
		void Deduct(const int);
		bool SoldOut() const;
		String GetID() const;
		Date GetNN() const;
		Date GetNSX() const;
		Date GetHSD() const;
		int GetPrice() const;
		int GetSL() const;
		bool Deleted() const;
		void Delete();
		String GetProductName() const;
		String GetProductID() const;
		virtual int Calculate(const int&) const;
		friend class Product;
};
#endif