#include <iostream>
#include <cmath>
#include <fstream>
#include <Windows.h>
#include "String.h"
#include "Date.h"
#include "InitTemplateClass.cpp"
#include "Output.h"
#include "Exception.h"
#include "MenuManage.h"
using namespace std;
int main()
{
	DList<Product*> PList;
	DList<Customer*> CList;
	DList<Bill*> BList;
	mnu::InitMenu();
	int choice;
	mnu::Node *Mptr = mnu::TMainMenu;
	do{
		system("cls");
		try{
			if (Mptr->ptr != nullptr)
			{
				Mptr->ptr(choice);
			}
			else if (Mptr->ptr1 != nullptr)
			{
				Mptr->ptr1(PList, choice);
			}
			else if (Mptr->ptr2 != nullptr)
			{
				Mptr->ptr2(PList, choice);
			}
			else if (Mptr->ptr2 != nullptr)
			{
				Mptr->ptr2(PList, choice);
			}
			else if (Mptr->ptr3 != nullptr)
			{
				Mptr->ptr3(CList, choice);
			}
			else if (Mptr->ptr4 != nullptr)
			{
				Mptr->ptr4(CList, choice);
			}
			else if (Mptr->ptr5 != nullptr)
			{
				Mptr->ptr5(BList, PList, CList, choice);
			}
			Mptr = (Mptr->child)[choice];
		}
		catch (Exception ex)
		{
			mnu::LeftPrint(ex.What(),mnu::WIDTH);
			system("pause");
			system("cls");
		}
	} while (Mptr != nullptr);
	mnu::DeleteMenu();
	return 0;
}