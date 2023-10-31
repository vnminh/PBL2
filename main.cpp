#include <iostream>
#include "LoHang.h"
#include "String.h"
#include "Date.h"
#include "DNode.cpp"
#include "DList.cpp"
#include "Product.h"
#include "Exception.h"
#include <fstream>
using namespace std;
void InsertProduct(DList<Product> &List, Product& p, const LoHang& lo)
{
	DNode<Product> * ptr = List.Find(p.GetID(), &Product::GetID);
	if (ptr == NULL){
		p.AddLo(lo);
		List.InsertLast(p);
	}
	else
	{
		(ptr->data).AddLo(lo);
	}
}
void input(const String &name, DList<Product>& List)
{
	ifstream inp;
	inp.open(name);
	if (inp.fail())
	{
		throw Exception("FILE NOT EXIST");
	}
	String id_lo = name;
	String temp;
	temp.GetLine(inp);
	Date nn(temp);
	while (!inp.eof()){
		String id_p;
		id_p.GetLine(inp);
		String name;
		name.GetLine(inp);
		String xs;
		xs.GetLine(inp);
		temp.GetLine(inp);
		Date nsx(temp);
		temp.GetLine(inp);
		Date hsd(temp);
		int price, sl;
		inp >> price >> sl;
		inp.ignore();
		Product p(id_p, name, xs);
		InsertProduct(List, p, LoHang(id_lo, nn, nsx, hsd, price, sl));
	}
}
void Nhap(DList<Product> & List)
{
	do
	{
		try
		{
			cout << "Nhap ten file:";
			String fname;
			fname.GetLine(cin);
			input(fname, List);
			cout << "Input thanh cong\n";
			break;
		}
		catch (Exception ex)
		{
			cout << ex.What() << "\nHay nhap lai\n";
		}
	} while (true);
}
int main()
{
	DList<Product> List;
	Nhap(List);
	cout << List;
	Nhap(List);
	cout << List;
	List.Release();
	cout << List;
	return 0;
}
