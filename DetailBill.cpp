#include "DetailBill.h"
#include "DetailProduct.h"
#include "Product.h"
using namespace std;
DetailBill::DetailBill(DetailProduct * ptr, const int & sl)
	:SL(sl), ptrDP(ptr), ptrB(nullptr)
{}
void DetailBill::ConnectBill(Bill* ptr)
{
	this->ptrB = ptr;
}
int DetailBill::GetSL() const
{
	return this->SL;
}
String DetailBill::GetNameProduct() const
{
	return (this->ptrDP)->GetProductName();
}
String DetailBill::GetIDDetailProduct() const
{
	return ((this->ptrDP)->GetProductID()) + ((this->ptrDP)->GetID());
}
int DetailBill::GetPrice() const
{
	return (this->ptrDP)->GetPrice();
}