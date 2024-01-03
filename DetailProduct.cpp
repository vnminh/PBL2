#include "DetailProduct.h"
#include "Product.h"
#include "Exception.h"
#include <iostream>
using namespace std;
DetailProduct::DetailProduct(const String& id, const Date& nn, const Date& nsx, const Date& hsd, const int& sl)
	:ID(id), NN(nn), NSX(nsx), HSD(hsd), SL(sl),isDeleted(false), ptrP(nullptr)
{
	if (id.GetLength() != 4)
	{
		throw Exception("WRONG FORMAT FOR BATCH ID");
	}
	if (id[0] != 'L')
	{
		throw Exception("WRONG FORMAT FOR BATCH ID");
	}
	for (int i = 1; i <= 3; i++)
	{
		if (id[i]<'0' || id[i]>'9')
		{
			throw Exception("WRONG FORMAT FOR BATCH ID");
		}
	}
	if (sl <= 0)
	{
		throw Exception("INVALID VALUE FOR QUANTITY");
	}
}
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
	(this->ptrP)->Deduct(num);
}
void DetailProduct::Add(const int num)
{
	(this->SL) += num;
	(this->ptrP)->Add(num);
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
int DetailProduct::GetSL() const
{
	return this->SL;
}
int DetailProduct::GetPrice() const
{
	return this->ptrP->GetPrice();
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
bool DetailProduct::SLWarn() const
{
	return this->ptrP->GetSL() <= 10;
}
bool DetailProduct::HSDWarn() const
{
	return Today() + 7 >= this->HSD;
}
void DetailProduct::Delete()
{
	this->isDeleted=true;
	(this->ptrP)->DeleteDP(this);
}
int DetailProduct::Calculate(const int & num) const
{
	return num*(this->GetPrice());
}
String DetailProduct::GetSL_str() const
{
	return String::to_string(this->SL);
}
String DetailProduct::GetDonVi() const
{
	return String("");
}