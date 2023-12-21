#include "Output.h"
#include "Exception.h"
#include "Phone.h"
#include "Date.h"
#include "Customer.h"
#include <conio.h>
#include <Windows.h>
void mnu::DrawTitle(int type, int w, const String t) // type = 0 1 2 3
{
	CenterPrint(t, w,' ',std::cout);
	std::cout << "\n\n" << '+'; DrawLine(w - 2, '=', std::cout); std::cout << '+' << std::endl;
	String title[4]{"PRODUCT MANAGEMENT", "CUSTOMER MANAGEMENT", "BILL MANAGEMENT", "PAYMENT"};
	int subw = (mnu::WIDTH - 8) / 4;
	for (int i = 0; i < 4; i++)
	{
		if (i == type)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			std::cout << '|'; CenterPrint(title[i], subw, ' ', std::cout); std::cout << '|';
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		else
		{
			std::cout << '|'; CenterPrint(title[i], subw, ' ', std::cout); std::cout << '|';
		}
	}
	std::cout << std::endl << '+'; DrawLine(w - 2, '=', std::cout); std::cout << '+' << "\n\n";
}
void mnu::DrawLine(int len, char c, std::ostream& out)
{
	for (int i = 1; i <= len; i++)
	{
		out << c;
	}
}
void mnu::CenterPrint(const String &s, int len, char pad, std::ostream& out)
{
	int temp = len - s.GetLength();
	if (temp <= 0)
	{
		out << s;
		return;
	}
	int before = floor(temp * 1.0 / 2);
	int after = ceil(temp * 1.0 / 2);
	DrawLine(before, pad,out);
	out << s;
	DrawLine(after, pad,out);
}
void mnu::LeftPrint(const String &s, int len, char pad, std::ostream& out)
{
	int remain = len - s.GetLength();
	out << s;
	if (remain < 0) return;
	DrawLine(remain, pad,out);
}
void mnu::LeftPrintForInput(const String &s, int len, char pad, std::ostream& out)
{
	int remain = len - s.GetLength();
	out << s;
	if (remain < 0)
	{
		out << ": ";
		return;
	}
	DrawLine(remain, pad,out);
	out << ": ";
}
void mnu::PadLeftPrint(const String &s, int padlen, char pad, std::ostream& out)
{
	DrawLine(padlen, pad,out);
	out << s;
}
void mnu::Pause()
{
	mnu::CenterPrint("Press ENTER to continue ...", mnu::WIDTH, ' ', std::cout);
	_getch();
}
template <typename T>
bool mnu::InputAndCheck(const String &mess, const int& width, void(*format)(const String&, int, char, std::ostream&), T& var)
{
	bool ok = false;
	do
	{
		(*format)(mess, width, ' ',std::cout);
		try
		{
			fflush(stdin);
			std::cin.clear();
			std::cin >> var;
			ok = true;
		}
		catch (Exception ex)
		{
			LeftPrint(ex.What(),0,' ',std::cout);
			std::cout << std::endl;
			LeftPrint("INPUT AGAIN, PLEASE\n",0,' ',std::cout);
		}
	} while (!ok);
	return true;
}
template bool mnu::InputAndCheck<Phone>(const String&, const int &, void(*)(const String&, int, char, std::ostream&), Phone&);
template bool mnu::InputAndCheck<Date>(const String&, const int &, void(*)(const String&, int, char, std::ostream&), Date&);
template <class T>
void mnu::CheckID(const String&)
{}
template <>
void mnu::CheckID<Product>(const String &id)
{
	if (id.GetLength() != 9)
	{
		throw Exception("WRONG FORMAT FOR PRODUCT ID");
	}
	if (id[0] != 'M' || id[1] != 'H')
	{
		throw Exception("WRONG FORMAT FOR PRODUCT ID");
	}
	String type = id.SubStr(7, 2);
	if (type != String("01") && type != String("00"))
	{
		throw Exception("WRONG FORMAT FOR PRODUCT ID");
	}
	for (int i = 2; i <= 6; i++)
	{
		if (id[i]<'0' || id[i]>'9')
		{
			throw Exception("WRONG FORMAT FOR PRODUCT ID");
		}
	}
}
template <>
void mnu::CheckID<DetailProduct>(const String &id)
{
	if (id.GetLength() != 4)
	{
		throw Exception("WRONG FORMAT FOR BATCH ID");
	}
	if (id[0] != 'L')
	{
		throw Exception("WRONG FORMAT FOR BATCH ID");
	}
	for (int i = 1; i <= 3; i++)
	{
		if (id[i]<'0' || id[i]>'9')
		{
			throw Exception("WRONG FORMAT FOR BATCH ID");
		}
	}
}
template <>
void mnu::CheckID<Bill>(const String &id)
{
	if (id.GetLength() != 7)
	{
		throw Exception("WRONG FORMAT FOR BILL ID");
	}
	if (id[0] != 'H' || id[1] != 'D')
	{
		throw Exception("WRONG FORMAT FOR BILL ID");
	}
	for (int i = 2; i <= 6; i++)
	{
		if (id[i]<'0' || id[i]>'9')
		{
			throw Exception("WRONG FORMAT FOR BILL ID");
		}
	}
}
template void mnu::CheckID<Product>(const String&);
template void mnu::CheckID<DetailProduct>(const String&);
template void mnu::CheckID<Bill>(const String&);
template <class T>
void mnu::ProcessAfterSearch(T *ptr)
{
	if (ptr->GetPhone() == Phone("0000000000"))
	{
		system("pause");
		return;
	}
	std::cout << "PRESS d TO DELETE CUSTOMER" << std::endl;
	char d = _getch();
	if (d == 'd' || d == 'D')
	{
		ptr->Delete();
	}
}
template <>
void mnu::ProcessAfterSearch<Product>(Product *ptr)
{
	int choice;
	do
	{
		std::cout << "Type ordinal number of entry to delete (Type '0' to continue and '-1' to clear all) : ";
		std::cin >> choice;
		if (choice >= -1 && choice <= ptr->GetNumDP()) break;
		else
		{
			fflush(stdin);
			std::cin.clear();
			std::cout<<"INVALID VALUE\n";
		}
	} while (true);
	if (choice == 0) return;
	if (choice > 0)
	{
		DetailProduct *ptrDP = FindIndex(ptr->GetDPList(), choice);
		ptrDP->Delete();
		return;
	}
	if (choice == -1)
	{
		ptr->Delete();
		return;
	}
}
template <>
void mnu::ProcessAfterSearch<Bill>(Bill *ptr)
{
	std::cout << "PRESS p TO PRINT BILL" << std::endl;
	char p = _getch();
	if (p == 'p' || p == 'P')
	{
		OutputBillFile(ptr->GetID(), ptr);
	}
}
template void mnu::ProcessAfterSearch<Product>(Product *);
template void mnu::ProcessAfterSearch<Customer>(Customer *);
template void mnu::ProcessAfterSearch<Bill>(Bill *);
template <class T>
void mnu::ProcessForSort(DList<T*>*)
{}
template <>
void mnu::ProcessForSort<Product>(DList<Product*>* ptr)
{
	do
	{
		int choice;
		PadLeftPrint("1.Sort Product in ASCENDING order of price\n", 0, ' ', std::cout);
		PadLeftPrint("2.Sort Product in DESCENDING order of price\n", 0, ' ', std::cout);
		PadLeftPrint("0.Skip\n", 0, ' ', std::cout);
		while (true)
		{
			PadLeftPrint("Type your choice : ", 0, ' ', std::cout); std::cin >> choice;
			if (choice < 0 || choice>2)
			{
				PadLeftPrint("INVALID VALUE\n", 0, ' ', std::cout);
				continue;
			}
			break;
		}
		if (choice == 1)
		{
			QuickSort<Product,int>(ptr->GetFirstElement(), ptr->GetLastElement(), &Product::GetPrice, 1);

		}
		else if (choice == 2)
		{
			QuickSort<Product, int>(ptr->GetFirstElement(), ptr->GetLastElement(), &Product::GetPrice, -1);
		}
		else break;
		system("cls");
		DrawTitle(mnu::SubMenu);
		OutputTable(*ptr, std::cout);
	} while (true);
}
template void mnu::ProcessForSort<Customer>(DList<Customer*>*);
template void mnu::ProcessForSort<Bill>(DList<Bill*>*);