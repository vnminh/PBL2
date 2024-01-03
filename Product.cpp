#include "Product.h"
#include "Output.h"
#include "DList.h"
#include "DetailProduct.h"
#include "Exception.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
using namespace std;
Product::Product(const String &id, const String &n, const String &xs, const int &price)
	:ID(id), Name(n), XS(xs), isDeleted(false), NumDP(0), Price(price)
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
	if (price <= 0)
	{
		throw Exception("PRICE MUST STRICTLY BE GREATER THAN 0");
	}
}
Product::~Product()
{}
void Product::AddDetailProduct( DetailProduct * ptr)
{
	ptr->ConnectProduct(this);
	(this->List).InsertLast(new DNode<DetailProduct *>(ptr));
	this->SL += ptr->GetSL();
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
String Product::GetSL_str() const
{
	String donvi = (this->List).GetFirstElement()->data->GetDonVi();
	if (donvi == String("")) return String::to_string(this->SL);
	else return String::to_string(this->SL) + String(" ") + donvi;
}
int Product::GetSL() const
{
	return this->SL;
}
int Product::GetPrice() const
{
	return this->Price;
}
bool Product::SLWarn() const
{
	if ((this->List).GetFirstElement() == nullptr) return true;
	return (this->List).GetFirstElement()->data->SLWarn();
}
const DList<DetailProduct*>& Product::GetDPList() const
{
	return this->List;
}
void Product::Deduct(const int sl)
{
	this->SL -= sl;
}
void Product::Add(const int sl)
{
	this->SL += sl;
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
void Product::DeleteDP(DetailProduct *ptr)
{
	this->NumDP--;
	this->SL -= ptr->SL;
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
	const int w = 20, wnum = 5;
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
	out << '|'; mnu::CenterPrint("NUM", wnum, ' ', out);
	out << '|'; mnu::CenterPrint("ID", w, ' ', out);
	out << '|'; mnu::CenterPrint("PRODUCT 'S NAME", mnu::WIDTH - wnum - 4 * w - 7, ' ', out);
	out << '|'; mnu::CenterPrint("ORIGIN", w, ' ', out);
	out << '|'; mnu::CenterPrint("QUANTITY/WEIGHT", w, ' ', out);
	out << '|'; mnu::CenterPrint("PRICE", w, ' ', out); out << '|' << '\n';
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
	const DNode<Product*> *curPtr = list.GetFirstElement();
	int i = 1;
	while (curPtr != nullptr)
	{
		if (curPtr->data->SLWarn())
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			out << '|'; mnu::CenterPrint(String::to_string(i), wnum, ' ', out);
			out << '|'; mnu::CenterPrint((curPtr->data)->ID, w, ' ', out);
			out << '|'; mnu::CenterPrint((curPtr->data)->Name, mnu::WIDTH - wnum - 4 * w - 7, ' ', out);
			out << '|'; mnu::CenterPrint((curPtr->data)->XS, w, ' ', out);
			out << '|';
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			mnu::CenterPrint((curPtr->data)->GetSL_str(), w, ' ', out);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			out << '|';
			mnu::CenterPrint(MoneyFormat(String::to_string((curPtr->data)->Price)), w, ' ', out); out << '|' << '\n';
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		else
		{
			out << '|'; mnu::CenterPrint(String::to_string(i), wnum, ' ', out);
			out << '|'; mnu::CenterPrint((curPtr->data)->ID, w, ' ', out);
			out << '|'; mnu::CenterPrint((curPtr->data)->Name, mnu::WIDTH - wnum - 4 * w - 7, ' ', out);
			out << '|'; mnu::CenterPrint((curPtr->data)->XS, w, ' ', out);
			out << '|'; mnu::CenterPrint((curPtr->data)->GetSL_str(), w, ' ', out);
			out << '|'; mnu::CenterPrint(MoneyFormat(String::to_string((curPtr->data)->Price)), w, ' ', out); out << '|' << '\n';
		}
		out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
		curPtr = curPtr->next; i++;
	}
	if (i == 1)
	{
		out << "|"; mnu::CenterPrint("EMPTY LIST", mnu::WIDTH - 2, ' ', out); out << "|\n";
		out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
	}
}
void OutputDetail(const Product * ptrP, std::ostream& out)
{
	if (ptrP == nullptr)
	{
		out << "ID              : NOT FOUND" << endl;
		out << "Product 's name :" << endl;
		out << "Origin          :" << endl;
		out << "Price           :" << endl;
		OutputDetailProduct(DList<DetailProduct *>(), out);
	}
	else
	{
		out << "ID              :" << ptrP->ID << endl;
		out << "Product 's name :" << ptrP->Name << endl;
		out << "Origin          :" << ptrP->XS << endl;
		out << "Price           :" << ptrP->Price << endl;
		OutputDetailProduct(ptrP->List, out);
	}
}
void OutputDetailProduct(const DList<DetailProduct *>& List, std::ostream& out)
{
	const int w1 = 15, wnum = 5, w2 = (mnu::WIDTH - 7 - wnum - 2 * w1) / 3, w3 = mnu::WIDTH - 7 - wnum - 2 * w1 - 2 * w2;
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2,'-',out); out << '+' << '\n';
	out << '|'; mnu::CenterPrint("NUM", wnum, ' ', out);
	out << '|'; mnu::CenterPrint("BATCH ID", w1, ' ', out);
	out << '|'; mnu::CenterPrint("RECEIPT DAY", w3, ' ', out);
	out << '|'; mnu::CenterPrint("MFG", w2, ' ', out);
	out << '|'; mnu::CenterPrint("EXP", w2, ' ', out);
	out << '|'; mnu::CenterPrint("QUANTITY", w1, ' ', out); out << '|' << '\n';
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
	const DNode<DetailProduct *> *curPtr = (List).GetFirstElement();
	int cnt = 1;
	while (curPtr != nullptr)
	{
		if (!((curPtr->data)->Deleted)())
		{
			if (curPtr->data->HSDWarn())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				out << '|'; mnu::CenterPrint(String::to_string(cnt), wnum, ' ', out);
				out << '|'; mnu::CenterPrint((curPtr->data)->GetID(), w1, ' ', out);
				out << '|'; mnu::CenterPrint((curPtr->data)->GetNN().to_string(), w3, ' ', out);
				out << '|'; mnu::CenterPrint((curPtr->data)->GetNSX().to_string(), w2, ' ', out);
				out << '|'; 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); 
				mnu::CenterPrint((curPtr->data)->GetHSD().to_string(), w2, ' ', out);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				out << '|'; mnu::CenterPrint((curPtr->data)->GetSL_str(), w1, ' ', out); out << '|' << '\n';
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				out << '|'; mnu::CenterPrint(String::to_string(cnt), wnum, ' ', out);
				out << '|'; mnu::CenterPrint((curPtr->data)->GetID(), w1, ' ', out);
				out << '|'; mnu::CenterPrint((curPtr->data)->GetNN().to_string(), w3, ' ', out);
				out << '|'; mnu::CenterPrint((curPtr->data)->GetNSX().to_string(), w2, ' ', out);
				out << '|'; mnu::CenterPrint((curPtr->data)->GetHSD().to_string(), w2, ' ', out);
				out << '|'; mnu::CenterPrint((curPtr->data)->GetSL_str(), w1, ' ', out); out << '|' << '\n';
			}
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
void OutputExpiredDetailProduct(const DList<DetailProduct *>& List, std::ostream& out)
{
	const int w1 = 20, wnum = 5, w2 = (mnu::WIDTH - 7 - wnum - 2 * w1) / 3, w3 = mnu::WIDTH - 7 - wnum - 2 * w1 - 2 * w2;
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
	out << '|'; mnu::CenterPrint("NUM", wnum, ' ', out);
	out << '|'; mnu::CenterPrint("DETAIL PRODUCT ID", w1, ' ', out);
	out << '|'; mnu::CenterPrint("RECEIPT DAY", w3, ' ', out);
	out << '|'; mnu::CenterPrint("MFG", w2, ' ', out);
	out << '|'; mnu::CenterPrint("EXP", w2, ' ', out);
	out << '|'; mnu::CenterPrint("QUANTITY", w1, ' ', out); out << '|' << '\n';
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
	const DNode<DetailProduct *> *curPtr = (List).GetFirstElement();
	int cnt = 1;
	while (curPtr != nullptr)
	{
		if (!((curPtr->data)->Deleted)())
		{
			String ID = curPtr->data->GetProductID() + curPtr->data->GetID();
			if (curPtr->data->HSDWarn())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				out << '|'; mnu::CenterPrint(String::to_string(cnt), wnum, ' ', out);
				out << '|'; mnu::CenterPrint(ID, w1, ' ', out);
				out << '|'; mnu::CenterPrint((curPtr->data)->GetNN().to_string(), w3, ' ', out);
				out << '|'; mnu::CenterPrint((curPtr->data)->GetNSX().to_string(), w2, ' ', out);
				out << '|';
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				mnu::CenterPrint((curPtr->data)->GetHSD().to_string(), w2, ' ', out);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				out << '|'; mnu::CenterPrint((curPtr->data)->GetSL_str(), w1, ' ', out); out << '|' << '\n';
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				out << '|'; mnu::CenterPrint(String::to_string(cnt), wnum, ' ', out);
				out << '|'; mnu::CenterPrint(ID, w1, ' ', out);
				out << '|'; mnu::CenterPrint((curPtr->data)->GetNN().to_string(), w3, ' ', out);
				out << '|'; mnu::CenterPrint((curPtr->data)->GetNSX().to_string(), w2, ' ', out);
				out << '|'; mnu::CenterPrint((curPtr->data)->GetHSD().to_string(), w2, ' ', out);
				out << '|'; mnu::CenterPrint((curPtr->data)->GetSL_str(), w1, ' ', out); out << '|' << '\n';
			}
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