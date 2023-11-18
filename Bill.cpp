#include "Bill.h"
#include "DetailBill.h"
#include "Product.h"
#include "Customer.h"
#include "Output.h"
using namespace std;
long long Bill::NumBill = 0;
Bill::Bill(const Date& date)
	:BuyDate(date),Total(0),NumDetailBill(0), ptrC(nullptr)
{
	Bill::NumBill++;
	this->ID = String("HD") + String::to_string(Bill::NumBill, 5);
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
Phone Bill::GetCustomerPhone() const
{
	return (this->ptrC)->GetPhone();
}
void Bill::SetNumDetailBill(const int& num)
{
	this->NumDetailBill = num;
}
void Bill::SetTotal(const int & total)
{
	this->Total = total;
}
void InsertBill(DList<Bill*> &BList, Bill * ptr)
{
	BList.InsertLast(new DNode<Bill*>(ptr));
}
void OutputDetail(const Bill * ptrB)
{
	if (ptrB == nullptr)
	{
		mnu::PadLeftPrint("Khong tim thay\n");
		return;
	}
	cout << "ID             : " << ptrB->ID << endl;
	cout << "Ten khach hang : ";
	if (ptrB->ptrC != nullptr)
	{
		cout << (ptrB->ptrC)->GetName();
	}
	cout << endl;
	cout << "Ngay mua       : " << ptrB->BuyDate << endl;
	const int w1 = 15;
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	cout << '|'; mnu::CenterPrint("STT", w1);
	cout << '|'; mnu::CenterPrint("ID mat hang", w1);
	cout << '|'; mnu::CenterPrint("Ten mat hang", mnu::WIDTH - 5 * w1 - 7);
	cout << '|'; mnu::CenterPrint("Don gia", w1);
	cout << '|'; mnu::CenterPrint("So luong", w1);
	cout << '|'; mnu::CenterPrint("Thanh Tien", w1); cout << '|' << '\n';
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	const DNode<DetailBill *> *curPtr = (ptrB->List).GetFirstElement();
	int cnt = 1;
	while (curPtr != nullptr)
	{
		cout << '|'; mnu::CenterPrint(String::to_string(cnt), w1);
		cout << '|'; mnu::CenterPrint((curPtr->data)->GetIDDetailProduct(), w1);
		cout << '|'; mnu::CenterPrint((curPtr->data)->GetNameProduct(), mnu::WIDTH - 5 * w1 - 7);
		cout << '|'; mnu::CenterPrint(String::to_string((curPtr->data)->GetPrice()), w1);
		cout << '|'; mnu::CenterPrint(String::to_string((curPtr->data)->GetSL()), w1);
		cout << '|'; mnu::CenterPrint(MoneyFormat(String::to_string((curPtr->data)->Pay())), w1); cout << '|' << '\n';
		cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
		curPtr = curPtr->next;
		cnt++;
	}
	cout << '|'; mnu::DrawLine(w1, ' ');
	cout << '|'; mnu::DrawLine(w1, ' ');
	cout << '|'; mnu::DrawLine(mnu::WIDTH - 5 * w1 - 7, ' ');
	cout << '|'; mnu::DrawLine(w1, ' ');
	cout << '|'; mnu::DrawLine(w1, ' ');
	cout << '|'; mnu::CenterPrint(MoneyFormat(String::to_string(ptrB->Total)), w1); cout << '|' << '\n';
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
}
void OutputTable(const DList<Bill*>& list)
{
	if (list.GetFirstElement() == nullptr)
	{
		mnu::PadLeftPrint("Khong tim thay\n");
		return;
	}
	const int w = 15;
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	cout << '|'; mnu::CenterPrint("STT", w);
	cout << '|'; mnu::CenterPrint("ID HOA DON", w);
	cout << '|'; mnu::CenterPrint("TEN KHACH HANG", mnu::WIDTH - 5 - 4 * w);
	cout << '|'; mnu::CenterPrint("TONG TIEN", 2 * w); cout << '|' << '\n';
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	const DNode<Bill*> *curPtr = list.GetFirstElement();
	int i = 1;
	while (curPtr != nullptr)
	{
		cout << '|'; mnu::CenterPrint(String::to_string(i), w);
		cout << '|'; mnu::CenterPrint((curPtr->data)->ID, w);
		cout << '|'; 
		if ((curPtr->data)->ptrC != nullptr)
		{
			mnu::CenterPrint(((curPtr->data)->ptrC)->GetName(), mnu::WIDTH - 5 - 4 * w);
		}
		else
		{
			mnu::DrawLine(mnu::WIDTH - 5 - 4 * w, ' ');
		}
		cout << '|'; mnu::CenterPrint(String::to_string((curPtr->data)->Total), 2 * w); cout << '|' << '\n';
		cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
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