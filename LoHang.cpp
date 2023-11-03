#include "LoHang.h"
#include <iostream>
using namespace std;
LoHang::LoHang(const String& id, const Date& nn, const Date& nsx, const Date& hsd,const int& price, const int& sl)
	:ID(id), NN(nn), NSX(nsx), HSD(hsd),Price(price), SL(sl)
{}
LoHang::~LoHang()
{}
ostream& operator<<(ostream& out, const LoHang & lo)
{
	out << lo.ID << ' ' << lo.NN << ' ' << lo.NSX << ' ' << lo.HSD << ' ' << lo.Price << ' ' << lo.SL;
	return out;
}
String LoHang::GetID() const
{
	return this->ID;
}
Date LoHang::GetNN() const
{
	return this->NN;
}
Date LoHang::GetNSX() const
{
	return this->NSX;
}
Date LoHang::GetHSD() const
{
	return this->HSD;
}
int LoHang::GetPrice() const
{
	return this->Price;
}
int LoHang::GetSL() const
{
	return this->SL;
}