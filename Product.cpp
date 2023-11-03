#include "DNode.cpp"
#include "DList.cpp"
#include "Product.h"
#include <iostream>
using namespace std;
Product::Product(const String &id, const String &n, const String &xs)
	:ID(id), Name(n), XS(xs)
{}
Product::~Product()
{}
void Product::AddLo(const LoHang & l) 
{
	this->List.InsertLast(l);
}
ostream& operator<<(ostream& out, const Product& p)
{
	out << p.ID << ' ' << p.Name << ' ' << p.XS << '\n';
	out << p.List;
	return out;
}
String Product::GetID() const
{
	return this->ID;
}
String Product::GetName() const
{
	return this->Name;
}
String Product::GetXS() const
{
	return this->XS;
}
void InsertProduct(DList<Product> &List, Product& p, const LoHang& lo)
{
	DNode<Product> * ptr = List.FindFirstMatch(p.ID, &Product::GetID);
	if (ptr == NULL){
		p.AddLo(lo);
		List.InsertLast(p);
	}
	else
	{
		(ptr->data).AddLo(lo);
	}
}