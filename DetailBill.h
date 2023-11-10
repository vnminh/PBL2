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
public:
	DetailBill(DetailProduct *, const int &);
	void ConnectBill(Bill*);
	int GetSL() const;
	String GetNameProduct() const;
	String GetIDDetailProduct() const;
	int GetPrice() const;
};
#endif