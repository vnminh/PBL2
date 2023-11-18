#ifndef BILL_H
#define BILL_H
#include "String.h"
#include "Date.h"
#include "Phone.h"
#include "DList.h"
class Product;
class DetailBill;
class Customer;
class Bill
{
	friend int CalRevenue(const DList<Bill*>&, const Date&, const Date&, DList<Bill*> &);
	friend void OutputTable(const DList<Bill*>&);
	friend void OutputDetail(const Bill *);
	friend void InsertBill(DList<Bill*>&, Bill *);
private:
	static long long NumBill;
	String ID;
	int Total;
	Date BuyDate;
	int NumDetailBill;
	DList < DetailBill *> List;
	Customer * ptrC;
	void ConnectCustomer(Customer *);
public:
	Bill(const Date&);
	void AddDetailBill(DetailBill*);
	String GetID() const;
	int GetTotal() const;
	Date GetBuyDate() const;
	Phone GetCustomerPhone() const;
	void SetNumDetailBill(const int&);
	void SetTotal(const int&);
	friend class Customer;
};
#endif