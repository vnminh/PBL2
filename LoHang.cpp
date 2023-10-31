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
