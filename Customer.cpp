#include "Customer.h"
#include "Output.h"
#include "DList.cpp"
#include "Bill.h"
using namespace std;
long long Customer::NumCustomer = 0;
Customer::Customer(const String& name, const Phone& phone, const String& add)
	:Name(name), PhoneNumber(phone), Address(add)
{
	Customer::NumCustomer++;
	this->ID = String("KH") + String::to_string(Customer::NumCustomer, 5);
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
Customer* InsertCustomer(DList<Customer *>& list, const String & id,const Phone &phone,const String &add, bool &check)
{
	Customer* ptr = FindFirstMatch(list, phone, &Customer::GetPhone);
	if (ptr == nullptr){
		DNode<Customer *> * Newptr = new DNode<Customer *>(new Customer(id,phone,add));
		list.InsertLast(Newptr);
		check = true;
		return Newptr->data;
	}
	else
	{
		check = false;
		return ptr;
	}
}
void OutputTable(const DList<Customer*> & list)
{
	if (list.GetFirstElement() == nullptr)
	{
		mnu::PadLeftPrint("Khong tim thay\n");
		return;
	}
	const int w = 13;
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	cout << '|'; mnu::CenterPrint("STT", w);
	cout << '|'; mnu::CenterPrint("ID", w);
	cout << '|'; mnu::CenterPrint("TEN KHACH HANG", floor((mnu::WIDTH - 6 - 2 * w - (w + 2))*1.0 / 2));
	cout << '|'; mnu::CenterPrint("SDT", w + 2);
	cout << '|'; mnu::CenterPrint("DIA CHI", ceil((mnu::WIDTH - 6 - 2 * w - (w + 2))*1.0 / 2)); cout << '|' << '\n';
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	const DNode<Customer*> *curPtr = list.GetFirstElement();
	int i = 1;
	while (curPtr != nullptr)
	{
		cout << '|'; mnu::CenterPrint(String::to_string(i), w);
		cout << '|'; mnu::CenterPrint((curPtr->data)->ID, w);
		cout << '|'; mnu::CenterPrint((curPtr->data)->Name, floor((mnu::WIDTH - 6 - 2 * w - (w + 2))*1.0 / 2));
		cout << '|'; mnu::CenterPrint(((curPtr->data)->PhoneNumber).to_string(), w + 2);
		cout << '|'; mnu::CenterPrint((curPtr->data)->Address, ceil((mnu::WIDTH - 6 - 2 * w - (w + 2))*1.0 / 2)); cout << '|' << '\n';
		cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
		curPtr = curPtr->next; i++;
	}
}
void OutputDetail(Customer * ptrC)
{
	if (ptrC == nullptr)
	{
		mnu::PadLeftPrint("Khong tim thay khach hang\n");
		return;
	}
	cout << "ID             : " << ptrC->ID << endl;
	cout << "Ten khach hang : " << ptrC->Name << endl;
	cout << "Phone          : " << ptrC->PhoneNumber << endl;
	cout << "Dia chi        : " << ptrC->Address << endl;
	const int w1 = 13;
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	cout << '|'; mnu::CenterPrint("STT", w1);
	cout << '|'; mnu::CenterPrint("ID Hoa don", w1);
	cout << '|'; mnu::CenterPrint("Ngay mua", floorl((mnu::WIDTH - 5 - 2 * w1)*1.0 / 2));
	cout << '|'; mnu::CenterPrint("Tong Tien", ceill((mnu::WIDTH - 5 - 2 * w1)*1.0 / 2)); cout << '|' << '\n';
	cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	const DNode<Bill *> *curPtr = (ptrC->List).GetFirstElement();
	int cnt = 1;
	while (curPtr != nullptr)
	{
		cout << '|'; mnu::CenterPrint(String::to_string(cnt), w1);
		cout << '|'; mnu::CenterPrint((curPtr->data)->GetID() , w1);
		cout << '|'; mnu::CenterPrint(((curPtr->data)->GetBuyDate()).to_string(), floorl((mnu::WIDTH - 5 - 2 * w1)*1.0 / 2));
		cout << '|'; mnu::CenterPrint(String::to_string((curPtr->data)->GetTotal()), ceill((mnu::WIDTH - 5 - 2 * w1)*1.0 / 2)); cout << '|' << '\n';
		cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
		cnt++;
		curPtr = curPtr->next;
	}
	if (cnt == 1)
	{
		cout << "|"; mnu::CenterPrint("Khach hang chua co hoa don nao", mnu::WIDTH-2);cout<<"|\n";
		cout << '+'; mnu::DrawLine(mnu::WIDTH - 2); cout << '+' << '\n';
	}
}
void OutputCustomerFile(const String &fname, const DList<Customer*>& List)
{
	FILE *f_o;
	freopen_s(&f_o, fname, "w", stdout);
	OutputTable(List);
	fclose(f_o);
}