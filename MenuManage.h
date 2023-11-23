#ifndef MENU_MANAGE_H
#define MENU_MANAGE_H
#include <iostream>
#include <Windows.h>
#include <conio.h>
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
		const int w = 23;
		LeftPrintForInput("Nhap ID mat hang", w, ' ', cout); fflush(stdin); id_p.GetLine(cin);
		if (id_p == String("")) return false;
		LeftPrintForInput("Nhap ten mat hang", w, ' ', cout); fflush(stdin); name.GetLine(cin);
		LeftPrintForInput("Nhap xuat su mat hang", w, ' ', cout); fflush(stdin); xs.GetLine(cin);
		LeftPrintForInput("Nhap ID lo hang", w, ' ', cout); fflush(stdin); id_dp.GetLine(cin);
		InputAndCheck("Nhap ngay nhap hang", w, &mnu::LeftPrintForInput, nn);
		InputAndCheck("Nhap ngay san xuat", w, &mnu::LeftPrintForInput, nsx);
		InputAndCheck("Nhap han su dung", w, &mnu::LeftPrintForInput, hsd);
		LeftPrintForInput("Nhap gia", w, ' ', cout); cin >> price;
		LeftPrintForInput("Nhap so luong", w, ' ', cout); cin >> sl;
		DetailProduct *ptrDP = nullptr;
		if (id_p.SubStr(7,2) == String("01"))
		{
			ptrDP = new DetailWeightProduct(id_dp, nn, nsx, hsd, price, sl);
		}
		else
		{
			ptrDP = new DetailProduct(id_dp, nn, nsx, hsd, price, sl);
		}
		InsertProduct(List, id_p, name, xs, ptrDP);
		return true;
	}
	bool input_kb(DList<Customer *>& List)
	{
		String name, add;
		Phone phone;
		const int w = 24;
		LeftPrintForInput("Nhap ten khach hang", w, ' ', cout); fflush(stdin); name.GetLine(cin);
		if (name == String("")) return false;
		InputAndCheck("Nhap SDT khach mat hang", w, &mnu::LeftPrintForInput, phone);
		LeftPrintForInput("Nhap dia chi khach hang", w, ' ', cout); fflush(stdin); add.GetLine(cin);
		bool check;
		InsertCustomer(List, name, phone, add, check);
		if (!check)
		{
			throw Exception("Khach hang nay da ton tai");
		}
		return true;
	}
	//---------------------------------INPUT PRODUCT--------------------------------------
	void input(const String &fname, DList<Product*>& List)
	{
		ifstream inp;
		inp.open(fname);
		if (inp.fail())
		{
			throw Exception("FILE NOT EXIST");
		}
		Date nn (fname,".");
		while (!inp.eof()){
			String temp;
			fflush(stdin); temp.GetLine(inp);
			char *ptr;
			String id_p = strtok_s(temp, ",", &ptr);
			String name = strtok_s(nullptr, ",", &ptr);
			String xs = strtok_s(nullptr, ",", &ptr);
			String id_dp = strtok_s(nullptr, ",", &ptr);
			String nsx_str = strtok_s(nullptr, ",", &ptr);
			Date nsx(nsx_str);
			String hsd_str = strtok_s(nullptr, ",", &ptr);
			Date hsd(hsd_str);
			String price_str = strtok_s(nullptr, ",", &ptr); 
			int price = atoi(price_str);
			String sl_str = strtok_s(nullptr, ",", &ptr);
			int sl = atoi(sl_str);
			DetailProduct * ptrDP =nullptr;
			if (id_p.SubStr(7,2) == String("01"))
			{
				ptrDP = new DetailWeightProduct(id_dp, nn, nsx, hsd, price, sl);
			}
			else
			{
				ptrDP = new DetailProduct(id_dp, nn, nsx, hsd, price, sl);
			}
			InsertProduct(List, id_p, name, xs, ptrDP);
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
		while (!inp.eof()){
			String temp;
			fflush(stdin); temp.GetLine(inp);
			char *ptr;
			String name = strtok_s(temp, ",", &ptr);
			String phone = strtok_s(nullptr, ",", &ptr);
			String add = strtok_s(nullptr, ",", &ptr);
			bool check;
			InsertCustomer(List, name,phone,add,check);
		}
		inp.close();
	}
	//---------------------------------Chuc nang TKSP-----------------------------------------------
	namespace search_mnu
	{
		bool stilluse = false;
	}
	// --ID---
	template<class T>
	void Search_ID(const DList<T*>& List, int &choice)
	{
		DrawTitle(mnu::SubMenu);
		String data_lookup;
		PadLeftPrint("Nhap ID can tim kiem :",mnu::LEFTSPACE,' ',cout);  fflush(stdin); data_lookup.GetLine(cin);
		T *ptr = FindFirstMatch(List, data_lookup, &T::GetID);
		OutputDetail(ptr,cout);
		choice = 1;
		system("pause");
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
			PadLeftPrint("Nhap ten can tim kiem :",mnu::LEFTSPACE,' ',cout); fflush(stdin); data_lookup.GetLine(cin);
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
		PadLeftPrint("Nhap STT mat hang muon xem chi tiet (chon 0 de quay lai):", 0,' ',cout); cin >> choice; 
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
			T * ptr = FindIndex(*ptrAns_List_For_Search, choice);
			OutputDetail(ptr,cout);
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
			PadLeftPrint("Nhap xuat su san phan can tim kiem :", mnu::LEFTSPACE, ' ', cout); fflush(stdin); data_lookup.GetLine(cin);
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
		PadLeftPrint("Nhap STT mat hang muon xem chi tiet (chon 0 de quay lai):", 0, ' ', cout); cin >> choice;
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
			Product * ptr = FindIndex(*ptrAns_List_For_Search, choice);
			OutputDetail(ptr,cout);
			system("pause");
			choice = 1;
		}
	}
	//-----SDT----
	void Search_Phone(const DList<Customer*>& List, int &choice)
	{
		DrawTitle(mnu::SubMenu);
		Phone data_lookup;
		InputAndCheck("Nhap SDT can tim kiem :", mnu::LEFTSPACE, &mnu::PadLeftPrint, data_lookup);
		Customer *ptr = FindFirstMatch(List, data_lookup, &Customer::GetPhone);
		OutputDetail(ptr,cout);
		choice = 1;
		system("pause");
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
			InputAndCheck("Nhap ngay mua cua hoa don can tim kiem :", mnu::LEFTSPACE, &mnu::PadLeftPrint, data_lookup);
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
		PadLeftPrint("Nhap STT hoa don muon xem chi tiet (chon 0 de quay lai):", 0, ' ', cout); cin >> choice;
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
			Bill * ptr = FindIndex(*ptrAns_List_For_Search, choice);
			OutputDetail(ptr,cout);
			system("pause");
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
			InputAndCheck("Nhap SDT cua hoa don can tim kiem : ", mnu::LEFTSPACE, &mnu::PadLeftPrint, data_lookup);
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
		PadLeftPrint("Nhap STT hoa don muon xem chi tiet (chon 0 de quay lai):", 0, ' ', cout); cin >> choice;
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
			Bill * ptr = FindIndex(*ptrAns_List_For_Search, choice);
			OutputDetail(ptr,cout);
			system("pause");
			choice = 1;
		}
	}
	//----------------------------------template nhap tu file-------------------------------------------------
	template<class T>
	void Nhap(DList<T*> & List, int & choice)
	{
		DrawTitle(mnu::SubMenu);
		PadLeftPrint("Nhap ten file:",mnu::LEFTSPACE,' ',cout);
		String fname;
		fflush(stdin); fname.GetLine(cin);
		if (fname == String(""))
		{
			choice = 0;
			return;
		}
		input(fname, List);
		PadLeftPrint("Input thanh cong", mnu::LEFTSPACE, ' ', cout);
		Sleep(mnu::WAIT);
		choice = 1;
	}
	//----------------------------------template nhap tu ban phim-------------------------------------------------
	template<class T>
	void Nhap_kb(DList<T*> & List, int & choice)
	{
		DrawTitle(mnu::SubMenu);
		if (input_kb(List))	PadLeftPrint("Input thanh cong", mnu::LEFTSPACE, ' ', cout);
		Sleep(mnu::WAIT);
		choice = 1;
	}
	//-----------------------------------MAIN MENU------------------------------------------------
	void MainMenu(int& choice)
	{
		mnu::SubMenu = -1;
		DrawTitle(mnu::SubMenu);
		PadLeftPrint("1.Quan ly san pham", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("2.Quan ly khach hang", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("3.Quan ly hoa don", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("4.Tinh hoa don", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("0.Ket thuc", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("Lua chon cua ban :", mnu::LEFTSPACE, ' ', cout); std::cin >> choice; mnu::SubMenu = choice - 1;
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
			cout << "Ban muon kiem tra san pham het hang trong bao nhieu ngay : "; cin >> day;
			if (day < 0)
			{
				fflush(stdin);
				cin.clear();
				throw Exception("INVALID VALUE");
			}
			ptrAnsList = OutOfExpiration(List, day);
		}
		OutputDetailProduct(*ptrAnsList,cout);
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
		cout << "\nBan muon xoa tat ca san pham tren khong\n";
		cout << "1.Xoa tat ca\n";
		cout << "0.Khong xoa va quay lai\n";
		cout << "Lua chon cua ban : ";cin >> choice;
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
			CenterPrint("DA XOA THANH CONG", mnu::WIDTH,' ',cout);
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
		PadLeftPrint("1.Them san pham", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("2.Tim kiem san pham", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("3.Quan ly san pham het hang", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("0.Quay lai", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("Lua chon cua ban :", mnu::LEFTSPACE, ' ', cout); std::cin >> choice;
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
		PadLeftPrint("1.Them bang file", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("2.Nhap tu ban phim", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("0.Quay lai", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("Lua chon cua ban :", mnu::LEFTSPACE, ' ', cout); std::cin >> choice;
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
		PadLeftPrint("1.Tim kiem theo ma mat hang", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("2.Tim kiem theo ten mat hang", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("3.Tim kiem theo xuat xu", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("0.Quay lai", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("Lua chon cua ban :", mnu::LEFTSPACE, ' ', cout); cin >> choice;
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
		PadLeftPrint("1.Them khach hang", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("2.Tim kiem khach hang", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("3.Chinh sua thong tin khach hang", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("0.Quay lai", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("Lua chon cua ban :", mnu::LEFTSPACE, ' ', cout); cin >> choice;
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
		PadLeftPrint("1.Tim kiem theo SDT Khach hang", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("2.Tim kiem theo ten Khach hang", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("0.Quay lai", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("Lua chon cua ban :", mnu::LEFTSPACE, ' ', cout); cin >> choice;
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
		InputAndCheck("Nhap SDT cua khach hang can cap nhat : ", mnu::LEFTSPACE, &mnu::PadLeftPrint, phone);
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
		PadLeftPrint("Chon muc thong tin muon cap nhat", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("1.Ten", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("2.So dien thoai", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("3.Dia chi", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("0.Quay lai", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("Lua chon cua ban :", mnu::LEFTSPACE, ' ', cout); cin >> choice;
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
			cout << "Nhap thong tin sua doi : ";
			fflush(stdin); update_info.GetLine(cin);
			ptrC->SetName(update_info);
			break;
		}
		case 2:
		{
			Phone update_info;
			InputAndCheck("Nhap thong tin sua doi : ", 0, &mnu::LeftPrint, update_info);
			ptrC->SetPhone(update_info);
			break;
		}
		case 3:
		{
			String update_info;
			cout << "Nhap thong tin sua doi : ";
			fflush(stdin); update_info.GetLine(cin);
			ptrC->SetName(update_info);
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
		LeftPrintForInput("Ngay", w, ' ', cout); cout << buydate << endl;
		LeftPrintForInput("Thoi gian", w, ' ', cout); cout << buytime << endl;
		InputAndCheck("Nhap SDT khach hang", w, &mnu::LeftPrintForInput, phone);
		Customer* ptrC = nullptr; bool inserted=false;
		if (phone != Phone("0000000000")) // Khach hang muon luu thong tin hay ko
		{
			ptrC = InsertCustomer(CList, c_name, phone, address, inserted);
			if (inserted)
			{
				LeftPrintForInput("Ten khach hang", w, ' ', cout); fflush(stdin); c_name.GetLine(cin);
				LeftPrintForInput("Dia chi khach hang", w, ' ', cout); fflush(stdin); address.GetLine(cin);
				ptrC->SetName(c_name);
				ptrC->SetAddress(address);
			}
			else
			{
				LeftPrintForInput("Ten khach hang", w, ' ', cout); cout << ptrC->GetName() << endl;
				LeftPrintForInput("Dia chi khach hang", w, ' ', cout); cout << ptrC->GetAddress() << endl;
			}
		}	
		int cnt = 0;
		int total = 0;
		Bill *ptrB = new Bill(buydate,buytime);
		do
		{
			std::cout << "\n\n" << '+'; DrawLine(mnu::WIDTH - 2, '=',cout); std::cout << '+' << "\n\n";
			String id_p; int sl;
			LeftPrintForInput("Nhap ma mat hang", w, ' ', cout); fflush(stdin); id_p.GetLine(cin);
			if (id_p == String("")) break;
			String p_id, dp_id;
			p_id = id_p.SubStr(0, 9);
			dp_id = id_p.SubStr(9, 4);
			Product* ptrP = FindFirstMatch(PList, p_id, &Product::GetID);
			if (ptrP == nullptr)
			{
				cout << "Khong tim thay san pham\n";
				continue;
			}
			DetailProduct* ptrDP = ptrP->FindDetailProduct(dp_id);
			if (ptrDP == nullptr)
			{
				cout << "Khong tim thay san pham\n";
				continue;
			}
			cnt++;
			String type = id_p.SubStr(7, 2);
			if (type == String("01"))
			{
				LeftPrintForInput("Nhap khoi luong(don vi gam)", w, ' ', cout);
			}
			else
			{
				LeftPrintForInput("Nhap so luong", w, ' ', cout);
			}
			cin >> sl;
			total += ptrDP->Calculate(sl);
			DetailBill *ptrDB = new DetailBill(ptrDP, sl);
			ptrDP->Deduct(sl);
			ptrDP->AddDetailBill(ptrDB);
			ptrB->AddDetailBill(ptrDB);
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
		if (ptrC != nullptr)
		{
			ptrC->AddBill(ptrB);
		}
		InsertBill(BList, ptrB);
		system("cls");
		DrawTitle(mnu::SubMenu);
		OutputDetail(ptrB,cout);
		cout << "XUAT HOA DON ???\nNHAN p DE XUAT DON";
		char p = _getch();
		if (p == 'p' || p == 'P')
		{
			OutputBillFile(ptrB->GetID(), ptrB);
		}
		choice = 1;
	}
	//----------TINH DOANH THU-------------------
	void Revenue(const DList<Bill*> &List, int &choice)
	{
		DrawTitle(mnu::SubMenu);
		cout << "Nhap khoang thoi gian muon tinh doanh thu\n";
		int w = 15;
		Date s, f;
		InputAndCheck("Tu ngay", w, &mnu::LeftPrintForInput, s);
		InputAndCheck("Den ngay", w, &mnu::LeftPrintForInput, f);
		DList<Bill*> AnsList;
		int total_revenue = CalRevenue(List, s, f, AnsList);
		OutputTable(AnsList,cout);
		cout << '|'; CenterPrint("TONG", w,' ',cout);
		cout << '|'; CenterPrint(String::to_string(total_revenue), mnu::WIDTH - 3 - w, ' ', cout); cout << '|' << endl;
		cout << '+'; DrawLine(mnu::WIDTH - 2, '=',cout); cout << '+' << endl;
		system("pause");
		choice = 1;
	}
	//----------------------------------MENU3--------------------------------------------------
	void Menu3(int &choice)
	{
		DrawTitle(mnu::SubMenu);
		PadLeftPrint("1.Tinh doanh thu", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("2.Truy xuat hoa don", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("0.Quay lai", mnu::LEFTSPACE, ' ', cout); cout << "\n";
		PadLeftPrint("Lua chon cua ban :", mnu::LEFTSPACE, ' ', cout); cin >> choice;
		if (choice < 0 || choice>3)
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
		PadLeftPrint("1.Truy xuat theo ID hoa don", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("2.Truy xuat theo SDT khach hang", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("3.Truy xuat theo ngay mua", mnu::LEFTSPACE, ' ', cout); cout << '\n';
		PadLeftPrint("0.Quay lai", mnu::LEFTSPACE, ' ', cout); cout << "\n";
		PadLeftPrint("Lua chon cua ban :", mnu::LEFTSPACE, ' ', cout); cin >> choice;
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
		PadLeftPrint("1.Tiep tuc", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("0.Quay lai", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("Lua chon cua ban :", mnu::LEFTSPACE, ' ', cout); std::cin >> choice;
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
		PadLeftPrint("Ban muon tiep tuc", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("1.Tiep tuc voi truy xuat cu", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("2.Tiep tuc voi truy xuat moi", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("0.Quay lai", mnu::LEFTSPACE, ' ', cout); std::cout << '\n';
		PadLeftPrint("Lua chon cua ban :", mnu::LEFTSPACE, ' ', cout); std::cin >> choice;
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
	Node *TMenu1_2_1 = new Node(&Search_ID<Product>, 2);
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
	Node *TMenu2_2_1 = new Node(&Search_Phone, 2);
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
	Node *TMenu3_2_1 = new Node(&Search_ID<Bill>, 2);
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
		TMenu1_2_1->AddChild_TT(TMenu1_2_1_TT, 1);
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
		TMenu2_2_1->AddChild_TT(TMenu2_2_1_TT, 1);
		TMenu2_2_2->AddChild_TT(TMenu2_2_2_TT, 2);
		TMenu2_2_2->AddChild_TTTK(TMenu2_2_2_TTTK, 1);
		TMenu2->AddChild(TMenu2_3, 3);
		TMenu2_3->AddChild_TT(TMenu2_3_TT, 1);

		TMainMenu->AddChild(TMenu3, 3);
		TMenu3->AddChild(TMenu3_1, 1);
		TMenu3_1->AddChild_TT(TMenu3_1_TT, 1);
		TMenu3->AddChild(TMenu3_2, 2);
		TMenu3_2->AddChild(TMenu3_2_1, 1);
		TMenu3_2_1->AddChild_TT(TMenu3_2_1_TT, 1);
		TMenu3_2->AddChild(TMenu3_2_2, 2);
		TMenu3_2_2->AddChild_TTTK(TMenu3_2_2_TTTK, 1);
		TMenu3_2_2->AddChild_TT(TMenu3_2_1_TT, 2);
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
		delete TMenu3_2_1_TT;
		delete TMenu2_2_2_TTTK;
		delete TMenu2_2_1_TT;
		delete TMenu2_2_2_TT;
		delete TMenu2_1_1_TT;
		delete TMenu2_1_2_TT;
		delete TMenu1_1_1_TT;
		delete TMenu1_1_2_TT;
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
