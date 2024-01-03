#ifndef MENU_MANAGE_H
#define MENU_MANAGE_H
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <exception>
#include "String.h"
#include "Exception.h"
#include "Output.h"

namespace mnu
{
	//--------------------------------INPUT_FROM KEY BOARD_PRODUCT-------------------------
	bool input_kb(DList<Product *>& List)
	{
		String id_p, name, xs, id_dp;
		Date nn, nsx, hsd;
		int calunit,price, sl;
		const int w = 47;
		do
		{
			try
			{
				LeftPrintForInput("Type the ID of product", w, ' ', cout); fflush(stdin); id_p.GetLine(cin);
				if (id_p == String("")) return false;
				id_p.Upper();
				CheckID<Product>(id_p);
				break;
			}
			catch (Exception &ex)
			{
				cout << ex.What() << endl;
			}
		} while (true);
		Product *ptrP = nullptr;
		ptrP = FindFirstMatch(List, id_p, &Product::GetID);
		if (ptrP == nullptr)
		{
			LeftPrintForInput("Type name of product", w, ' ', cout); fflush(stdin); name.GetLine(cin);
			LeftPrintForInput("Type the origin of Product", w, ' ', cout); fflush(stdin); xs.GetLine(cin); xs.Upper();
			LeftPrintForInput("Type the cost of Product", w, ' ', cout); cin >> price;			
			ptrP = new Product(id_p, name, xs,price);
			List.InsertLast(new DNode<Product*>(ptrP));
		}
		else
		{
			LeftPrintForInput("Type name of product", w, ' ', cout); cout << ptrP->GetName() << endl;
			LeftPrintForInput("Type the origin of Product", w, ' ', cout); cout << ptrP->GetXS() << endl;
			LeftPrintForInput("Type the cost of Product", w, ' ', cout); cout << MoneyFormat(String::to_string(ptrP->GetPrice())) << endl;
		}
		do
		{
			try
			{
				LeftPrintForInput("Type the ID of Batch of Product", w, ' ', cout); fflush(stdin); id_dp.GetLine(cin);	//nhap id lo hang
				id_dp.Upper();
				CheckID<DetailProduct>(id_dp);
				break;
			}
			catch (Exception &ex)
			{
				cout << ex.What() << endl;
			}
		} while (true);
		DetailProduct *ptrDP = nullptr;
		ptrDP = ptrP->FindDetailProduct(id_dp);
		if (ptrDP == nullptr)
		{
			InputAndCheck("Type the Day of Receipt Product (dd/mm/yyyy)", w, &mnu::LeftPrintForInput, nn);	//ngay nhap san pham
			InputAndCheck("Type the Manufacturing Date (dd/mm/yyyy)", w, &mnu::LeftPrintForInput, nsx);		//nhap nha san xuat
			InputAndCheck("Type the Expiration Date (dd/mm/yyyy)", w, &mnu::LeftPrintForInput, hsd);			//nhap han su dung
			if (id_p.SubStr(7, 2) == String("01"))
			{
				LeftPrintForInput("Type the weight of Product (gam)", w, ' ', cout); cin >> sl;          //nhap khoi luong hang hoa
				ptrDP = new DetailWeightProduct(id_dp, nn, nsx, hsd, sl);				
			}
			else
			{
				LeftPrintForInput("Type the quantity of Product", w, ' ', cout); cin >> sl;          //nhap so luong hang hoa
				ptrDP = new DetailProduct(id_dp, nn, nsx, hsd, sl);
			}
			ptrP->AddDetailProduct(ptrDP);
		}
		else
		{
			throw Exception(String("PRODUCT WITH ID ") + id_p + id_dp + String(" EXISTED!!!!!"));
		}
		return true;
	}
	bool input_kb(DList<Customer *>& List)
	{
		String name, add;
		Phone phone;
		const int w = 24;
		InputAndCheck("Type the Phone Number of Customer", w, &mnu::LeftPrintForInput, phone);
		if (phone == Phone("0000000000")) return false;
		Customer *ptrC = nullptr;
		ptrC = FindFirstMatch(List, phone, &Customer::GetPhone);
		if (ptrC == nullptr)
		{
			LeftPrintForInput("Type the Name of Customer", w, ' ', cout); fflush(stdin); name.GetLine(cin);
			LeftPrintForInput("Type the Address of Customer", w, ' ', cout); fflush(stdin); add.GetLine(cin);
			ptrC = new Customer(name, phone, add);
			List.InsertLast(new DNode<Customer*>(ptrC));
		}
		else
		{
			throw Exception(String("CUSTOMER WITH PHONE NUMBER ") + phone.to_string() + String(" EXISTED!!!!!"));
		}
		return true;
	}
	//---------------------------------INPUT PRODUCT--------------------------------------
	void checkformatfile(char *ptr)
	{
		if (!strcmp(ptr,""))
		{
			throw Exception("WRONG FORMAT");
		}
	}
	void input(const String &fname, DList<Product*>& List)
	{
		ifstream inp;
		inp.open(fname);
		if (inp.fail())
		{
			throw Exception("FILE NOT EXIST");
		}
		Date nn (fname,".");
		{
			String temp;
			temp.GetLine(inp);
		}// Skip dong dau tien
		int cnt = 0;
		while (!inp.eof())
		{
			cnt++;
			try
			{
				String temp;
				temp.GetLine(inp);
				char *ptr;
				String id_p = strtok_s(temp, ",", &ptr);
				checkformatfile(ptr);
				String name = strtok_s(nullptr, ",", &ptr);
				checkformatfile(ptr);
				String xs = strtok_s(nullptr, ",", &ptr);
				checkformatfile(ptr);
				String id_dp = strtok_s(nullptr, ",", &ptr);
				checkformatfile(ptr);
				String nsx_str = strtok_s(nullptr, ",", &ptr);
				checkformatfile(ptr);
				String hsd_str = strtok_s(nullptr, ",", &ptr);
				checkformatfile(ptr);
				String price_str = strtok_s(nullptr, ",", &ptr);
				int price = atoi(price_str);
				String sl_str = strtok_s(nullptr, ",", &ptr);
				int sl = atoi(sl_str);
				// initialize new product
				Product *ptrP = nullptr;
				ptrP = new Product(id_p, name, xs, price);
				DetailProduct * ptrDP = nullptr;
				if (id_p.SubStr(7, 2) == String("01"))
				{
					ptrDP = new DetailWeightProduct(id_dp, nn, Date(nsx_str), Date (hsd_str), sl);
				}
				else
				{
					ptrDP = new DetailProduct(id_dp, nn, Date(nsx_str), Date(hsd_str), sl);
				}

				if (!InsertProduct(List, ptrP, ptrDP))
				{
					String mess = String ("Entry ")+String::to_string(cnt)+ String(" PRODUCT WITH ID ") + id_p + id_dp + String(" EXISTED!!!!!");
					PadLeftPrint(mess, mnu::LEFTSPACE, ' ', std::cout);
					std::cout << endl;
				}
			}
			catch (Exception &ex)
			{
				String mess = String("Entry ") + String::to_string(cnt) + String(" ") + ex.What();
				PadLeftPrint(mess, mnu::LEFTSPACE, ' ', std::cout);
				std::cout << endl;
			}
		}
		
		inp.close();
	}
	void input(const String &fname, DList<Customer*>& List)
	{
		ifstream inp;
		inp.open(fname);
		if (inp.fail())
		{
			throw Exception("FILE NOT EXIST");
		}
		{
			String temp;
			temp.GetLine(inp);
		}// Skip dong dau tien
		int cnt = 0;
		while (!inp.eof())
		{
			cnt++;
			try 
			{
				String temp;
				fflush(stdin); temp.GetLine(inp);
				char *ptr;
				String name = strtok_s(temp, ",", &ptr);
				checkformatfile(ptr);
				String phone_str = strtok_s(nullptr, ",", &ptr);
				checkformatfile(ptr);
				String add = strtok_s(nullptr, ",", &ptr);
				Customer *ptrC = new Customer(name, Phone(phone_str), add);
				bool check;
				InsertCustomer(List, ptrC, check);
				if (!check)
				{
					String mess =String("ENTRY ")+ String::to_string(cnt)+ String(" CUSTOMER WITH PHONE NUMBER ") + phone_str + String(" EXISTED!!!!!");
					PadLeftPrint(mess, mnu::LEFTSPACE, ' ', cout);
					cout << endl;
				}
			}
			catch (Exception &ex)
			{
				String mess = String("ENTRY ") + String::to_string(cnt) + String(" ") + ex.What();
				PadLeftPrint(mess, mnu::LEFTSPACE, ' ', cout);
				cout << endl;
			}
		}
		inp.close();
	}
	//---------------------------------INPUT BILL HIDEN FUNC----------------------------------------

