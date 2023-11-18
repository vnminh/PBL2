#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "String.h"
#include "Phone.h"
#include "DList.h"
class Bill;
class Customer
{
	friend void OutputCustomerFile(const String &, const DList<Customer*>&);
	friend Customer* InsertCustomer(DList<Customer*>&, const String &, const Phone &, const String &,bool&);
	friend void OutputTable(const DList<Customer* >&);
	friend void OutputDetail(Customer *);
private:
	static long long NumCustomer;
	String ID;
	String Name;
	Phone PhoneNumber;
	String Address;
	DList<Bill*> List;
public:
	Customer(const String&,const Phone&, const String&);
	void AddBill(Bill *);
	String GetID() const;
	String GetName() const;
	Phone GetPhone() const;
	String GetAddress() const;
	void SetPhone(const Phone &);
	void SetName(const String &);
	void SetAddress(const String&);
};
#endif