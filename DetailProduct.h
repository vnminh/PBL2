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
		Product *ptrP;
		DList<DetailBill*> List;
	public:
		DetailProduct(const String&, const Date&, const Date&, const Date&, const int&, const int&);
		~DetailProduct();
		void ConnectProduct(Product *);
		void AddDetailBill(DetailBill *);
		void Deduct(const int &);
		bool SoldOut() const;
		String GetID() const;
		Date GetNN() const;
		Date GetNSX() const;
		Date GetHSD() const;
		int GetPrice() const;
		int GetSL() const;
		String GetProductName() const;
		String GetProductID() const;
};
#endif