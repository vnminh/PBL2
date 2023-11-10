#ifndef MENU_MANAGE_H
#define MENU_MANAGE_H
#include <iostream>
#include <Windows.h>
#include "String.h"
#include "Exception.h"
#include "Output.h"
namespace mnu
{
	//--------------------------------INPUT_FROM KEY BOARD_PRODUCT-------------------------
	void input_kb(DList<Product *>& List)
	{
		String id_p, name, xs, id_dp;
		Date nn, nsx, hsd;
		int price, sl;
		const int w = 23;
		LeftPrint("Nhap ID mat hang", w); cout << ": "; id_p.GetLine(cin);
		LeftPrint("Nhap ten mat hang", w); cout << ": "; name.GetLine(cin);
		LeftPrint("Nhap xuat su mat hang", w); cout << ": "; xs.GetLine(cin);
		LeftPrint("Nhap ID lo hang", w); cout << ": ";  id_dp.GetLine(cin);
		LeftPrint("Nhap ngay nhap hang", w); cout << ": "; cin >> nn;
		LeftPrint("Nhap ngay san xuat", w); cout << ": "; cin >> nsx;
		LeftPrint("Nhap han su dung", w); cout << ": "; cin >> hsd;
		LeftPrint("Nhap gia", w); cout << ": "; cin >> price;
		LeftPrint("Nhap so luong", w); cout << ": "; cin >> sl;
		DetailProduct * ptrDP = new DetailProduct(id_dp, nn, nsx, hsd, price, sl);
		InsertProduct(List, id_p, name, xs, ptrDP);
	}
	void input_kb(DList<Customer *>& List)
	{
		String name, phone, add;
		const int w = 24;
		LeftPrint("Nhap ten khach hang", w); cout << ": "; name.GetLine(cin);
		LeftPrint("Nhap SDT khach mat hang", w); cout << ": "; phone.GetLine(cin);
		LeftPrint("Nhap dia chi khach hang", w); cout << ": ";  add.GetLine(cin);
		bool check;
		InsertCustomer(List, name, phone, add, check);
		if (!check)
		{
			throw Exception("Khach hang nay da ton tai");
		}
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
			temp.GetLine(inp);
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
			DetailProduct * ptrDP = new DetailProduct(id_dp, nn, nsx, hsd, price, sl);
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
		Date nn(fname, ".");
		while (!inp.eof()){
			String temp;
			temp.GetLine(inp);
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
		DrawTitle();
		String data_lookup;
		PadLeftPrint("Nhap ID can tim kiem :"); data_lookup.GetLine(cin);
		T *ptr = FindFirstMatch(List, data_lookup, &T::GetID);
		OutputDetail(ptr);
		choice = 1;
		system("pause");
	}
	//--NAME---
	template<class T>
	void Search_Name(const DList<T*>& List, int &choice)
	{
		static DList<T*>* ptrAns_List_For_Search = nullptr;
		static int cnt_Search = 0;
		DrawTitle();
		if (!search_mnu::stilluse)
		{
			ptrAns_List_For_Search = nullptr;
			cnt_Search = 0;
			String data_lookup;
			PadLeftPrint("Nhap ten can tim kiem :"); data_lookup.GetLine(cin);
			ptrAns_List_For_Search = FindAll(List, data_lookup, &T::GetName, cnt_Search);
			search_mnu::stilluse = true;
		}
		OutputTable(*ptrAns_List_For_Search, cnt_Search);
		if (cnt_Search == 0)
		{
			system("pause");
			search_mnu::stilluse = false;
			choice = 2;
			return;
		}
		PadLeftPrint("Nhap STT mat hang muon xem chi tiet (chon 0 de quay lai):", 0); cin >> choice; cin.ignore();
		if (choice<0 || choice>cnt_Search)
		{
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
			OutputDetail(ptr);
			system("pause");
			choice = 1;
		}
	}
	//--Xuat SU --
	void Search_XS(const DList<Product*>& List, int &choice)
	{
		static DList<Product*>* ptrAns_List_For_Search;
		static int cnt_Search;
		DrawTitle();
		if (!search_mnu::stilluse)
		{
			ptrAns_List_For_Search = nullptr;
			cnt_Search = 0;
			String data_lookup;
			PadLeftPrint("Nhap xuat su san phan can tim kiem :"); data_lookup.GetLine(cin);
			ptrAns_List_For_Search = FindAll(List, data_lookup, &Product::GetXS, cnt_Search);
			search_mnu::stilluse = true;
		}
		OutputTable(*ptrAns_List_For_Search, cnt_Search);
		if (cnt_Search == 0)
		{
			system("pause");
			search_mnu::stilluse = true;
			choice = 2;
			return;
		}
		PadLeftPrint("Nhap STT mat hang muon xem chi tiet (chon 0 de quay lai):", 0); cin >> choice; cin.ignore();
		if (choice<0 || choice>cnt_Search)
		{
			throw Exception("INVALID VALUE");
		}
		if (choice == 0)
		{
			search_mnu::stilluse = true;
			return;
		}
		else
		{
			system("cls");
			Product * ptr = FindIndex(*ptrAns_List_For_Search, choice);
			OutputDetail(ptr);
			system("pause");
			choice = 1;
		}
	}
	//-----SDT----
	void Search_Phone(const DList<Customer*>& List, int &choice)
	{
		DrawTitle();
		String data_lookup;
		PadLeftPrint("Nhap SDT can tim kiem :"); data_lookup.GetLine(cin);
		Customer *ptr = FindFirstMatch(List, data_lookup, &Customer::GetPhone);
		OutputDetail(ptr);
		choice = 1;
		system("pause");
	}
	//---Ngay mua-------
	void Search_BuyDate(const DList<Bill*>& List, int & choice)
	{
		static DList<Bill*>* ptrAns_List_For_Search;
		static int cnt_Search;
		DrawTitle();
		if (!search_mnu::stilluse)
		{
			ptrAns_List_For_Search = nullptr;
			cnt_Search = 0;
			Date data_lookup;
			PadLeftPrint("Nhap ngay mua cua hoa don can tim kiem :"); cin >> data_lookup; cin.ignore();
			ptrAns_List_For_Search = FindAll(List, data_lookup, &Bill::GetBuyDate, cnt_Search);
			search_mnu::stilluse = true;
		}
		OutputTable(*ptrAns_List_For_Search, cnt_Search);
		if (cnt_Search == 0)
		{
			system("pause");
			search_mnu::stilluse = true;
			choice = 2;
			return;
		}
		PadLeftPrint("Nhap STT hoa don muon xem chi tiet (chon 0 de quay lai):", 0); cin >> choice; cin.ignore();
		if (choice<0 || choice>cnt_Search)
		{
			throw Exception("INVALID VALUE");
		}
		if (choice == 0)
		{
			search_mnu::stilluse = true;
			return;
		}
		else
		{
			system("cls");
			Bill * ptr = FindIndex(*ptrAns_List_For_Search, choice);
			OutputDetail(ptr);
			system("pause");
			choice = 1;
		}
	}
	//---SDT Bill---
	void Search_Phone_Bill(const DList<Bill*>& List, int & choice)
	{
		static DList<Bill*>* ptrAns_List_For_Search;
		static int cnt_Search;
		DrawTitle();
		if (!search_mnu::stilluse)
		{
			ptrAns_List_For_Search = nullptr;
			cnt_Search = 0;
			String data_lookup;
			PadLeftPrint("Nhap ngay mua cua hoa don can tim kiem :"); data_lookup.GetLine(cin);
			ptrAns_List_For_Search = FindAll(List, data_lookup, &Bill::GetCustomerPhone, cnt_Search);
			search_mnu::stilluse = true;
		}
		OutputTable(*ptrAns_List_For_Search, cnt_Search);
		if (cnt_Search == 0)
		{
			system("pause");
			search_mnu::stilluse = true;
			choice = 2;
			return;
		}
		PadLeftPrint("Nhap STT hoa don muon xem chi tiet (chon 0 de quay lai):", 0); cin >> choice; cin.ignore();
		if (choice<0 || choice>cnt_Search)
		{
			throw Exception("INVALID VALUE");
		}
		if (choice == 0)
		{
			search_mnu::stilluse = true;
			return;
		}
		else
		{
			system("cls");
			Bill * ptr = FindIndex(*ptrAns_List_For_Search, choice);
			OutputDetail(ptr);
			system("pause");
			choice = 1;
		}
	}
	//----------------------------------template nhap tu file-------------------------------------------------
	template<class T>
	void Nhap(DList<T*> & List, int & choice)
	{
		DrawTitle();
		PadLeftPrint("Nhap ten file:");
		String fname;
		fname.GetLine(cin);
		if (fname == String(""))
		{
			choice = 0;
			return;
		}
		input(fname, List);
		PadLeftPrint("Input thanh cong"); std::cout << "\n";
		system("pause");
		choice = 1;
	}
	//----------------------------------template nhap tu ban phim-------------------------------------------------
	template<class T>
	void Nhap_kb(DList<T*> & List, int & choice)
	{
		DrawTitle();
		input_kb(List);
		PadLeftPrint("Input thanh cong"); std::cout << "\n";
		system("pause");
		choice = 1;
	}
	//-----------------------------------MAIN MENU------------------------------------------------
	void MainMenu(int& choice)
	{
		DrawTitle();
		PadLeftPrint("1.Quan ly san pham"); std::cout << '\n';
		PadLeftPrint("2.Quan ly khach hang"); std::cout << '\n';
		PadLeftPrint("3.Quan ly hoa don"); std::cout << '\n';
		PadLeftPrint("0.Ket thuc"); std::cout << '\n';
		PadLeftPrint("Lua chon cua ban :"); std::cin >> choice; cin.ignore();
		if (choice < 0 || choice>3)
		{
			throw Exception("INVALID VALUE");
		}
	}
	//---------------------------------------QUAN LY MAT HANG------------------------------------
	//------------------------------------MENU 1----------------------------------------------------
	void Menu1(int &choice)
	{
		DrawTitle();
		PadLeftPrint("1.Them san pham"); std::cout << '\n';
		PadLeftPrint("2.Tim kiem san pham"); std::cout << '\n';
		PadLeftPrint("0.Quay lai"); std::cout << '\n';
		PadLeftPrint("Lua chon cua ban :"); std::cin >> choice; cin.ignore();
		if (choice < 0 || choice>2)
		{
			throw Exception("INVALID VALUE");
		}
	}
	//----------------------------------MENU 1/2-1 ------------------------------------------------------
	void Menu12_1(int &choice)
	{
		DrawTitle();
		PadLeftPrint("1.Them bang file"); std::cout << '\n';
		PadLeftPrint("2.Nhap tu ban phim"); std::cout << '\n';
		PadLeftPrint("0.Quay lai"); std::cout << '\n';
		PadLeftPrint("Lua chon cua ban :"); std::cin >> choice; cin.ignore();
		if (choice < 0 || choice>2)
		{
			throw Exception("INVALID VALUE");
		}
	}
	
	//----------------------------------MENU 1-2 ------------------------------------------------------
	void Menu1_2(int& choice)
	{
		DrawTitle();
		PadLeftPrint("1.Tim kiem theo ma mat hang"); cout << '\n';
		PadLeftPrint("2.Tim kiem theo ten mat hang"); cout << '\n';
		PadLeftPrint("3.Tim kiem theo xuat xu"); cout << '\n';
		PadLeftPrint("0.Quay lai"); cout << '\n';
		PadLeftPrint("Lua chon cua ban :"); cin >> choice; cin.ignore();
		if (choice < 0 || choice>3)
		{
			throw Exception("INVALID VALUE");
		}
	}
	//-----------------------------------QUAN LY KHACH HANG------------------------------------------
	//----------------------------------MENU 2 --------------------------------------------------------
	void Menu2(int &choice)
	{
		CenterPrint(TITLE, WIDTH);
		cout << "\n\n" << '+'; DrawLine(WIDTH - 2, '='); cout << '+' << "\n\n";
		PadLeftPrint("1.Them khach hang"); cout << '\n';
		PadLeftPrint("2.Tim kiem khach hang"); cout << '\n';
		PadLeftPrint("3.Chinh sua thong tin khach hang"); cout << '\n';
		PadLeftPrint("0.Quay lai"); cout << '\n';
		PadLeftPrint("Lua chon cua ban :"); cin >> choice; cin.ignore();
		if (choice < 0 || choice>3)
		{
			throw Exception("INVALID VALUE");
		}
	}
	//-------------------------------MENU 2-1 --------------------------------------------
	// TRUNG VOI MENU 1-1
	//----------------------------------MENU 2-2 ------------------------------------------------------
	void Menu2_2(int& choice)
	{
		DrawTitle();
		PadLeftPrint("1.Tim kiem theo SDT Khach hang"); cout << '\n';
		PadLeftPrint("2.Tim kiem theo ten Khach hang"); cout << '\n';
		PadLeftPrint("0.Quay lai"); cout << '\n';
		PadLeftPrint("Lua chon cua ban :"); cin >> choice; cin.ignore();
		if (choice < 0 || choice>3)
		{
			throw Exception("INVALID VALUE");
		}
	}
	//----Update thong tin khach hang---------
	void ChangeCustomerInfo(DList<Customer*>& List, int & choice)
	{
		DrawTitle();
		String phone;
		PadLeftPrint("Nhap SDT cua khach hang can cap nhat : "); phone.GetLine(cin);
		Customer * ptrC = FindFirstMatch(List, phone, &Customer::GetPhone);
		system("cls");
		DrawTitle();
		OutputDetail(ptrC);
		if (ptrC == nullptr)
		{
			choice = 1;
			return;
		}
		PadLeftPrint("Chon muc thong tin muon cap nhat"); cout << '\n';
		PadLeftPrint("1.Ten"); cout << '\n';
		PadLeftPrint("2.So dien thoai"); cout << '\n';
		PadLeftPrint("3.Dia chi"); cout << '\n';
		PadLeftPrint("Lua chon cua ban :"); cin >> choice; cin.ignore();
		if (choice < 1 || choice>3)
		{
			throw Exception("INVALID VALUE");
		}
		system("cls");
		DrawTitle();
		String data_update;
		LeftPrint("Nhap thong sua doi : ", 0); data_update.GetLine(cin);
		switch (choice)
		{
		case 1:
		{
			ptrC->SetName(data_update);
			break;
		}
		case 2:
		{
			ptrC->SetPhone(data_update);
			break;
		}
		case 3:
		{
			ptrC->SetAddress(data_update);
			break;
		}
		}
		choice = 1;
	}
	//----------------------------------QUAN LY HOA DON--------------------------------------
	void BillCalculate(DList<Bill*>& BList, DList<Product*>& PList, DList<Customer*>& CList, int &choice)
	{
		DrawTitle();
		int w = 30;
		String c_name, phone, d;
		LeftPrint("Nhap ngay mua", w); cout << ": "; d.GetLine(cin);
		LeftPrint("Nhap ten khach hang", w); cout << ": "; c_name.GetLine(cin);
		LeftPrint("Nhap SDT khach hang", w); cout << ": "; phone.GetLine(cin);
		Date buydate = Date(d);
		int cnt = 0;
		int total = 0;
		Bill *ptrB = new Bill(buydate);
		bool check;
		Customer* ptrC = InsertCustomer(CList, c_name, phone,"", check);
		(ptrB->ConnectCustomer)(ptrC);
		do
		{
			String temp; int sl;
			LeftPrint("Nhap ma mat hang", w); cout << ": "; temp.GetLine(cin);
			if (temp == String("")) break;
			cnt++;
			LeftPrint("Nhap so luong", w); cout << ": "; cin >> sl; cin.ignore();
			String p_id, dp_id;
			p_id = temp.SubStr(0, 5);
			dp_id = temp.SubStr(5, 3);
			Product* ptrP = FindFirstMatch(PList, p_id, &Product::GetID);
			DetailProduct* ptrDP = ptrP->FindDetailProduct(dp_id);
			total += (ptrDP->GetPrice())*sl;
			DetailBill *ptrDB = new DetailBill(ptrDP, sl);
			ptrDP->Deduct(sl);
			ptrDP->AddDetailBill(ptrDB);
			ptrB->AddDetailBill(ptrDB);
			ptrB->SetNumDetailBill(cnt);
			ptrB->SetTotal(total);
			InsertBill(BList, ptrB);
		} while (true);
		ptrC->AddBill(ptrB);
		system("cls");
		DrawTitle();
		OutputDetail(ptrB);
		system("pause");
		choice = 1;
	}
	//----------------------------------MENU3--------------------------------------------------
	void Menu3(int &choice)
	{
		DrawTitle();
		PadLeftPrint("1.Tinh hoa don"); cout << '\n';
		PadLeftPrint("2.Tinh doanh thu"); cout << '\n';
		PadLeftPrint("3.Truy xuat hoa don"); cout << '\n';
		PadLeftPrint("0.Quay lai"); cout << "\n";
		PadLeftPrint("Lua chon cua ban :"); cin >> choice; cin.ignore();
		if (choice < 0 || choice>3)
		{
			throw Exception("INVALID VALUE");
		}
	}
	//----------------------------------Menu3_3----------------------------------------------
	void Menu3_3(int &choice)
	{
		DrawTitle();
		PadLeftPrint("1.Truy xuat theo ID hoa don"); cout << '\n';
		PadLeftPrint("2.Truy xuat theo SDT khach hang"); cout << '\n';
		PadLeftPrint("3.Truy xuat theo ngay mua"); cout << '\n';
		PadLeftPrint("0.Quay lai"); cout << "\n";
		PadLeftPrint("Lua chon cua ban :"); cin >> choice; cin.ignore();
		if (choice < 0 || choice>3)
		{
			throw Exception("INVALID VALUE");
		}
	}
	//-----------------------------------MENU TT----------------------------------------------
	void MenuTT(int &choice)
	{
		DrawTitle();
		PadLeftPrint("1.Tiep tuc"); std::cout << '\n';
		PadLeftPrint("0.Quay lai"); std::cout << '\n';
		PadLeftPrint("Lua chon cua ban :"); std::cin >> choice; cin.ignore();
		if (choice < 0 || choice>1)
		{
			throw Exception("INVALID VALUE");
		}
	}
	//-------------------------------------MENU TT CHO TM KIEM ----------------------------------
	void MenuTTTK(int &choice)
	{
		DrawTitle();
		PadLeftPrint("Ban muon tiep tuc"); std::cout << '\n';
		PadLeftPrint("1.Tiep tuc voi truy xuat cu"); std::cout << '\n';
		PadLeftPrint("2.Tiep tuc voi truy xuat moi"); std::cout << '\n';
		PadLeftPrint("0.Quay lai"); std::cout << '\n';
		PadLeftPrint("Lua chon cua ban :"); std::cin >> choice; cin.ignore();
		if (choice < 0 || choice>2)
		{
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
	Node *TMainMenu = new Node(&MainMenu, 4);

	Node *TMenu1 = new Node(&Menu1, 3);
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

	Node *TMenu3 = new Node(&Menu3, 4);
	Node *TMenu3_1 = new Node(&BillCalculate, 2);
	Node *TMenu3_1_TT = new Node(&MenuTT, 2);
	Node *TMenu3_3 = new Node(&Menu3, 4);
	Node *TMenu3_3_1 = new Node(&Search_ID<Bill>, 2);
	Node *TMenu3_3_1_TT = new Node(&MenuTT, 2);
	Node *TMenu3_3_2 = new Node(&Search_Phone_Bill, 3);
	Node *TMenu3_3_2_TTTK = new Node(&MenuTTTK, 3);
	Node *TMenu3_3_2_TT = new Node(&MenuTT, 2);
	Node *TMenu3_3_3 = new Node(&Search_BuyDate, 3);
	Node *TMenu3_3_3_TTTK = new Node(&MenuTTTK, 3);
	Node *TMenu3_3_3_TT = new Node(&MenuTT, 2);
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
		TMenu3->AddChild(TMenu3_3, 3);
		TMenu3_3->AddChild(TMenu3_3_1, 1);
		TMenu3_3_1->AddChild(TMenu3_3_1_TT, 1);
		TMenu3_3->AddChild(TMenu3_3_2, 2);
		TMenu3_3_2->AddChild(TMenu3_3_2_TTTK, 1);
		TMenu3_3_2->AddChild(TMenu3_3_1_TT, 2);
		TMenu3_3->AddChild(TMenu3_3_3, 3);
		TMenu3_3_3->AddChild(TMenu3_3_3_TTTK, 1);
		TMenu3_3_3->AddChild(TMenu3_3_3_TT, 2);
	}
	void DeleteMenu()
	{
		delete TMenu3_3_3_TTTK;
		delete TMenu3_3_3_TT;
		delete TMenu3_3_2_TTTK;
		delete TMenu3_3_2_TT;
		delete TMenu3_3_1_TT;
		delete TMenu3_1_TT;
		delete TMenu2_3_TT;
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
		delete TMenu3_3_3;
		delete TMenu3_3_2;
		delete TMenu3_3_1;
		delete TMenu2_2_2;
		delete TMenu2_2_1;
		delete TMenu2_1_2;
		delete TMenu2_1_1;
		delete TMenu1_1_2;
		delete TMenu1_1_1;
		delete TMenu1_2_1;
		delete TMenu1_2_2;
		delete TMenu1_2_3; 
		delete TMenu3_3;
		delete TMenu3_1;
		delete TMenu2_3;
		delete TMenu2_2;
		delete TMenu2_1;
		delete TMenu1_2;
		delete TMenu1_1;
		delete TMenu3;
		delete TMenu2;
		delete TMenu1;
		delete TMainMenu;
	}
}
#endif
