#pragma once
#include "DetailProduct.h"
class DetailWeightProduct :	public DetailProduct
{
private:
	static int CalUnit;
public:
	DetailWeightProduct(const String&, const Date&, const Date&, const Date&, const int&);
	~DetailWeightProduct();
	virtual  int Calculate(const int &) const;
	virtual bool SLWarn() const;
	virtual String GetSL_str() const;
	static void SetCalUnit(const int &);
};

