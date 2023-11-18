#include "DetailProduct.h"
#include "Product.h"
#include <iostream>
using namespace std;
DetailProduct::DetailProduct(const String& id, const Date& nn, const Date& nsx, const Date& hsd, const int& price, const int& sl)
	:ID(id), NN(nn), NSX(nsx), HSD(hsd), Price(price), SL(sl),isDeleted(false), ptrP(nullptr)
{}
DetailProduct::~DetailProduct()
{}
void DetailProduct::ConnectProduct(Product * ptr)
{
	this->ptrP = ptr;
}
void DetailProduct::AddDetailBill(DetailBill *ptr)
{
	(this->List).InsertLast(new DNode<DetailBill*>(ptr));
}
void DetailProduct::Deduct(const int num)
{
	(this->SL) -= num;
	if (this->SL <= 0)
	{
		isDeleted = true;
	}
	(this->ptrP)->Deduct(num);
}
bool DetailProduct::SoldOut() const
{
	return (this->SL) == 0;
}
String DetailProduct::GetID() const
{
	return this->ID;
}
Date DetailProduct::GetNN() const
{
	return this->NN;
}
Date DetailProduct::GetNSX() const
{
	return this->NSX;
}
Date DetailProduct::GetHSD() const
{
	return this->HSD;
}
int DetailProduct::GetPrice() const
{
	return this->Price;
}
int DetailProduct::GetSL() const
{
	return this->SL;
}
bool DetailProduct::Deleted() const
{
	return this->isDeleted;
}
String DetailProduct::GetProductName() const
{
	return (this->ptrP)->GetName();
}
String DetailProduct::GetProductID() const
{
	return (this->ptrP)->GetID();
}
void DetailProduct::Delete()
{
	this->Deduct(this->SL);
}
int DetailProduct::Calculate(const int & num) const
{
	return num*(this->Price);
}