#include "DNode.cpp"
#include "DList.cpp"
#include "Product.h"
#include <iostream>
using namespace std;
Product::Product(const String &id, const String &n, const String &ncc)
	:ID(id), Name(n), NCC(ncc)
{}
Product::~Product()
{}
void Product::AddLo(const LoHang & l) 
{
	this->List.InsertLast(l);
}
ostream& operator<<(ostream& out, const Product& p)
{
	out << p.ID << ' ' << p.Name << ' ' << p.NCC << '\n';
	out << p.List;
	return out;
}