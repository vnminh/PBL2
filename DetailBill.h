#ifndef DETAILBILL_H
#define DETAILBILL_H
#include "String.h"
class DetailProduct;
class Bill;
class DetailBill
{
private:
	int SL;
	DetailProduct * ptrDP;
	Bill * ptrB;
	void ConnectBill(Bill*);
public:
	DetailBill(DetailProduct *, const int &);
	int GetSL() const;
	String GetNameProduct() const;
	String GetIDDetailProduct() const;
	int GetPrice() const;
	int Pay() const;
	friend class Bill;
};
#endif