	//--------------------------------
	
	void InputBill(const String &fname, DList<Bill*> &BList, DList<Product*> &PList, DList<Customer*> &CList)
	{
		ifstream f_i(fname);
		String c_name = "", address = "";
		Phone phone;
		Date buydate;
		Time buytime;
		while (!f_i.eof())
		{
			f_i >> buydate;
			f_i >> buytime;
			f_i.ignore();
			f_i >> phone;
			Customer* ptrC = nullptr; bool inserted = false;
			c_name.GetLine(f_i);
			address.GetLine(f_i);
			ptrC = InsertCustomer(CList, new Customer(c_name, phone, address), inserted);
			int numOfProduct;
			f_i >> numOfProduct;
			int cnt = 0;
			int total = 0;
			Bill *ptrB = new Bill(buydate, buytime);
			do
			{
				String id_p; int sl;
				f_i.ignore();
				id_p.GetLine(f_i);
				String p_id, dp_id;
				p_id = id_p.SubStr(0, 9);
				dp_id = id_p.SubStr(9, 4);
				Product* ptrP = FindFirstMatch(PList, p_id, &Product::GetID);
				DetailProduct* ptrDP = ptrP->FindDetailProduct(dp_id);
				cnt++;
				f_i >> sl;
				total += ptrDP->Calculate(sl);
				DetailBill *ptrDB = new DetailBill(ptrDP, sl);
				ptrDP->Deduct(sl);
				ptrDP->AddDetailBill(ptrDB);
				ptrB->AddDetailBill(ptrDB);
			} while (cnt < numOfProduct);
			ptrB->SetTotal(total);
			ptrB->SetNumDetailBill(cnt);
			ptrC->AddBill(ptrB);
			InsertBill(BList, ptrB);
		}
		f_i.close();
	}
	//---------------------------------Chuc nang TKSP-----------------------------------------------
	namespace search_mnu
	{
		bool stilluse = false;
	}
	// --ID---
	template <typename T>
	void Search_ID(const DList<T*>& List, int &choice)
	{
		static DList<T*>* ptrAns_List_For_Search = nullptr;
		static int cnt_Search = 0;
		bool all = false;
		DrawTitle(mnu::SubMenu);
		if (!search_mnu::stilluse)
		{
			if (ptrAns_List_For_Search != nullptr)
			{
				delete ptrAns_List_For_Search;
			}
			ptrAns_List_For_Search = nullptr;
			cnt_Search = 0;
			String data_lookup;
			do
			{
				try
				{
					PadLeftPrint("Type the ID for searching :", mnu::LEFTSPACE, ' ', cout); fflush(stdin); data_lookup.GetLine(cin);
					if (data_lookup == String("*"))
					{
						all = true;
						break;
					}
					data_lookup.Upper();
					CheckID<T>(data_lookup);
					break;
				}
				catch (exception &ex)
				{
					PadLeftPrint(ex.what(), mnu::LEFTSPACE, ' ', cout);
					cout << endl;
				}
			} while (true);
			if (!all)
			{
				T *ptr = FindFirstMatch(List, data_lookup, &T::GetID);
				OutputDetail(ptr, cout);
				if (ptr != nullptr)
				{
					ProcessAfterSearch<T>(ptr);
				}
				choice = 2;
				system("pause");
				return;
			}
			ptrAns_List_For_Search = FindAll(List, false, &T::Deleted, cnt_Search);
			search_mnu::stilluse = true;
		}
		OutputTable(*ptrAns_List_For_Search, cout);
		if (cnt_Search == 0)
		{
			system("pause");
			search_mnu::stilluse = false;
			choice = 2;
			return;
		}
		ProcessForSort<T>(ptrAns_List_For_Search);
		PadLeftPrint("Type ordinal number of entry to view its Detail (Type '0' to return) : ", 0, ' ', cout); cin >> choice;
		if (choice<0 || choice>cnt_Search)
		{
			fflush(stdin);
			cin.clear();
			throw Exception("INVALID VALUE");
		}
		if (choice == 0)
		{
			search_mnu::stilluse = false;
			return;
		}
		else
		{
			system("cls");
			DrawTitle(mnu::SubMenu);
			T * ptr = FindIndex(*ptrAns_List_For_Search, choice);
			OutputDetail(ptr, cout);
			ProcessAfterSearch<T>(ptr);
			choice = 1;
		}
	}
	//--NAME---
	template<class T>
	void Search_Name(const DList<T*>& List, int &choice)
	{
		static DList<T*>* ptrAns_List_For_Search = nullptr;
		static int cnt_Search = 0;
		DrawTitle(mnu::SubMenu);
		if (!search_mnu::stilluse)
		{
			if (ptrAns_List_For_Search != nullptr)
			{
				delete ptrAns_List_For_Search;
			}
			ptrAns_List_For_Search = nullptr;
			cnt_Search = 0;
			String data_lookup;
			PadLeftPrint("Type the name for searching :",mnu::LEFTSPACE,' ',cout); fflush(stdin); data_lookup.GetLine(cin);
			ptrAns_List_For_Search = FindAll(List, data_lookup, &T::GetName, cnt_Search);
			search_mnu::stilluse = true;
		}
		OutputTable(*ptrAns_List_For_Search,cout);
		if (cnt_Search == 0)
		{
			system("pause");
			search_mnu::stilluse = false;
			choice = 2;
			return;
		}
		ProcessForSort<T>(ptrAns_List_For_Search);
		PadLeftPrint("Type ordinal number of entry to view its Detail (Type '0' to return) : ", 0,' ',cout); cin >> choice; 
		if (choice<0 || choice>cnt_Search)
		{
			fflush(stdin);
			cin.clear();
			throw Exception("INVALID VALUE");
		}
		if (choice == 0)
		{
			search_mnu::stilluse = false;
			return;
		}
		else
		{
			system("cls");
			DrawTitle(mnu::SubMenu);
			T * ptr = FindIndex(*ptrAns_List_For_Search, choice);
			OutputDetail(ptr,cout);
			ProcessAfterSearch<T>(ptr);
			system("pause");
			choice = 1;
		}
	}
	//--Xuat SU --
	void Search_XS(const DList<Product*>& List, int &choice)
	{
		static DList<Product*>* ptrAns_List_For_Search;
		static int cnt_Search;
		DrawTitle(mnu::SubMenu);
		if (!search_mnu::stilluse)
		{
			if (ptrAns_List_For_Search != nullptr)
			{
				delete ptrAns_List_For_Search;
			}
			ptrAns_List_For_Search = nullptr;
			cnt_Search = 0;
			String data_lookup;
			PadLeftPrint("Type origin for searching :", mnu::LEFTSPACE, ' ', cout); fflush(stdin); data_lookup.GetLine(cin); data_lookup.Upper();
			ptrAns_List_For_Search = FindAll(List, data_lookup, &Product::GetXS, cnt_Search);
			search_mnu::stilluse = true;
		}
		OutputTable(*ptrAns_List_For_Search,cout);
		if (cnt_Search == 0)
		{
			system("pause");
			search_mnu::stilluse = false;
			choice = 2;
			return;
		}
		ProcessForSort<Product>(ptrAns_List_For_Search);
		PadLeftPrint("Type ordinal number of entry to view its Detail (Type '0' to return)\n", 0, ' ', cout); cin >> choice;
		if (choice<0 || choice>cnt_Search)
		{
			fflush(stdin);
			cin.clear();
			throw Exception("INVALID VALUE");
		}
		if (choice == 0)
		{
			search_mnu::stilluse = false;
			return;
		}
		else
		{
			system("cls");
			DrawTitle(mnu::SubMenu);
			Product * ptr = FindIndex(*ptrAns_List_For_Search, choice);
			OutputDetail(ptr,cout);
			ProcessAfterSearch<Product>(ptr);
			system("pause");
			choice = 1;
		}
	}
	//-----SDT----
	void Search_Phone(const DList<Customer*>& List, int &choice)
	{
		static DList<Customer*>* ptrAns_List_For_Search;
		static int cnt_Search;
		bool all = false;
		DrawTitle(mnu::SubMenu);
		if (!search_mnu::stilluse)
		{
			if (ptrAns_List_For_Search != nullptr)
			{
				delete ptrAns_List_For_Search;
			}
			ptrAns_List_For_Search = nullptr;
			cnt_Search = 0;
			String data_lookup;
			do
			{
				try
				{
					PadLeftPrint("Type phone number for searching : ", mnu::LEFTSPACE, ' ', cout); fflush(stdin); data_lookup.GetLine(cin);
					if (data_lookup == String("*"))
					{
						all = true;
						break;
					}
					CheckPhone(data_lookup);
					break;
				}
				catch (Exception &ex)
				{
					PadLeftPrint(ex.What(), mnu::LEFTSPACE, ' ', cout);
					cout << endl;
				}
			} while (true);
			if (!all)
			{
				Phone phone(data_lookup);
				system("cls");
				DrawTitle(mnu::SubMenu);
				Customer *ptr = FindFirstMatch(List, phone, &Customer::GetPhone);
				OutputDetail(ptr, cout);
				if (ptr != nullptr)
				{
					ProcessAfterSearch<Customer>(ptr);
				}
				choice = 2;
				system("pause");
				return;
			}
			ptrAns_List_For_Search = FindAll(List, false, &Customer::Deleted, cnt_Search);
			search_mnu::stilluse = true;
		}
		system("cls");
		DrawTitle(mnu::SubMenu);
		OutputTable(*ptrAns_List_For_Search, cout);
		if (cnt_Search == 0)
		{
			system("pause");
			search_mnu::stilluse = false;
			choice = 2;
			return;
		}
		PadLeftPrint("Type ordinal number of entry to view its detail (Type '0' to return) : ", 0, ' ', cout); cin >> choice;
		if (choice<0 || choice>cnt_Search)
		{
			fflush(stdin);
			cin.clear();
			throw Exception("INVALID VALUE");
		}
		if (choice == 0)
		{
			search_mnu::stilluse = false;
			return;
		}
		else
		{
			system("cls");
			DrawTitle(mnu::SubMenu);
			Customer * ptr = FindIndex(*ptrAns_List_For_Search, choice);
			OutputDetail(ptr, cout);
			ProcessAfterSearch<Customer>(ptr);
			choice = 1;
		}
	}
	//---Ngay mua-------
	void Search_BuyDate(const DList<Bill*>& List, int & choice)
	{
		static DList<Bill*>* ptrAns_List_For_Search;
		static int cnt_Search;
		DrawTitle(mnu::SubMenu);
		if (!search_mnu::stilluse)
		{
			if (ptrAns_List_For_Search != nullptr)
			{
				delete ptrAns_List_For_Search;
			}
			ptrAns_List_For_Search = nullptr;
			cnt_Search = 0;
			Date data_lookup;
			InputAndCheck("Type buy date for searching : ", mnu::LEFTSPACE, &mnu::PadLeftPrint, data_lookup);
			ptrAns_List_For_Search = FindAll(List, data_lookup, &Bill::GetBuyDate, cnt_Search);
			search_mnu::stilluse = true;
		}
		OutputTable(*ptrAns_List_For_Search,cout);
		if (cnt_Search == 0)
		{
			system("pause");
			search_mnu::stilluse = false;
			choice = 2;
			return;
		}
		PadLeftPrint("Type ordinal number of entry to view its detail (Type '0' to return) : ", 0, ' ', cout); cin >> choice;
		if (choice<0 || choice>cnt_Search)
		{
			fflush(stdin);
			cin.clear();
			throw Exception("INVALID VALUE");
		}
		if (choice == 0)
		{
			search_mnu::stilluse = false;
			return;
		}
		else
		{
			system("cls");
			DrawTitle(mnu::SubMenu);
			Bill * ptr = FindIndex(*ptrAns_List_For_Search, choice);
			OutputDetail(ptr,cout);
			ProcessAfterSearch<Bill>(ptr);
			choice = 1;
		}
	}
	//---SDT Bill---
	void Search_Phone_Bill(const DList<Bill*>& List, int & choice)
	{
		static DList<Bill*>* ptrAns_List_For_Search;
		static int cnt_Search;
		DrawTitle(mnu::SubMenu);
		if (!search_mnu::stilluse)
		{
			if (ptrAns_List_For_Search != nullptr)
			{
				delete ptrAns_List_For_Search;
			}
			ptrAns_List_For_Search = nullptr;
			cnt_Search = 0;
			Phone data_lookup;
			InputAndCheck("Type phone number for searching : ", mnu::LEFTSPACE, &mnu::PadLeftPrint, data_lookup);
			ptrAns_List_For_Search = FindAll(List, data_lookup, &Bill::GetCustomerPhone, cnt_Search);
			search_mnu::stilluse = true;
		}
		OutputTable(*ptrAns_List_For_Search,cout);
		if (cnt_Search == 0)
		{
			system("pause");
			search_mnu::stilluse = false;
			choice = 2;
			return;
		}
		PadLeftPrint("Type ordinal number of entry to view its detail (Type '0' to return) : ", 0, ' ', cout); cin >> choice;
		if (choice<0 || choice>cnt_Search)
		{
			fflush(stdin);
			cin.clear();
			throw Exception("INVALID VALUE");
		}
		if (choice == 0)
		{
			search_mnu::stilluse = false;
			return;
		}
		else
		{
			system("cls");
			DrawTitle(mnu::SubMenu);
			Bill * ptr = FindIndex(*ptrAns_List_For_Search, choice);
			OutputDetail(ptr,cout);
			ProcessAfterSearch<Bill>(ptr);
			choice = 1;
		}
	}
	//----------------------------------template nhap tu file-------------------------------------------------
	template<class T>
	void Nhap(DList<T*> & List, int & choice)
	{
		DrawTitle(mnu::SubMenu);
		PadLeftPrint("Type the name of the file : ",mnu::LEFTSPACE,' ',cout);
		String fname;
		fflush(stdin); fname.GetLine(cin);
		if (fname == String(""))
		{
			choice = 0;
			return;
		}
		try
		{
			input(fname, List);
			CenterPrint("INPUT SUCCESSFULLY",mnu::WIDTH,' ',cout);
		}
		catch (Exception &ex)
		{
			CenterPrint(ex.What(), mnu::WIDTH, ' ', cout);
		};
		Pause();
		choice = 1;
	}
	//----------------------------------template nhap tu ban phim-------------------------------------------------
	template<class T>
	void Nhap_kb(DList<T*> & List, int & choice)
	{
		DrawTitle(mnu::SubMenu);
		if (input_kb(List))	PadLeftPrint("SUCCESSFUL INPUT", mnu::LEFTSPACE, ' ', cout);
		Sleep(mnu::WAIT);
		choice = 1;
	}
	//-----------------------------------MAIN MENU------------------------------------------------
	void MainMenu(int& choice)
	{
		mnu::SubMenu = -1;
		DrawTitle(mnu::SubMenu);
		PadLeftPrint("1.Product Management", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("2.Customer Management", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("3.Bill Management", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("4.Payment", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("0.Quit", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("Type your choice :", mnu::LEFTSPACE, ' ', cout); std::cin >> choice; mnu::SubMenu = choice - 1;
		if (choice < 0 || choice>4)
		{
			fflush(stdin);
			cin.clear(); 
			throw Exception("INVALID VALUE");
		}
	}
	//---------------------------------------QUAN LY MAT HANG---------------------------------------
	//---QUAN LY MAT HANG HET HSD----
	void ManageExpiration(const DList<Product*>& List, int &choice)
	{
		DrawTitle(mnu::SubMenu);
		static DList<DetailProduct *> *ptrAnsList = nullptr;
		int day;
		if (ptrAnsList == nullptr)
		{
			cout << "Type day(s) you want to check for Product Expiration : "; cin >> day;
			if (day < 0)
			{
				fflush(stdin);
				cin.clear();
				throw Exception("INVALID VALUE");
			}
			ptrAnsList = OutOfExpiration(List, day);
		}
		OutputExpiredDetailProduct(*ptrAnsList,cout);
		if (ptrAnsList->GetFirstElement() == nullptr)
		{
			Sleep(mnu::WAIT);
			if (ptrAnsList != nullptr)
			{
				delete ptrAnsList;
				ptrAnsList = nullptr;
			}
			choice = 0;
			return;
		}
		cout << "\nDo you want to delete all of above products ?\n";
		cout << "1.Delete all\n";
		cout << "0.Keep all and return\n";
		cout << "Type your choice : "; cin >> choice;
		if (choice < 0 || choice>1)
		{
			fflush(stdin);
			cin.clear();
			throw Exception("INVALID VALUE");
		}
		if (choice == 1)
		{
			DNode<DetailProduct*>* curPtr = ptrAnsList->GetFirstElement();
			while (curPtr != nullptr)
			{
				(curPtr->data)->Delete();
				curPtr = curPtr->next;
			}
			CenterPrint("SUCCESSFUL DELETE", mnu::WIDTH,' ',cout);
			Sleep(mnu::WAIT);
		}
		if (ptrAnsList != nullptr)
		{
			delete ptrAnsList;
			ptrAnsList = nullptr;
		}
		choice = 0;
	}
	//------------------------------------MENU 1----------------------------------------------------
	void Menu1(int &choice)
	{
		DrawTitle(mnu::SubMenu);
		PadLeftPrint("1.Add new Product(s)", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("2.Search Product", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("3.Product expiration management", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("0.Return", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("Type your choice :", mnu::LEFTSPACE, ' ', cout); std::cin >> choice;
		if (choice < 0 || choice>3)
		{
			fflush(stdin);
			cin.clear();
			throw Exception("INVALID VALUE");
		}
	}
	//----------------------------------MENU 1/2-1 ------------------------------------------------------
	void Menu12_1(int &choice)
	{
		DrawTitle(mnu::SubMenu);
		PadLeftPrint("1.Add from file", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("2.Add from keyboard", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("0.Return", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("Type your choice :", mnu::LEFTSPACE, ' ', cout); std::cin >> choice;
		if (choice < 0 || choice>2)
		{
			fflush(stdin);
			cin.clear();
			throw Exception("INVALID VALUE");
		}
	}
	
	//----------------------------------MENU 1-2 ------------------------------------------------------
	void Menu1_2(int& choice)
	{
		DrawTitle(mnu::SubMenu);
		PadLeftPrint("1.Search by ID of Product", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("2.Search by Name of Product", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("3.Search by Origin of Product", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("0.Return", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("Type your choice :", mnu::LEFTSPACE, ' ', cout); cin >> choice;
		if (choice < 0 || choice>3)
		{
			fflush(stdin);
			cin.clear();
			throw Exception("INVALID VALUE");
		}
	}
	//-----------------------------------QUAN LY KHACH HANG------------------------------------------
	//----------------------------------MENU 2 --------------------------------------------------------
	void Menu2(int &choice)
	{
		DrawTitle(mnu::SubMenu);
		PadLeftPrint("1.Add new Customer(s)", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("2.Search Customer", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("3.Update information of Customer", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("0.Return", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("Type your choice :", mnu::LEFTSPACE, ' ', cout); cin >> choice;
		if (choice < 0 || choice>3)
		{
			fflush(stdin);
			cin.clear();
			throw Exception("INVALID VALUE");
		}
	}
	//-------------------------------MENU 2-1 --------------------------------------------
	// TRUNG VOI MENU 1-1
	//----------------------------------MENU 2-2 ------------------------------------------------------
	void Menu2_2(int& choice)
	{
		DrawTitle(mnu::SubMenu);
		PadLeftPrint("1.Search by Phone Number of customer", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("2.Search by Name of customer", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("0.Return", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("Type your choice :", mnu::LEFTSPACE, ' ', cout); cin >> choice;
		if (choice < 0 || choice>2)
		{
			fflush(stdin);
			cin.clear();
			throw Exception("INVALID VALUE");
		}
	}
	//----Update thong tin khach hang---------
	void ChangeCustomerInfo(DList<Customer*>& List, int & choice)
	{
		DrawTitle(mnu::SubMenu);
		Phone phone;
		InputAndCheck("Type the Phone Number of Customer needed to Update : ", mnu::LEFTSPACE, &mnu::PadLeftPrint, phone);
		Customer * ptrC = FindFirstMatch(List, phone, &Customer::GetPhone);
		if (ptrC == nullptr)
		{
			OutputDetail(ptrC,cout);
			Sleep(mnu::WAIT);
			choice = 1;
			return;
		}
		system("cls");
		DrawTitle(mnu::SubMenu);
		OutputDetail(ptrC,cout);
		PadLeftPrint("Choose the information need updating", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("1.Name", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("2.Phone number", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("3.Address", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("0.Return", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("Type your choice : ", mnu::LEFTSPACE, ' ', cout); cin >> choice;
		if (choice < 0 || choice>3)
		{
			fflush(stdin);
			cin.clear();
			throw Exception("INVALID VALUE");
		}
		if (choice == 0)
		{
			return;
		}
		system("cls");
		DrawTitle(mnu::SubMenu);
		switch (choice)
		{
			case 1:
			{
				String update_info;
				cout << "Type the new name : ";
				fflush(stdin); update_info.GetLine(cin);
				if (update_info != String(""))
					ptrC->SetName(update_info);
				break;
			}
			case 2:
			{
				Phone update_info;
				InputAndCheck("Type the new phone number : ", 0, &mnu::LeftPrint, update_info);
				if (update_info != Phone("0000000000"))
					ptrC->SetPhone(update_info);
				break;
			}
			case 3:
			{
				String update_info;
				cout << "Type the new address : ";
				fflush(stdin); update_info.GetLine(cin);
				if (update_info != String(""))
					ptrC->SetAddress(update_info);
				break;
			}
		}
		choice = 1;
	}
	//----------------------------------QUAN LY HOA DON--------------------------------------
	void BillCalculate(DList<Bill*>& BList, DList<Product*>& PList, DList<Customer*>& CList, int &choice)
	{
		DrawTitle(mnu::SubMenu);
		int w = 30;
		String c_name="",address="";
		Phone phone;
		Date buydate=Today();
		Time buytime=Now();
		LeftPrintForInput("Date", w, ' ', cout); cout << buydate << endl;
		LeftPrintForInput("Time", w, ' ', cout); cout << buytime << endl;
		InputAndCheck("Type customer 's phone number", w, &mnu::LeftPrintForInput, phone);
		bool inserted = false;
		Customer* ptrC = InsertCustomer(CList, new Customer(c_name, phone, address), inserted);
		if (phone != Phone("0000000000")) // Khach hang muon luu thong tin hay ko
		{
			if (inserted)
			{
				LeftPrintForInput("Name of Customer", w, ' ', cout); fflush(stdin); c_name.GetLine(cin);
				if (c_name != String(""))
				{
					LeftPrintForInput("Address of Customer", w, ' ', cout); fflush(stdin); address.GetLine(cin);
				}
				else 
				ptrC->SetName(c_name);
				ptrC->SetAddress(address);
			}
			else
			{
				LeftPrintForInput("Name of Customer", w, ' ', cout); cout << ptrC->GetName() << endl;
				LeftPrintForInput("Address of Customer", w, ' ', cout); cout << ptrC->GetAddress() << endl;
			}
		}	
		int cnt = 0;
		int total = 0;
		Bill *ptrB = new Bill(buydate,buytime);
		do
		{
			std::cout << "\n\n" << '+'; DrawLine(mnu::WIDTH - 2, '=',cout); std::cout << '+' << "\n\n";
			String id_p; int sl;
			LeftPrintForInput("Type the ID of the product", w, ' ', cout); fflush(stdin); id_p.GetLine(cin);
			id_p.Upper();
			if (id_p == String("")) break;
			String p_id, dp_id;
			if (id_p.GetLength() != 13)
			{
				cout << "INVALID PRODUCT ID\n";
				continue;
			}
			p_id = id_p.SubStr(0, 9);
			dp_id = id_p.SubStr(9, 4);
			Product* ptrP = FindFirstMatch(PList, p_id, &Product::GetID);
			if (ptrP == nullptr)
			{
				cout << "Product Not found\n";
				continue;
			}
			DetailProduct* ptrDP = ptrP->FindDetailProduct(dp_id);
			if (ptrDP == nullptr)
			{
				cout << "Product Not found\n";
				continue;
			}
			String type = id_p.SubStr(7, 2),q_str;
			if (type == String("01"))
			{
				q_str = "weight(unit: gram)";
			}
			else
			{
				q_str = "quantity";
			}
			LeftPrintForInput("Name of product", w, ' ', cout); cout << ptrP->GetName()<<endl;
			LeftPrintForInput("Receipt date", w, ' ', cout); cout << ptrDP->GetNN()<<endl;
			LeftPrintForInput("Manufacturing date", w, ' ', cout); cout << ptrDP->GetNSX()<<endl;
			LeftPrintForInput("Expiration date", w, ' ', cout); cout << ptrDP->GetHSD()<<endl;
			LeftPrintForInput("Price", w, ' ', cout); cout << ptrDP->GetPrice()<<endl;
			LeftPrintForInput(String("Remained ")+q_str, w, ' ', cout); cout << ptrDP->GetSL()<<endl;
			cnt++;
			do
			{
				try
				{
					LeftPrintForInput(String("Type the ")+q_str, w, ' ', cout);
					cin >> sl;
					if (sl > ptrDP->GetSL())
					{
						throw Exception(String("REMAINED ") + q_str + String(" NOT ENOUGH"));
					}
					break;
				}
				catch (Exception &ex)
				{
					cout << ex.What()<<endl;
				}
			} while (true);
			if (sl > 0)
			{
				total += ptrDP->Calculate(sl);
				DetailBill *ptrDB = new DetailBill(ptrDP, sl);
				//ptrDP->Deduct(sl);
				//ptrDP->AddDetailBill(ptrDB);
				ptrB->AddDetailBill(ptrDB);
			}
		} while (true);
		if (cnt == 0)
		{
			delete ptrB;
			if (inserted)
			{
				CList.RemoveLast();
			}
			choice = 1;
			return;
		}
		ptrB->SetTotal(total);
		ptrB->SetNumDetailBill(cnt);
		ptrC->AddBill(ptrB);
		system("cls");
		DrawTitle(mnu::SubMenu);
		OutputDetail(ptrB, cout);
		cout << "PRESS y TO CONFIRM BILL\n";
		char y = _getch();
		if (y == 'y' || y == 'Y')
		{
			ptrB->Confirm();
			InsertBill(BList, ptrB);
			cout << "PRESS p TO PRINT BILL";
			char p = _getch();
			if (p == 'p' || p == 'P')
			{
				OutputBillFile(ptrB->GetID(), ptrB);
			}
		}
		else
		{
			ptrB->Cancel();
			delete ptrB;
		}
		choice = 1;
	}
	//----------TINH DOANH THU-------------------
	void Revenue(const DList<Bill*> &List, int &choice)
	{
		DrawTitle(mnu::SubMenu);
		cout << "Type the period of time you want to calculate Revenue\n";
		int w = 20;
		Date s, f;
		InputAndCheck("From date", w, &mnu::LeftPrintForInput, s);
		InputAndCheck("To date", w, &mnu::LeftPrintForInput, f);
		DList<Bill*> AnsList;
		int total_revenue = CalRevenue(List, s, f, AnsList);
		OutputTable(AnsList,cout);
		cout << '|'; CenterPrint("TOTAL OF REVENUE", w,' ',cout);
		cout << '|'; CenterPrint(MoneyFormat(String::to_string(total_revenue)), mnu::WIDTH - 3 - w, ' ', cout); cout << '|' << endl;
		cout << '+'; DrawLine(mnu::WIDTH - 2, '=',cout); cout << '+' << endl;
		system("pause");
		choice = 1;
	}
	//----------------------------------MENU3--------------------------------------------------
	void Menu3(int &choice)
	{
		DrawTitle(mnu::SubMenu);
		PadLeftPrint("1.Calculate Revenue", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("2.Search the invoice for the product.", mnu::LEFTSPACE, ' ', cout); cout << '\n';	//truy xuat hoa don
		PadLeftPrint("0.Return", mnu::LEFTSPACE, ' ', cout); cout << "\n";
		PadLeftPrint("Type your choice :", mnu::LEFTSPACE, ' ', cout); cin >> choice;
		if (choice < 0 || choice>2)
		{
			fflush(stdin);
			cin.clear();
			throw Exception("INVALID VALUE");
		}
	}
	//----------------------------------Menu3_3----------------------------------------------
	void Menu3_2(int &choice)
	{
		DrawTitle(mnu::SubMenu);
		PadLeftPrint("1.Search bill by ID", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("2.Search bill by customers' phone number", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("3.Search bill by buy date", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("0.Return", mnu::LEFTSPACE, ' ', cout); cout << "\n";
		PadLeftPrint("Type your choice :", mnu::LEFTSPACE, ' ', cout); cin >> choice;
		if (choice < 0 || choice>3)
		{
			fflush(stdin);
			cin.clear();
			throw Exception("INVALID VALUE");
		}
	}
	//-----------------------------------MENU TT----------------------------------------------
	void MenuTT(int &choice)
	{
		DrawTitle(mnu::SubMenu);
		PadLeftPrint("1.Continue", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("0.Return", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("Type your choice :", mnu::LEFTSPACE, ' ', cout); std::cin >> choice;
		if (choice < 0 || choice>1)
		{
			fflush(stdin);
			cin.clear();
			throw Exception("INVALID VALUE");
		}
	}
	//-------------------------------------MENU TT CHO TM KIEM ----------------------------------
	void MenuTTTK(int &choice)
	{
		DrawTitle(mnu::SubMenu);
		PadLeftPrint("Do you want to continue ?", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("1.Continue with current query", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("2.Continue with new query", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("0.Return", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("Type your choice :", mnu::LEFTSPACE, ' ', cout); std::cin >> choice;
		if (choice < 0 || choice>2)
		{
			fflush(stdin);
			cin.clear();
			throw Exception("INVALID VALUE");
		}
		if (choice == 2 || choice == 0)
		{
			search_mnu::stilluse = false;
		}
	}

	
	//---------------------------Create Menu Tree----------------------------------------
	struct Node
	{
		void(*ptr) (int&) = nullptr;
		void(*ptr1) (DList<Product*>&, int&) = nullptr;
		void(*ptr2) (const DList<Product*>&, int&) = nullptr;
		void(*ptr3) (DList<Customer*>&, int&) = nullptr;
		void(*ptr4) (const DList<Customer*>&, int&) = nullptr;
		void(*ptr5) (DList<Bill*>&, DList<Product*>&, DList<Customer*>&, int&) = nullptr;
		void(*ptr6) (const DList<Bill*>&, int&) = nullptr;
		void(*ptr7) (DList<Bill*>&, int&) = nullptr;
		int num_child;
		Node ** child;
		//---------------------vs0------------------------------
		Node(void(*ptr) (int&), int num)
			:ptr(ptr), num_child(num)
		{
			this->child = new Node*[this->num_child]{nullptr};
		}
		//---------------------vs1-----------------------------
		Node(void(*ptr1) (DList<Product*>&, int&), int num)
			:ptr1(ptr1),  num_child(num)
		{
			if (this->num_child > 0)
				this->child = new Node*[this->num_child]{nullptr};
			else this->child = nullptr;
		}
		//---------------------vs2------------------------------
		Node(void(*ptr2) (const DList<Product*>&, int&), int num)
			: ptr2(ptr2), num_child(num)
		{
			if (this->num_child > 0)
				this->child = new Node*[this->num_child]{nullptr};
			else this->child = nullptr;
		}
		//---------------------vs3------------------------------
		Node(void(*ptr3) (DList<Customer*>&, int&), int num)
			: ptr3(ptr3), num_child(num)
		{
			if (this->num_child > 0)
				this->child = new Node*[this->num_child]{nullptr};
			else this->child = nullptr;
		}
		//---------------------vs4------------------------------
		Node(void(*ptr4) (const DList<Customer*>&, int&), int num)
			: ptr4(ptr4), num_child(num)
		{
			if (this->num_child > 0)
				this->child = new Node*[this->num_child]{nullptr};
			else this->child = nullptr;
		}
		//---------------------vs5------------------------------
		Node(void(*ptr5) (DList<Bill*>&, DList<Product*>&, DList<Customer*>&, int&), int num)
			: ptr5(ptr5), num_child(num)
		{
			if (this->num_child > 0)
				this->child = new Node*[this->num_child]{nullptr};
			else this->child = nullptr;
		}
		//---------------------vs6------------------------------
		Node(void(*ptr6) (const DList<Bill*>&, int&), int num)
			: ptr6(ptr6), num_child(num)
		{
			if (this->num_child > 0)
				this->child = new Node*[this->num_child]{nullptr};
			else this->child = nullptr;
		}
		Node(void(*ptr7) ( DList<Bill*>&, int&), int num)
			: ptr7(ptr7), num_child(num)
		{
			if (this->num_child > 0)
				this->child = new Node*[this->num_child]{nullptr};
			else this->child = nullptr;
		}
		//--------------------------------------------------------
		~Node()
		{
			delete this->child;
		}
		void AddChild(Node *node, int index)
		{
			(this->child)[index] = node;
			(node->child)[0] = this;
		}
		void AddChild_TT(Node *node, int index)
		{
			(this->child)[index] = node;
			(node->child)[1] = this;
			(node->child)[0] = (this->child)[0];
		}
		void AddChild_TTTK(Node *node, int index)
		{
			(this->child)[index] = node;
			(node->child)[1] = (node->child)[2] = this;
			(node->child)[0] = (this->child)[0];
		}
	};
	Node *TMainMenu = new Node(&MainMenu, 5);

	Node *TMenu1 = new Node(&Menu1, 4);
	Node *TMenu1_1 = new Node(&Menu12_1, 3);
	Node *TMenu1_1_1 = new Node(&Nhap<Product>, 2);
	Node *TMenu1_1_1_TT = new Node(&MenuTT, 2);
	Node *TMenu1_1_2 = new Node(&Nhap_kb<Product>, 2);
	Node *TMenu1_1_2_TT = new Node(&MenuTT, 2);
	Node *TMenu1_2 = new Node(&Menu1_2, 4);
	Node *TMenu1_2_1 = new Node(&Search_ID<Product>, 3);
	Node *TMenu1_2_1_TTTK = new Node(&MenuTTTK, 3);
	Node *TMenu1_2_1_TT = new Node(&MenuTT, 2);
	Node *TMenu1_2_2 = new Node(&Search_Name<Product>, 3);
	Node *TMenu1_2_2_TTTK = new Node(&MenuTTTK, 3);
	Node *TMenu1_2_2_TT = new Node(&MenuTT, 2);
	Node *TMenu1_2_3 = new Node(&Search_XS, 3);
	Node *TMenu1_2_3_TTTK = new Node(&MenuTTTK, 3);
	Node *TMenu1_2_3_TT = new Node(&MenuTT, 2);
	Node *TMenu1_3 = new Node(&ManageExpiration, 1);

	Node *TMenu2 = new Node(&Menu2, 4);
	Node *TMenu2_1 = new Node(&Menu12_1, 3);
	Node *TMenu2_1_1 = new Node(&Nhap<Customer>, 2);
	Node *TMenu2_1_1_TT = new Node(&MenuTT, 2);
	Node *TMenu2_1_2 = new Node(&Nhap_kb<Customer>, 2);
	Node *TMenu2_1_2_TT = new Node(&MenuTT, 2);
	Node *TMenu2_2 = new Node(&Menu2_2, 3);
	Node *TMenu2_2_1 = new Node(&Search_Phone, 3);
	Node *TMenu2_2_1_TTTK = new Node(&MenuTTTK, 3);
	Node *TMenu2_2_1_TT = new Node(&MenuTT, 2);
	Node *TMenu2_2_2 = new Node(&Search_Name<Customer>, 3);
	Node *TMenu2_2_2_TTTK = new Node(&MenuTTTK, 3);
	Node *TMenu2_2_2_TT = new Node(&MenuTT, 2);
	Node *TMenu2_3 = new Node(&ChangeCustomerInfo, 2);
	Node *TMenu2_3_TT = new Node(&MenuTT, 2);

	Node *TMenu3 = new Node(&Menu3, 3);
	Node *TMenu3_1 = new Node(&Revenue, 2);
	Node *TMenu3_1_TT = new Node(&MenuTT, 2);
	Node *TMenu3_2 = new Node(&Menu3_2, 4);
	Node *TMenu3_2_1 = new Node(&Search_ID<Bill>, 3);
	Node *TMenu3_2_1_TTTK = new Node(&MenuTTTK, 3);
	Node *TMenu3_2_1_TT = new Node(&MenuTT, 2);
	Node *TMenu3_2_2 = new Node(&Search_Phone_Bill, 3);
	Node *TMenu3_2_2_TTTK = new Node(&MenuTTTK, 3);
	Node *TMenu3_2_2_TT = new Node(&MenuTT, 2);
	Node *TMenu3_2_3 = new Node(&Search_BuyDate, 3);
	Node *TMenu3_2_3_TTTK = new Node(&MenuTTTK, 3);
	Node *TMenu3_2_3_TT = new Node(&MenuTT, 2);


	Node *TMenu4 = new Node(&BillCalculate, 2);
	Node *TMenu4_TT = new Node(&MenuTT, 2);
	void InitMenu()
	{
		TMainMenu->AddChild(TMenu1, 1);
		TMenu1->AddChild(TMenu1_1, 1);
		TMenu1_1->AddChild(TMenu1_1_1, 1);
		TMenu1_1->AddChild(TMenu1_1_2, 2);
		TMenu1_1_1->AddChild_TT(TMenu1_1_1_TT,1);
		TMenu1_1_2->AddChild_TT(TMenu1_1_2_TT, 1);
		TMenu1->AddChild(TMenu1_2, 2);
		TMenu1_2->AddChild(TMenu1_2_1, 1);
		TMenu1_2->AddChild(TMenu1_2_2, 2);
		TMenu1_2->AddChild(TMenu1_2_3, 3);
		TMenu1_2_1->AddChild_TT(TMenu1_2_1_TT, 2);
		TMenu1_2_1->AddChild_TTTK(TMenu1_2_1_TTTK, 1);
		TMenu1_2_2->AddChild_TT(TMenu1_2_2_TT, 2);
		TMenu1_2_2->AddChild_TTTK(TMenu1_2_2_TTTK, 1);
		TMenu1_2_3->AddChild_TT(TMenu1_2_3_TT, 2);
		TMenu1_2_3->AddChild_TTTK(TMenu1_2_3_TTTK, 1);
		TMenu1->AddChild(TMenu1_3,3);

		TMainMenu->AddChild(TMenu2, 2);
		TMenu2->AddChild(TMenu2_1, 1);
		TMenu2_1->AddChild(TMenu2_1_1, 1);
		TMenu2_1->AddChild(TMenu2_1_2, 2);
		TMenu2_1_1->AddChild_TT(TMenu2_1_1_TT, 1);
		TMenu2_1_2->AddChild_TT(TMenu2_1_2_TT, 1);
		TMenu2->AddChild(TMenu2_2, 2);
		TMenu2_2->AddChild(TMenu2_2_1, 1);
		TMenu2_2->AddChild(TMenu2_2_2, 2);
		TMenu2_2_1->AddChild_TT(TMenu2_2_1_TT, 2);
		TMenu2_2_1->AddChild_TTTK(TMenu2_2_1_TTTK, 1);
		TMenu2_2_2->AddChild_TT(TMenu2_2_2_TT, 2);
		TMenu2_2_2->AddChild_TTTK(TMenu2_2_2_TTTK, 1);
		TMenu2->AddChild(TMenu2_3, 3);
		TMenu2_3->AddChild_TT(TMenu2_3_TT, 1);

		TMainMenu->AddChild(TMenu3, 3);
		TMenu3->AddChild(TMenu3_1, 1);
		TMenu3_1->AddChild_TT(TMenu3_1_TT, 1);
		TMenu3->AddChild(TMenu3_2, 2);
		TMenu3_2->AddChild(TMenu3_2_1, 1);
		TMenu3_2_1->AddChild_TTTK(TMenu3_2_1_TTTK, 1);
		TMenu3_2_1->AddChild_TT(TMenu3_2_1_TT, 2);
		TMenu3_2->AddChild(TMenu3_2_2, 2);
		TMenu3_2_2->AddChild_TTTK(TMenu3_2_2_TTTK, 1);
		TMenu3_2_2->AddChild_TT(TMenu3_2_2_TT, 2);
		TMenu3_2->AddChild(TMenu3_2_3, 3);
		TMenu3_2_3->AddChild_TTTK(TMenu3_2_3_TTTK, 1);
		TMenu3_2_3->AddChild_TT(TMenu3_2_3_TT, 2);

		TMainMenu->AddChild(TMenu4, 4);
		TMenu4->AddChild_TT(TMenu4_TT, 1);
	}
	void DeleteMenu()
	{
		delete TMenu3_2_3_TTTK;
		delete TMenu3_2_3_TT;
		delete TMenu3_2_2_TTTK;
		delete TMenu3_2_2_TT;
		delete TMenu3_2_1_TTTK;
		delete TMenu3_2_1_TT;
		delete TMenu2_2_2_TTTK;
		delete TMenu2_2_1_TT;
		delete TMenu2_2_2_TT;
		delete TMenu2_1_1_TT;
		delete TMenu2_1_2_TT;
		delete TMenu1_1_1_TT;
		delete TMenu1_1_2_TT;
		delete TMenu1_2_1_TTTK;
		delete TMenu1_2_2_TTTK;
		delete TMenu1_2_3_TTTK;
		delete TMenu1_2_1_TT;
		delete TMenu1_2_2_TT;
		delete TMenu1_2_3_TT;
		delete TMenu3_2_3;
		delete TMenu3_2_2;
		delete TMenu3_2_1;
		delete TMenu3_1_TT;
		delete TMenu2_3_TT;
		delete TMenu2_2_2;
		delete TMenu2_2_1;
		delete TMenu2_1_2;
		delete TMenu2_1_1;
		delete TMenu1_1_2;
		delete TMenu1_1_1;
		delete TMenu1_2_1;
		delete TMenu1_2_2;
		delete TMenu1_2_3; 
		delete TMenu4_TT;
		delete TMenu3_2;
		delete TMenu3_1;
		delete TMenu2_3;
		delete TMenu2_2;
		delete TMenu2_1;
		delete TMenu1_3;
		delete TMenu1_2;
		delete TMenu1_1;
		delete TMenu4;
		delete TMenu3;
		delete TMenu2;
		delete TMenu1;
		delete TMainMenu;
	}
}
#endif
