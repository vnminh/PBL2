#include "Bill.h"
#include "DetailBill.h"
#include "Product.h"
#include "Customer.h"
#include "Output.h"
#include "Exception.h"
#include <fstream>
using namespace std;
long long Bill::NumBill = 0;
Bill::Bill(const Date& date, const Time& time)
	:BuyDate(date),BuyTime(time),Total(0),NumDetailBill(0),isDeleted(false), ptrC(nullptr)
{
	Bill::NumBill++;
	this->ID = String("HD") + String::to_string(Bill::NumBill, 5);
}
Bill::~Bill()
{
	Bill::NumBill--;
}
void Bill::AddDetailBill(DetailBill * ptr)
{
	ptr->ConnectBill(this);
	(this->List).InsertLast(new DNode<DetailBill*>(ptr));
}
void Bill::ConnectCustomer(Customer * ptr)
{
	this->ptrC = ptr;
}
String Bill::GetID() const
{
	return this->ID;
}
int Bill::GetTotal() const
{
	return this->Total;
}
Date Bill::GetBuyDate() const
{
	return this->BuyDate;
}
Time Bill::GetBuyTime() const
{
	return this->BuyTime;
}
Phone Bill::GetCustomerPhone() const
{
	return (this->ptrC)->GetPhone();
}
bool Bill::Deleted() const
{
	return this->isDeleted;
}
void Bill::SetNumDetailBill(const int& num)
{
	this->NumDetailBill = num;
}
void Bill::SetTotal(const int & total)
{
	this->Total = total;
}
void Bill::Delete()
{
	this->isDeleted = true;
}
void InsertBill(DList<Bill*> &BList, Bill * ptr)
{
	BList.InsertLast(new DNode<Bill*>(ptr));
}
void OutputDetail(const Bill * ptrB, std::ostream& out)
{
	if (ptrB == nullptr)
	{
		mnu::PadLeftPrint("Khong tim thay\n", mnu::LEFTSPACE,' ',out);
		return;
	}
	out << "ID                : " << ptrB->ID << endl;
	out << "Name of customer  : " << (ptrB->ptrC)->GetName() << endl;
	out << "Phone of customer : " << (ptrB->ptrC)->GetPhone() << endl;
	out << "Buy date          : " << ptrB->BuyTime << ' ' << ptrB->BuyDate << endl;
	const int w1 = 15;
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2,'-',out); out << '+' << '\n';
	out << '|'; mnu::CenterPrint("ORDINAL NUMBER", w1, ' ', out);
	out << '|'; mnu::CenterPrint("PRODUCT ID", w1, ' ', out);
	out << '|'; mnu::CenterPrint("NAME", mnu::WIDTH - 5 * w1 - 7, ' ', out);
	out << '|'; mnu::CenterPrint("UNIT PRICE", w1, ' ', out);
	out << '|'; mnu::CenterPrint("QUANTITY/WEIGHT", w1, ' ', out);
	out << '|'; mnu::CenterPrint("TOTAL", w1, ' ', out); out << '|' << '\n';
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
	const DNode<DetailBill *> *curPtr = (ptrB->List).GetFirstElement();
	int cnt = 1;
	while (curPtr != nullptr)
	{
		out << '|'; mnu::CenterPrint(String::to_string(cnt), w1, ' ', out);
		out << '|'; mnu::CenterPrint((curPtr->data)->GetIDDetailProduct(), w1, ' ', out);
		out << '|'; mnu::CenterPrint((curPtr->data)->GetNameProduct(), mnu::WIDTH - 5 * w1 - 7, ' ', out);
		out << '|'; mnu::CenterPrint(MoneyFormat(String::to_string((curPtr->data)->GetPrice())), w1, ' ', out);
		out << '|'; mnu::CenterPrint(String::to_string((curPtr->data)->GetSL()), w1, ' ', out);
		out << '|'; mnu::CenterPrint(MoneyFormat(String::to_string((curPtr->data)->Pay())), w1, ' ', out); out << '|' << '\n';
		out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
		curPtr = curPtr->next;
		cnt++;
	}
	out << '|'; mnu::DrawLine(w1, ' ',out);
	out << '|'; mnu::DrawLine(w1, ' ',out);
	out << '|'; mnu::DrawLine(mnu::WIDTH - 5 * w1 - 7, ' ',out);
	out << '|'; mnu::DrawLine(w1, ' ',out);
	out << '|'; mnu::DrawLine(w1, ' ',out);
	out << '|'; mnu::CenterPrint(MoneyFormat(String::to_string(ptrB->Total)), w1, ' ', out); out << '|' << '\n';
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2,'-',out); out << '+' << '\n';
}
void OutputTable(const DList<Bill*>& list, std::ostream& out)
{
	if (list.GetFirstElement() == nullptr)
	{
		mnu::PadLeftPrint("NOT FOUND\n",mnu::LEFTSPACE,' ',out);
		return;
	}
	const int w = 15;
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
	out << '|'; mnu::CenterPrint("ORDINAL NUMBER", w, ' ', out);
	out << '|'; mnu::CenterPrint("BILL ID", w, ' ', out);
	out << '|'; mnu::CenterPrint("CUSTOMER 'S NAME", mnu::WIDTH - 5 - 4 * w, ' ', out);
	out << '|'; mnu::CenterPrint("TOTAL", 2 * w, ' ', out); out << '|' << '\n';
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
	const DNode<Bill*> *curPtr = list.GetFirstElement();
	int i = 1;
	while (curPtr != nullptr)
	{
		out << '|'; mnu::CenterPrint(String::to_string(i), w, ' ', out);
		out << '|'; mnu::CenterPrint((curPtr->data)->ID, w, ' ', out);
		out << '|';
		if ((curPtr->data)->ptrC != nullptr)
		{
			mnu::CenterPrint(((curPtr->data)->ptrC)->GetName(), mnu::WIDTH - 5 - 4 * w, ' ', out);
		}
		else
		{
			mnu::DrawLine(mnu::WIDTH - 5 - 4 * w, ' ',out);
		}
		out << '|'; mnu::CenterPrint(MoneyFormat(String::to_string((curPtr->data)->Total)), 2 * w, ' ', out); out << '|' << '\n';
		out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
		curPtr = curPtr->next; i++;
	}
}
int CalRevenue(const DList<Bill*>& List, const Date &begin, const Date &end, DList<Bill*> &AnsList)
{
	int res = 0;
	DNode<Bill *> *curPtr = List.GetFirstElement();
	while (curPtr != nullptr)
	{
		Date d = (curPtr->data)->BuyDate;
		if (begin <= d && d <= end)
		{
			res += (curPtr->data)->Total;
			AnsList.InsertLast(new DNode<Bill *>(curPtr->data));
		}
		curPtr = curPtr->next;
	}
	return res;
}
void OutputBillFile(const String &fname, const Bill* ptrB)
{
	ofstream out(fname);
	OutputDetail(ptrB, out);
	out.close();
}
