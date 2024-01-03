#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "String.h"
#include "Phone.h"
#include "DList.h"
class Bill;
class Customer
{
	friend void OutputCustomerFile(const String &, const DList<Customer*>&);
	friend Customer* InsertCustomer(DList<Customer*>&, Customer *,bool&);
	friend void OutputTable(const DList<Customer* >&, std::ostream&);
	friend void OutputDetail(Customer *, std::ostream&);
private:
	static long long NumCustomer;
	String ID;
	String Name;
	Phone PhoneNumber;
	String Address;
	bool isDeleted;
	DList<Bill*> List;
public:
	Customer(const String&,const Phone&, const String&);
	~Customer();
	void AddBill(Bill *);
	String GetID() const;
	String GetName() const;
	Phone GetPhone() const;
	String GetAddress() const;
	bool Deleted() const;
	void SetPhone(const Phone &);
	void SetName(const String &);
	void SetAddress(const String&);
	void CancelCurrentBill();
	void Delete();
};
#endif
