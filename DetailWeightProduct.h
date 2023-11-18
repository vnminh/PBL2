#pragma once
#include "DetailProduct.h"
class DetailWeightProduct :	public DetailProduct
{
private:
	static int CalUnit;
public:
	DetailWeightProduct(const String&, const Date&, const Date&, const Date&, const int&, const int&);
	~DetailWeightProduct();
	int Calculate(const int &) const;
	static void SetCalUnit(const int &);
};

