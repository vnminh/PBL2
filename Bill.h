#ifndef BILL_H
#define BILL_H
#include "String.h"
#include "Date.h"
#include "DList.h"
class Product;
class DetailBill;
class Customer;
class Bill
{
	friend void OutputTable(const DList<Bill*>&, const int&);
	friend void OutputDetail(const Bill *);
	friend void InsertBill(DList<Bill*>, Bill *);
private:
	static long long NumBill;
	String ID;
	int Total;
	Date BuyDate;
	int NumDetailBill;
	DList < DetailBill *> List;
	Customer * ptrC;
public:
	Bill(const Date&);
	void AddDetailBill(DetailBill*);
	void ConnectCustomer(Customer *);
	String GetID() const;
	int GetTotal() const;
	Date GetBuyDate() const;
	String GetCustomerPhone() const;
	void SetNumDetailBill(const int&);
	void SetTotal(const int&);
};
#endif