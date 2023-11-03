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
void OutputTable(const DList<Product> & List, const int& num)
{
	if (num == 0)
	{
		cout << "Khogn tim thay";
		return;
	}
	const int w = 10;
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	cout << '|'; mnu::CenterPrint("STT", w);
	cout << '|'; mnu::CenterPrint("ID", w);
	cout << '|'; mnu::CenterPrint("TEN SAN PHAM", mnu::WIDTH - 5 - 4 * w);
	cout << '|'; mnu::CenterPrint("XUAT XU", 2 * w); cout << '|' << '\n';
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	const DNode<Product> *curPtr = List.GetFirstElement();
	for (int i = 1; i <= num; i++)
	{
		cout << '|'; mnu::CenterPrint(String(i), w);
		cout << '|'; mnu::CenterPrint((curPtr->data).ID, w);
		cout << '|'; mnu::CenterPrint((curPtr->data).Name, mnu::WIDTH - 5 - 4 * w);
		cout << '|'; mnu::CenterPrint((curPtr->data).XS, 2 * w); cout << '|' << '\n';
		cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	}
}
void OutputDetail(const DList<Product> & List, const int & index)
{
	const DNode<Product> *ptr = List.FindIndex(index);
	cout << "ID           :" << (ptr->data).ID << endl;
	cout << "Ten san pham :" << (ptr->data).Name << endl;
	cout << "Xuat xu      :" << (ptr->data).XS << endl;
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
	const DNode<LoHang> *curPtr = (ptr->data).List.GetFirstElement();
	int cnt = 1;
	while (curPtr != NULL)
	{
		cout << '|'; mnu::CenterPrint(String(cnt), w1);
		cout << '|'; mnu::CenterPrint((curPtr->data).GetID(), w1);
		cout << '|'; mnu::CenterPrint((curPtr->data).GetNN().show(), w2 + 1);
		cout << '|'; mnu::CenterPrint((curPtr->data).GetNSX().show(), w2);
		cout << '|'; mnu::CenterPrint((curPtr->data).GetHSD().show(), w2);
		cout << '|'; mnu::CenterPrint((curPtr->data).GetPrice(), w1);
		cout << '|'; mnu::CenterPrint((curPtr->data).GetSL(), w1); cout << '|' << '\n';
		cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
		cnt++;
		curPtr = curPtr->next;
	}
}