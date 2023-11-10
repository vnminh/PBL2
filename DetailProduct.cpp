#include "DetailProduct.h"
#include "Product.h"
#include <iostream>
using namespace std;
DetailProduct::DetailProduct(const String& id, const Date& nn, const Date& nsx, const Date& hsd, const int& price, const int& sl)
	:ID(id), NN(nn), NSX(nsx), HSD(hsd), Price(price), SL(sl), ptrP(nullptr)
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
void DetailProduct::Deduct(const int & num)
{
	(this->SL) -= num;
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
String DetailProduct::GetProductName() const
{
	return (this->ptrP)->GetName();
}
String DetailProduct::GetProductID() const
{
	return (this->ptrP)->GetID();
}