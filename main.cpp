#include <iostream>
#include <cmath>
#include <fstream>
#include <Windows.h>
#include "LoHang.h"
#include "String.h"
#include "Date.h"
#include "InitTemplateClass.cpp"
#include "Output.h"
#include "Exception.h"
#include "MenuManage.h"
using namespace std;
int main()
{
	DList<Product> List;
	mnu::InitMenu();
	int choice;
	mnu::Node *Mptr = mnu::TMainMenu;
	do{
		system("cls");
		try{
			if (Mptr->ptr != NULL)
			{
				Mptr->ptr(choice);
			}
			else if (Mptr->ptr1 != NULL)
			{
				Mptr->ptr1(List, choice);
			}
			else if (Mptr->ptr2 != NULL)
			{
				Mptr->ptr2(List, choice);
			}
			Mptr = (Mptr->child)[choice];
		}
		catch (Exception ex)
		{
			mnu::LeftPrint(ex.What(),mnu::WIDTH);
			system("cls");
		}
	} while (Mptr != NULL);
	List.Release();
	mnu::DeleteMenu();
	return 0;
}