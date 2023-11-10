#include "Product.h"
#include "Output.h"
#include "DList.h"
#include "DetailProduct.h"
#include <iostream>
using namespace std;
Product::Product(const String &id, const String &n, const String &xs)
	:ID(id), Name(n), XS(xs)
{}
Product::~Product()
{}
void Product::AddDetailProduct( DetailProduct * ptr)
{
	DNode<DetailProduct*> * newptr = new DNode<DetailProduct *> (ptr);
	(this->List).InsertLast(newptr);
}
DetailProduct* Product::FindDetailProduct(const String&id) const
{
	DetailProduct* ptr = FindFirstMatch(this->List, id, &DetailProduct::GetID);
	return ptr;
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
void InsertProduct(DList<Product *> &List, const String &id_p,const String &name,const String &xs,  DetailProduct *ptrDP )
{
	Product *ptrP = FindFirstMatch(List, id_p, &Product::GetID);
	if (ptrP == nullptr)
	{
		DNode<Product *> * Newptr = new DNode<Product *>(new Product(id_p, name, xs));
		(Newptr->data)->AddDetailProduct(ptrDP);
		ptrDP->ConnectProduct(Newptr->data);
		List.InsertLast(Newptr);
	}
	else
	{
		ptrP->AddDetailProduct(ptrDP);
		ptrDP->ConnectProduct(ptrP);
	}
}
void OutputTable(const DList<Product*> & list, const int& num)
{
	if (num == 0)
	{
		mnu::PadLeftPrint("Khong tim thay\n");
		return;
	}
	const int w = 10;
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	cout << '|'; mnu::CenterPrint("STT", w);
	cout << '|'; mnu::CenterPrint("ID", w);
	cout << '|'; mnu::CenterPrint("TEN SAN PHAM", mnu::WIDTH - 5 - 4 * w);
	cout << '|'; mnu::CenterPrint("XUAT XU", 2 * w); cout << '|' << '\n';
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	const DNode<Product*> *curPtr = list.GetFirstElement();
	for (int i = 1; i <= num; i++)
	{
		cout << '|'; mnu::CenterPrint(String::to_string(i), w);
		cout << '|'; mnu::CenterPrint((curPtr->data)->ID, w);
		cout << '|'; mnu::CenterPrint((curPtr->data)->Name, mnu::WIDTH - 5 - 4 * w);
		cout << '|'; mnu::CenterPrint((curPtr->data)->XS, 2 * w); cout << '|' << '\n';
		cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
		curPtr = curPtr->next;
	}
}
void OutputDetail(const Product * ptrP)
{
	if (ptrP == nullptr)
	{
		mnu::PadLeftPrint("Khong tim thay\n");
		return;
	}
	cout << "ID           :" << ptrP->ID << endl;
	cout << "Ten san pham :" << ptrP->Name << endl;
	cout << "Xuat xu      :" << ptrP->XS << endl;
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
	const DNode<DetailProduct *> *curPtr = (ptrP->List).GetFirstElement();
	int cnt = 1;
	while (curPtr != nullptr)
	{
		cout << '|'; mnu::CenterPrint(String::to_string(cnt), w1);
		cout << '|'; mnu::CenterPrint((curPtr->data)->GetID(), w1);
		cout << '|'; mnu::CenterPrint((curPtr->data)->GetNN().to_string(), w2 + 1);
		cout << '|'; mnu::CenterPrint((curPtr->data)->GetNSX().to_string(), w2);
		cout << '|'; mnu::CenterPrint((curPtr->data)->GetHSD().to_string(), w2);
		cout << '|'; mnu::CenterPrint(String::to_string((curPtr->data)->GetPrice()), w1);
		cout << '|'; mnu::CenterPrint(String::to_string((curPtr->data)->GetSL()), w1); cout << '|' << '\n';
		cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
		cnt++;
		curPtr = curPtr->next;
	}
}