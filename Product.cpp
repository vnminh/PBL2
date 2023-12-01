#include "Product.h"
#include "Output.h"
#include "DList.h"
#include "DetailProduct.h"
#include "Exception.h"
#include <iostream>
#include <fstream>
using namespace std;
Product::Product(const String &id, const String &n, const String &xs)
	:ID(id), Name(n), XS(xs), isDeleted(false), NumDP(0)
{
	if (id.GetLength() != 9)
	{
		throw Exception("WRONG FORMAT FOR PRODUCT ID");
	}
	if (id[0] != 'M' || id[1] != 'H')
	{
		throw Exception("WRONG FORMAT FOR PRODUCT ID");
	}
	String type = id.SubStr(7, 2);
	if (type != String("01") && type != String("00"))
	{
		throw Exception("WRONG FORMAT FOR PRODUCT ID");
	}
	for (int i = 2; i <= 6; i++)
	{
		if (id[i]<'0' || id[i]>'9')
		{
			throw Exception("WRONG FORMAT FOR PRODUCT ID");
		}
	}
	if (n == String(""))
	{
		throw Exception("NAME CAN'T BE EMPTY");
	}
	if (xs == String(""))
	{
		throw Exception("ORIGIN CAN'T BE EMPTY");
	}
}
Product::~Product()
{}
void Product::AddDetailProduct( DetailProduct * ptr)
{
	ptr->ConnectProduct(this);
	(this->List).InsertLast(new DNode<DetailProduct *>(ptr));
	this->NumDP++;
}
DetailProduct* Product::FindDetailProduct(const String&id) const
{
	DetailProduct* ptr = FindFirstMatch(this->List, id, &DetailProduct::GetID);
	return ptr;
} 
int Product::GetNumDP() const
{
	return this->NumDP;
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
const DList<DetailProduct*>& Product::GetDPList() const
{
	return this->List;
}
void Product::Delete()
{
	DNode<DetailProduct*>* curPtr = (this->List).GetFirstElement();
	while (curPtr != nullptr)
	{
		if (!((curPtr->data)->Deleted()))	(curPtr->data)->Delete();
		curPtr = curPtr->next;
	}
}
bool Product::Deleted() const
{
	return this->isDeleted;
}
void Product::DeleteDP()
{
	this->NumDP--;
}
bool InsertProduct(DList<Product *> &List, Product *ptrP,  DetailProduct *ptrDP )
{
	Product *lptrP = FindFirstMatch(List, ptrP->ID, &Product::GetID);
	if (lptrP == nullptr)
	{
		DNode<Product *> * Newptr = new DNode<Product *>(ptrP);
		(Newptr->data)->AddDetailProduct(ptrDP);
		List.InsertLast(Newptr);
		return true;
	}
	else
	{
		delete ptrP;
		DetailProduct *lptrDP = FindFirstMatch(lptrP->List, ptrDP->GetID(), &DetailProduct::GetID);
		if (lptrDP == nullptr)
		{
			lptrP->AddDetailProduct(ptrDP);
			return true;
		}
		else delete ptrDP;
	}
	return false;
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
	out << '|'; mnu::CenterPrint("ORDINAL NUMBER", w, ' ', out);
	out << '|'; mnu::CenterPrint("ID", w, ' ', out);
	out << '|'; mnu::CenterPrint("PRODUCT 'S NAME", mnu::WIDTH - 5 - 4 * w, ' ', out);
	out << '|'; mnu::CenterPrint("ORIGIN", 2 * w, ' ', out); out << '|' << '\n';
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
		mnu::PadLeftPrint("NOT FOUND\n",mnu::LEFTSPACE,' ',out);
		return;
	}
	out << "ID              :" << ptrP->ID << endl;
	out << "Product 's name :" << ptrP->Name << endl;
	out << "Origin          :" << ptrP->XS << endl;
	OutputDetailProduct(ptrP->List,out);
}
void OutputDetailProduct(const DList<DetailProduct *>& List, std::ostream& out)
{
	const int w1 = 15, w2 = (mnu::WIDTH - 8 - 4 * w1) / 3, w3 = mnu::WIDTH - 8 - 4 * w1 - 2 * w2;
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2,'-',out); out << '+' << '\n';
	out << '|'; mnu::CenterPrint("ORDINAL NUMBER", w1, ' ', out);
	out << '|'; mnu::CenterPrint("BATCH ID", w1, ' ', out);
	out << '|'; mnu::CenterPrint("RECEIPT DAY", w3, ' ', out);
	out << '|'; mnu::CenterPrint("MFG", w2, ' ', out);
	out << '|'; mnu::CenterPrint("EXP", w2, ' ', out);
	out << '|'; mnu::CenterPrint("PRICE", w1, ' ', out);
	out << '|'; mnu::CenterPrint("QUANTITY", w1, ' ', out); out << '|' << '\n';
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
	const DNode<DetailProduct *> *curPtr = (List).GetFirstElement();
	int cnt = 1;
	while (curPtr != nullptr)
	{
		if (!((curPtr->data)->Deleted)())
		{
			out << '|'; mnu::CenterPrint(String::to_string(cnt), w1, ' ', out);
			out << '|'; mnu::CenterPrint((curPtr->data)->GetID(), w1, ' ', out);
			out << '|'; mnu::CenterPrint((curPtr->data)->GetNN().to_string(), w3, ' ', out);
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
		out << "|"; mnu::CenterPrint("EMPTY LIST", mnu::WIDTH - 2, ' ', out); out << "|\n";
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
			OutputDetail(ptrP, out);
			i++;
		}
		curPtrP = curPtrP->next;
	}
	out.close();
}