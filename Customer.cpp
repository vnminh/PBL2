#include "Customer.h"
#include "Output.h"
#include "DList.cpp"
#include "Bill.h"
#include "Exception.h"
#include <fstream>
using namespace std;
long long Customer::NumCustomer = -1;
Customer::Customer(const String& name, const Phone& phone, const String& add)
	:Name(name), PhoneNumber(phone), Address(add), isDeleted(false)
{
	Customer::NumCustomer++;
	this->ID = String("KH") + String::to_string(Customer::NumCustomer, 5);
}
Customer::~Customer()
{
	Customer::NumCustomer--;
}
void Customer::AddBill(Bill * ptr)
{
	ptr->ConnectCustomer(this);
	(this->List).InsertLast(new DNode<Bill*>(ptr));
}
String Customer::GetID() const
{
	return this->ID;
}
String Customer::GetName() const
{
	return this->Name;
}
Phone Customer::GetPhone() const
{
	return this->PhoneNumber;
}
String Customer::GetAddress() const
{
	return this->Address;
}
bool Customer::Deleted() const
{
	return this->isDeleted;
}
void Customer::SetName(const String & name)
{
	this->Name = name;
}
void Customer::SetAddress(const String & add)
{
	this->Address = add;
}
void Customer::SetPhone(const Phone &phone)
{
	this->PhoneNumber = phone;
}
void Customer::Delete()
{
	this->isDeleted = true;
}
Customer* InsertCustomer(DList<Customer *>& list, Customer *ptrC, bool &check)
{
	Customer* ptr = FindFirstMatch(list, ptrC->PhoneNumber, &Customer::GetPhone);
	if (ptr == nullptr){
		DNode<Customer *> * Newptr = new DNode<Customer *>(ptrC);
		list.InsertLast(Newptr);
		check = true;
		return Newptr->data;
	}
	else
	{
		delete ptrC;   // trung thi xoa doi tuong muon them vao
		check = false;
		return ptr;
	}
}
void OutputTable(const DList<Customer*> & list, std::ostream& out)
{
	if (list.GetFirstElement() == nullptr)
	{
		mnu::PadLeftPrint("NOT FOUND\n",mnu::LEFTSPACE,' ',out);
		return;
	}
	const int w = 15;
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2,'-',out); out << '+' << '\n';
	out << '|'; mnu::CenterPrint("ORDINAL NUMBER", w,' ',out);
	out << '|'; mnu::CenterPrint("ID", w,' ',out);
	out << '|'; mnu::CenterPrint("CUSTOMER 'S NAME", floor((mnu::WIDTH - 6 - 2 * w - (w + 2))*1.0 / 2),' ',out);
	out << '|'; mnu::CenterPrint("PHONE NUMBER", w + 2,' ',out);
	out << '|'; mnu::CenterPrint("ADDRESS", ceil((mnu::WIDTH - 6 - 2 * w - (w + 2))*1.0 / 2),' ',out);out << '|' << '\n';
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2,'-',out); out << '+' << '\n';
	const DNode<Customer*> *curPtr = list.GetFirstElement();
	int i = 1;
	while (curPtr != nullptr)
	{
		if (!((curPtr->data)->isDeleted))
		{
			out << '|'; mnu::CenterPrint(String::to_string(i), w, ' ', out);
			out << '|'; mnu::CenterPrint((curPtr->data)->ID, w, ' ', out);
			out << '|'; mnu::CenterPrint((curPtr->data)->Name, floor((mnu::WIDTH - 6 - 2 * w - (w + 2))*1.0 / 2), ' ', out);
			out << '|'; mnu::CenterPrint(((curPtr->data)->PhoneNumber).to_string(), w + 2, ' ', out);
			out << '|'; mnu::CenterPrint((curPtr->data)->Address, ceil((mnu::WIDTH - 6 - 2 * w - (w + 2))*1.0 / 2), ' ', out); out << '|' << '\n';
			out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
			i++;
		}
		curPtr = curPtr->next; 
	}
}
void OutputDetail(Customer * ptrC, std::ostream& out)
{
	if (ptrC == nullptr)
	{
		mnu::PadLeftPrint("Khong tim thay khach hang\n",mnu::LEFTSPACE,' ',out);
		return;
	}
	out << "ID               : " << ptrC->ID << endl;
	out << "Customer 's name : " << ptrC->Name << endl;
	out << "Phone number     : " << ptrC->PhoneNumber << endl;
	out << "Address          : " << ptrC->Address << endl;
	const int w1 = 15;
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2,'-',out); out << '+' << '\n';
	out << '|'; mnu::CenterPrint("ORDINAL NUMBER", w1,' ',out);
	out << '|'; mnu::CenterPrint("BILL ID", w1,' ', out);
	out << '|'; mnu::CenterPrint("BUY DATE", floorl((mnu::WIDTH - 5 - 2 * w1)*1.0 / 2), ' ', out);
	out << '|'; mnu::CenterPrint("TOTAL", ceill((mnu::WIDTH - 5 - 2 * w1)*1.0 / 2), ' ', out); out << '|' << '\n';
	out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
	const DNode<Bill *> *curPtr = (ptrC->List).GetFirstElement();
	int cnt = 1;
	while (curPtr != nullptr)
	{
		if (!((curPtr->data)->Deleted()))
		{
			out << '|'; mnu::CenterPrint(String::to_string(cnt), w1, ' ', out);
			out << '|'; mnu::CenterPrint((curPtr->data)->GetID(), w1, ' ', out);
			out << '|'; mnu::CenterPrint(((curPtr->data)->GetBuyDate()).to_string(), floorl((mnu::WIDTH - 5 - 2 * w1)*1.0 / 2), ' ', out);
			out << '|'; mnu::CenterPrint(MoneyFormat(String::to_string((curPtr->data)->GetTotal())), ceill((mnu::WIDTH - 5 - 2 * w1)*1.0 / 2), ' ', out); out << '|' << '\n';
			out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
			cnt++;
		}
		curPtr = curPtr->next;
	}
	if (cnt == 1)
	{
		out << "|"; mnu::CenterPrint("Customer have not had any bill yet", mnu::WIDTH - 2, ' ', out); out << "|\n";
		out << '+'; mnu::DrawLine(mnu::WIDTH - 2, '-', out); out << '+' << '\n';
	}
}
void OutputCustomerFile(const String &fname, const DList<Customer*>& List)
{
	ofstream out(fname);
	OutputTable(List, out);
	out.close();
}