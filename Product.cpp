#include "DNode.cpp"
#include "DList.cpp"
#include "Product.h"
#include "Output.h"
#include <iostream>
using namespace std;
Product::Product(const String &id, const String &n, const String &xs)
	:ID(id), Name(n), XS(xs)
{}
Product::~Product()
{}
void Product::AddDP(const DetailProduct & dp)
{
	DNode<DetailProduct> * Newptr = new DNode<DetailProduct>(dp);
	(Newptr->data).ptrP = this;
	this->List.InsertLast(Newptr);
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
void InsertProduct(DList<Product> &List, const Product& p, const DetailProduct& dp)
{
	DNode<Product> * ptr = FindFirstMatch(List,p.ID, &Product::GetID);
	if (ptr == nullptr){
		DNode<Product> * Newptr = new DNode<Product>(p);
		(Newptr->data).AddDP(dp);
		List.InsertLast(Newptr);
	}
	else
	{
		(ptr->data).AddDP(dp);
	}
}
void OutputTable(const DList<DNode<Product>*> & List, const int& num)
{
	if (num == 0)
	{
		mnu::LeftPrint("Khong tim thay"); cout << endl;
		return;
	}
	const int w = 10;
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	cout << '|'; mnu::CenterPrint("STT", w);
	cout << '|'; mnu::CenterPrint("ID", w);
	cout << '|'; mnu::CenterPrint("TEN SAN PHAM", mnu::WIDTH - 5 - 4 * w);
	cout << '|'; mnu::CenterPrint("XUAT XU", 2 * w); cout << '|' << '\n';
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	const DNode<DNode<Product>*> *curPtr = List.GetFirstElement();
	for (int i = 1; i <= num; i++)
	{
		cout << '|'; mnu::CenterPrint(String::to_string(i), w);
		cout << '|'; mnu::CenterPrint(((curPtr->data)->data).ID, w);
		cout << '|'; mnu::CenterPrint(((curPtr->data)->data).Name, mnu::WIDTH - 5 - 4 * w);
		cout << '|'; mnu::CenterPrint(((curPtr->data)->data).XS, 2 * w); cout << '|' << '\n';
		cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
		curPtr = curPtr->next;
	}
}
void OutputDetail(const Product & p)
{
	cout << "ID           :" << p.ID << endl;
	cout << "Ten san pham :" << p.Name << endl;
	cout << "Xuat xu      :" << p.XS << endl;
	const int w1 = 10, w2 = (mnu::WIDTH - 8 - 4 * w1) / 3;
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	cout << '|'; mnu::CenterPrint("STT", w1);
	cout << '|'; mnu::CenterPrint("ID Lo", w1);
	cout << '|'; mnu::CenterPrint("Ngay nhap", w2 + 1);
	cout << '|'; mnu::CenterPrint("NSX", w2);
	cout << '|'; mnu::CenterPrint("HSD", w2);
	cout << '|'; mnu::CenterPrint("Gia", w1);
	cout << '|'; mnu::CenterPrint("So luong", w1); cout << '|' << '\n';
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	const DNode<DetailProduct> *curPtr = p.List.GetFirstElement();
	int cnt = 1;
	while (curPtr != nullptr)
	{
		cout << '|'; mnu::CenterPrint(String::to_string(cnt), w1);
		cout << '|'; mnu::CenterPrint((curPtr->data).GetID(), w1);
		cout << '|'; mnu::CenterPrint((curPtr->data).GetNN().to_string(), w2 + 1);
		cout << '|'; mnu::CenterPrint((curPtr->data).GetNSX().to_string(), w2);
		cout << '|'; mnu::CenterPrint((curPtr->data).GetHSD().to_string(), w2);
		cout << '|'; mnu::CenterPrint(String::to_string((curPtr->data).GetPrice()), w1);
		cout << '|'; mnu::CenterPrint(String::to_string((curPtr->data).GetSL()), w1); cout << '|' << '\n';
		cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
		cnt++;
		curPtr = curPtr->next;
	}
}