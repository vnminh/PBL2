#include "DetailWeightProduct.h"
#include "Product.h"
int DetailWeightProduct::CalUnit = 100;
DetailWeightProduct::DetailWeightProduct(const String& id, const Date& nn, const Date& nsx, const Date& hsd, const int& price, const int& sl)
	:DetailProduct(id, nn, nsx, hsd, price, sl)
{}
DetailWeightProduct::~DetailWeightProduct()
{}
int DetailWeightProduct::Calculate(const int& kl) const
{
	return DetailProduct::Calculate(kl)*1.0 / (this->CalUnit);
}
bool DetailWeightProduct::SLWarn() const
{
	return (this->ptrP)->GetSL() <= 1000;
}
void DetailWeightProduct::SetCalUnit(const int &unit)
{
	DetailWeightProduct::CalUnit = unit;
}