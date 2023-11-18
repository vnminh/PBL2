#include "Product.h"
#include "Output.h"
#include "DList.h"
#include "DetailProduct.h"
#include <iostream>
using namespace std;
Product::Product(const String &id, const String &n, const String &xs)
	:ID(id), Name(n), XS(xs), isDeleted(false)
{}
Product::~Product()
{}
void Product::AddDetailProduct( DetailProduct * ptr)
{
	ptr->ConnectProduct(this);
	(this->List).InsertLast(new DNode<DetailProduct *>(ptr));
	this->SL += ptr->GetSL();
}
DetailProduct* Product::FindDetailProduct(const String&id) const
{
	DetailProduct* ptr = FindFirstMatch(this->List, id, &DetailProduct::GetID);
	return ptr;
} 
int Product::GetSL() const
{
	return this->SL;
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
bool Product::Deleted() const
{
	return this->isDeleted;
}
void Product::Deduct(const int num)
{
	this->SL -= num;
	if (this->SL <= 0)
	{
		this->isDeleted = true;
	}
}
void InsertProduct(DList<Product *> &List, const String &id_p,const String &name,const String &xs,  DetailProduct *ptrDP )
{
	Product *ptrP = FindFirstMatch(List, id_p, &Product::GetID);
	if (ptrP == nullptr)
	{
		DNode<Product *> * Newptr = new DNode<Product *>(new Product(id_p, name, xs));
		(Newptr->data)->AddDetailProduct(ptrDP);
		List.InsertLast(Newptr);
	}
	else
	{
		ptrP->AddDetailProduct(ptrDP);
	}
}
void OutputTable(const DList<Product*> & list)
{
	if (list.GetFirstElement() == nullptr)
	{
		mnu::PadLeftPrint("Khong tim thay\n");
		return;
	}
	const int w = 20;
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	cout << '|'; mnu::CenterPrint("STT", w);
	cout << '|'; mnu::CenterPrint("ID", w);
	cout << '|'; mnu::CenterPrint("TEN SAN PHAM", mnu::WIDTH - 5 - 4 * w);
	cout << '|'; mnu::CenterPrint("XUAT XU", 2 * w); cout << '|' << '\n';
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	const DNode<Product*> *curPtr = list.GetFirstElement();
	int i = 1;
	while (curPtr != nullptr)
	{
		cout << '|'; mnu::CenterPrint(String::to_string(i), w);
		cout << '|'; mnu::CenterPrint((curPtr->data)->ID, w);
		cout << '|'; mnu::CenterPrint((curPtr->data)->Name, mnu::WIDTH - 5 - 4 * w);
		cout << '|'; mnu::CenterPrint((curPtr->data)->XS, 2 * w); cout << '|' << '\n';
		cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
		curPtr = curPtr->next; i++;
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
	OutputDetailProduct(ptrP->List);
}
void OutputDetailProduct(const DList<DetailProduct *>& List)
{
	const int w1 = 13, w2 = (mnu::WIDTH - 8 - 4 * w1) / 3, w3 = mnu::WIDTH - 8 - 4 * w1 - 2 * w2;
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	cout << '|'; mnu::CenterPrint("STT", w1);
	cout << '|'; mnu::CenterPrint("ID Lo", w1);
	cout << '|'; mnu::CenterPrint("Ngay nhap", w3);
	cout << '|'; mnu::CenterPrint("NSX", w2);
	cout << '|'; mnu::CenterPrint("HSD", w2);
	cout << '|'; mnu::CenterPrint("Gia", w1);
	cout << '|'; mnu::CenterPrint("So luong", w1); cout << '|' << '\n';
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	const DNode<DetailProduct *> *curPtr = (List).GetFirstElement();
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
	if (cnt == 1)
	{
		cout << "|"; mnu::CenterPrint("Danh sach rong", mnu::WIDTH - 2); cout << "|\n";
		cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	}
}
DList<DetailProduct*> * OutOfExpiration(const DList<Product*>&List, const int &day)
{
	DList<DetailProduct*> * AnsList = new DList < DetailProduct* > ;
	Date checkdate = Today() + day;
	DNode<Product*> * curPtrP = List.GetFirstElement();
	while (curPtrP != nullptr)
	{
		Product *ptrP = curPtrP->data;
		if (!(ptrP->isDeleted))
		{
			DNode<DetailProduct*> *curPtrDP = (ptrP->List).GetFirstElement();
			while (curPtrDP != nullptr)
			{
				DetailProduct* ptrDP = curPtrDP->data;
				if (!(ptrDP->Deleted()))
				{
					if (ptrDP->GetHSD() <= checkdate)
					{
						AnsList->InsertLast(new DNode<DetailProduct*> (ptrDP));
					}
				}
				curPtrDP = curPtrDP->next;
			}
		}
		curPtrP = curPtrP->next;
	}
	return AnsList;
}
void OutputProductFile(const String &fname, const DList<Product*>& List)
{
	FILE *f_o;
	freopen_s(&f_o, fname, "w", stdout);
	const DNode<Product*> *curPtrP = List.GetFirstElement();
	int i = 1;
	while (curPtrP != nullptr)
	{
		Product *ptrP = curPtrP->data;
		if (!(ptrP->isDeleted))
		{
			cout << endl <<  i << endl;
			cout << "ID           :" << ptrP->ID << endl;
			cout << "Ten san pham :" << ptrP->Name << endl;
			cout << "Xuat xu      :" << ptrP->XS << endl;
			const int w1 = 13, w2 = (mnu::WIDTH - 8 - 4 * w1) / 3, w3 = mnu::WIDTH - 8 - 4 * w1 - 2 * w2;
			cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
			cout << '|'; mnu::CenterPrint("STT", w1);
			cout << '|'; mnu::CenterPrint("ID Lo", w1);
			cout << '|'; mnu::CenterPrint("Ngay nhap", w3);
			cout << '|'; mnu::CenterPrint("NSX", w2);
			cout << '|'; mnu::CenterPrint("HSD", w2);
			cout << '|'; mnu::CenterPrint("Gia", w1);
			cout << '|'; mnu::CenterPrint("So luong", w1); cout << '|' << '\n';
			cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
			DNode<DetailProduct*> *curPtrDP = (ptrP->List).GetFirstElement();
			int cnt = 1;
			while (curPtrDP != nullptr)
			{
				DetailProduct* ptrDP = curPtrDP->data;
				if (!(ptrDP->Deleted()))
				{
					cout << '|'; mnu::CenterPrint(String::to_string(cnt), w1);
					cout << '|'; mnu::CenterPrint(ptrDP->GetID(), w1);
					cout << '|'; mnu::CenterPrint(ptrDP->GetNN().to_string(), w2 + 1);
					cout << '|'; mnu::CenterPrint(ptrDP->GetNSX().to_string(), w2);
					cout << '|'; mnu::CenterPrint(ptrDP->GetHSD().to_string(), w2);
					cout << '|'; mnu::CenterPrint(String::to_string(ptrDP->GetPrice()), w1);
					cout << '|'; mnu::CenterPrint(String::to_string(ptrDP->GetSL()), w1); cout << '|' << '\n';
					cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << endl;
					cnt++;
				}
				curPtrDP = curPtrDP->next;
			}
			i++;
		}
		curPtrP = curPtrP->next;
	}
	fclose(f_o);
}