#include "Product.h"
#include "Output.h"
#include "DList.h"
#include "DetailProduct.h"
#include <iostream>
#include <fstream>
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
void OutputTable(const DList<Product*> & list, std::ostream& out)
{
	if (list.GetFirstElement() == nullptr)
	{
		mnu::PadLeftPrint("Khong tim thay\n",mnu::LEFTSPACE,' ',out);
		return;
	}
	const int w = 20;
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
	out << '|'; mnu::CenterPrint("STT", w, ' ', out);
	out << '|'; mnu::CenterPrint("ID", w, ' ', out);
	out << '|'; mnu::CenterPrint("TEN SAN PHAM", mnu::WIDTH - 5 - 4 * w, ' ', out);
	out << '|'; mnu::CenterPrint("XUAT XU", 2 * w, ' ', out); out << '|' << '\n';
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
	const DNode<Product*> *curPtr = list.GetFirstElement();
	int i = 1;
	while (curPtr != nullptr)
	{
		out << '|'; mnu::CenterPrint(String::to_string(i), w, ' ', out);
		out << '|'; mnu::CenterPrint((curPtr->data)->ID, w, ' ', out);
		out << '|'; mnu::CenterPrint((curPtr->data)->Name, mnu::WIDTH - 5 - 4 * w, ' ', out);
		out << '|'; mnu::CenterPrint((curPtr->data)->XS, 2 * w, ' ', out); out << '|' << '\n';
		out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
		curPtr = curPtr->next; i++;
	}
}
void OutputDetail(const Product * ptrP, std::ostream& out)
{
	if (ptrP == nullptr)
	{
		mnu::PadLeftPrint("Khong tim thay\n",mnu::LEFTSPACE,' ',out);
		return;
	}
	out << "ID           :" << ptrP->ID << endl;
	out << "Ten san pham :" << ptrP->Name << endl;
	out << "Xuat xu      :" << ptrP->XS << endl;
	OutputDetailProduct(ptrP->List,out);
}
void OutputDetailProduct(const DList<DetailProduct *>& List, std::ostream& out)
{
	const int w1 = 13, w2 = (mnu::WIDTH - 8 - 4 * w1) / 3, w3 = mnu::WIDTH - 8 - 4 * w1 - 2 * w2;
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2,'-',out); out << '+' << '\n';
	out << '|'; mnu::CenterPrint("STT", w1, ' ', out);
	out << '|'; mnu::CenterPrint("ID Lo", w1, ' ', out);
	out << '|'; mnu::CenterPrint("Ngay nhap", w3, ' ', out);
	out << '|'; mnu::CenterPrint("NSX", w2, ' ', out);
	out << '|'; mnu::CenterPrint("HSD", w2, ' ', out);
	out << '|'; mnu::CenterPrint("Gia", w1, ' ', out);
	out << '|'; mnu::CenterPrint("So luong", w1, ' ', out); out << '|' << '\n';
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
	const DNode<DetailProduct *> *curPtr = (List).GetFirstElement();
	int cnt = 1;
	while (curPtr != nullptr)
	{
		if (!((curPtr->data)->Deleted)())
		{
			out << '|'; mnu::CenterPrint(String::to_string(cnt), w1, ' ', out);
			out << '|'; mnu::CenterPrint((curPtr->data)->GetID(), w1, ' ', out);
			out << '|'; mnu::CenterPrint((curPtr->data)->GetNN().to_string(), w2 + 1, ' ', out);
			out << '|'; mnu::CenterPrint((curPtr->data)->GetNSX().to_string(), w2, ' ', out);
			out << '|'; mnu::CenterPrint((curPtr->data)->GetHSD().to_string(), w2, ' ', out);
			out << '|'; mnu::CenterPrint(MoneyFormat(String::to_string((curPtr->data)->GetPrice())), w1, ' ', out);
			out << '|'; mnu::CenterPrint(String::to_string((curPtr->data)->GetSL()), w1, ' ', out); out << '|' << '\n';
			out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
			cnt++;
		}
		curPtr = curPtr->next;
	}
	if (cnt == 1)
	{
		out << "|"; mnu::CenterPrint("Danh sach rong", mnu::WIDTH - 2, ' ', out); out << "|\n";
		out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
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
	ofstream out(fname);
	const DNode<Product*> *curPtrP = List.GetFirstElement();
	int i = 1;
	while (curPtrP != nullptr)
	{
		Product *ptrP = curPtrP->data;
		if (!(ptrP->isDeleted))
		{
			out << endl <<  i << endl;
			OutputDetailProduct(ptrP->List, out);
			i++;
		}
		curPtrP = curPtrP->next;
	}
	out.close();
}