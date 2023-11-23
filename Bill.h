#ifndef BILL_H
#define BILL_H
#include "String.h"
#include "Date.h"
#include "Time.h"
#include "Phone.h"
#include "DList.h"
class Product;
class DetailBill;
class Customer;
class Bill
{
	friend int CalRevenue(const DList<Bill*>&, const Date&, const Date&, DList<Bill*> &);
	friend void OutputTable(const DList<Bill*>&, std::ostream&);
	friend void OutputDetail(const Bill *, std::ostream&);
	friend void InsertBill(DList<Bill*>&, Bill *);
	friend void OutputBillFile(const String &fname, const Bill*);
private:
	static long long NumBill;
	String ID;
	int Total;
	Date BuyDate;
	Time BuyTime;
	int NumDetailBill;
	bool isDeleted;
	DList < DetailBill *> List;
	Customer * ptrC;
	void ConnectCustomer(Customer *);
public:
	Bill(const Date&, const Time&);
	void AddDetailBill(DetailBill*);
	String GetID() const;
	int GetTotal() const;
	Date GetBuyDate() const;
	Time GetBuyTime() const;
	Phone GetCustomerPhone() const;
	bool Deleted() const;
	void SetNumDetailBill(const int&);
	void SetTotal(const int&);
	void Delete();
	friend class Customer;
};
#endif