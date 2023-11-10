#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "String.h"
#include "DList.h"
class Bill;
class Customer
{
	friend Customer* InsertCustomer(DList<Customer*>&, const String &, const String &, const String &,bool&);
	friend void OutputTable(const DList<Customer* >&, const int&);
	friend void OutputDetail(Customer *);
private:
	static long long NumCustomer;
	String ID;
	String Name;
	String Phone;
	String Address;
	DList<Bill*> List;
public:
	Customer(const String&,const String&, const String&);
	void AddBill(Bill *);
	String GetID() const;
	String GetName() const;
	String GetPhone() const;
	String GetAddress() const;
	void SetPhone(const String &);
	void SetName(const String &);
	void SetAddress(const String&);
};
#endif
