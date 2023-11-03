#ifndef MENU_MANAGE_H
#define MENU_MANAGE_H
#include <iostream>
#include <Windows.h>
#include "String.h"
#include "Exception.h"
#include "Output.h"
namespace mnu
{
	//---------------------------------INPUT PRODUCT--------------------------------------
	void input(const String &fname, DList<Product>& List)
	{
		ifstream inp;
		inp.open(fname);
		if (inp.fail())
		{
			throw Exception("FILE NOT EXIST");
		}
		String id_lo = fname;
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
		inp.close();
	}
	
	//-----------------------------------MAIN MENU------------------------------------------------
	void MainMenu(int& choice)
	{
		CenterPrint(TITLE, WIDTH);
		std::cout << "\n\n" << '+'; DrawLine(WIDTH - 2, '='); std::cout << '+' << "\n\n";
		LeftPrint("1.Quan ly san pham"); std::cout << '\n';
		LeftPrint("2.Quan ly khach hang"); std::cout << '\n';
		LeftPrint("3.Quan ly hoa don"); std::cout << '\n';
		LeftPrint("0.Ket thuc"); std::cout << '\n';
		LeftPrint("Lua chon cua ban :"); std::cin >> choice; cin.ignore();
		if (choice < 0 || choice>3)
		{
			throw Exception("INVALID VALUE");
		}
	}
	//------------------------------------MENU 1----------------------------------------------------
	void Menu1(int &choice)
	{
		CenterPrint(TITLE, WIDTH);
		std::cout << "\n\n" << '+'; DrawLine(WIDTH - 2, '='); std::cout << '+' << "\n\n";
		LeftPrint("1.Them san pham"); std::cout << '\n';
		LeftPrint("2.Tim kiem san pham"); std::cout << '\n';
		LeftPrint("0.Quay lai"); std::cout << '\n';
		LeftPrint("Lua chon cua ban :"); std::cin >> choice; cin.ignore();
		if (choice < 0 || choice>2)
		{
			throw Exception("INVALID VALUE");
		}
	}
	//----------------------------------MENU 1-1 ------------------------------------------------------
	void Menu1_1(int &choice)
	{
		CenterPrint(TITLE, WIDTH);
		std::cout << "\n\n" << '+'; DrawLine(WIDTH - 2, '='); std::cout << '+' << "\n\n";
		LeftPrint("1.Them bang file"); std::cout << '\n';
		LeftPrint("2.Nhap tu ban phim"); std::cout << '\n';
		LeftPrint("0.Quay lai"); std::cout << '\n';
		LeftPrint("Lua chon cua ban :"); std::cin >> choice; cin.ignore();
		if (choice < 0 || choice>2)
		{
			throw Exception("INVALID VALUE");
		}
	}
	//----------------------------------template nhap-------------------------------------------------
	template<class T>
	void Nhap(DList<T> & List, int & choice)
	{
		CenterPrint(TITLE, WIDTH);
		std::cout << "\n\n" << '+'; DrawLine(WIDTH - 2, '='); std::cout << '+' << "\n\n";
		LeftPrint("Nhap ten file:");
		String fname;
		fname.GetLine(cin);
		if (fname == String(""))
		{
			choice = 0;
			return;
		}
		input(fname, List);
		LeftPrint("Input thanh cong"); std::cout << "\n";
		Sleep(TIME_WAIT);
		choice = 1;
	}

	//----------------------------------MENU 1-2 ------------------------------------------------------
	void Menu1_2(int& choice)
	{
		CenterPrint(TITLE, WIDTH);
		std::cout << "\n\n" << '+'; DrawLine(WIDTH - 2, '='); std::cout << '+' << "\n\n";
		LeftPrint("1.Tim kiem theo ma san pham"); cout << '\n';
		LeftPrint("2.Tim kiem theo ten san pham"); cout << '\n';
		LeftPrint("3.Tim kiem theo xuat xu"); cout << '\n';
		LeftPrint("0.Quay lai"); cout << '\n';
		LeftPrint("Lua chon cua ban :"); cin >> choice; cin.ignore();
		if (choice < 0 || choice>3)
		{
			throw Exception("INVALID VALUE");
		}
	}
	//---------------------------------Chuc nang TKSP-----------------------------------------------
	namespace search_mnu
	{
		DList<Product> * ptrAns_List_For_Search = NULL;
		int cnt_Search = 0;
	}
	void Search(const DList<Product>& List, int &choice)
	{
		CenterPrint(TITLE, WIDTH);
		std::cout << "\n\n" << '+'; DrawLine(WIDTH - 2, '='); std::cout << '+' << "\n\n";
		if (search_mnu::ptrAns_List_For_Search == NULL)
		{
			String data;
			if (choice == 1)
			{
				LeftPrint("Nhap ma san phan can tim kiem :"); data.GetLine(cin);
				search_mnu::ptrAns_List_For_Search = List.FindAll(data, &Product::GetID, search_mnu::cnt_Search);
			}
			else if (choice == 2)
			{
				LeftPrint("Nhap ten san phan can tim kiem :"); data.GetLine(cin);
				search_mnu::ptrAns_List_For_Search = List.FindAll(data, &Product::GetName, search_mnu::cnt_Search);
			}
			else if (choice == 3)
			{
				LeftPrint("Nhap xuat xu san phan can tim kiem :"); data.GetLine(cin);
				search_mnu::ptrAns_List_For_Search = List.FindAll(data, &Product::GetXS, search_mnu::cnt_Search);
			}
		}
		OutputTable(*search_mnu::ptrAns_List_For_Search, search_mnu::cnt_Search);
		if (search_mnu::cnt_Search == 0)
		{
			search_mnu::ptrAns_List_For_Search = NULL;
			search_mnu::cnt_Search = 0;
			choice = 2;
			return;
		}
		LeftPrint("Nhap STT mat hang muon xem chi tiet (chon 0 de quay lai):", 0); cin >> choice; cin.ignore();
		if (choice<0 || choice>search_mnu::cnt_Search)
		{
			throw Exception("INVALID VALUE");
		}
		if (choice == 0)
		{
			search_mnu::ptrAns_List_For_Search = NULL;
			search_mnu::cnt_Search = 0;
		}
		else
		{
			system("cls");
			OutputDetail(*search_mnu::ptrAns_List_For_Search, choice);
			system("pause");
			choice = 1;
		}
	}
	
	
	//----------------------------------MENU 2 --------------------------------------------------------
	void Menu2(int &choice)
	{
		CenterPrint(TITLE, WIDTH);
		cout << "\n\n" << '+'; DrawLine(WIDTH - 2, '='); cout << '+' << "\n\n";
		LeftPrint("1.Them khach hang"); cout << '\n';
		LeftPrint("2.Tim kiem khach hang"); cout << '\n';
		LeftPrint("3.Chinh sua thong tin khach hang"); cout << '\n';
		LeftPrint("4.Xoa khach hang khoi danh sach"); cout << '\n';
		LeftPrint("5.Hien thi danh sach khach hang"); cout << '\n';
		LeftPrint("0.Quay lai"); cout << '\n';
		LeftPrint("Lua chon cua ban :"); cin >> choice; cin.ignore();
		if (choice < 0 || choice>5)
		{
			throw Exception("INVALID VALUE");
		}
	}
	//-----------------------------------MENU TT----------------------------------------------
	void MenuTT(int &choice)
	{
		CenterPrint(TITLE, WIDTH);
		std::cout << "\n\n" << '+'; DrawLine(WIDTH - 2, '='); std::cout << '+' << "\n\n";
		LeftPrint("Ban muon tiep tuc"); std::cout << '\n';
		LeftPrint("1.Tiep tuc"); std::cout << '\n';
		LeftPrint("0.Quay lai"); std::cout << '\n';
		LeftPrint("Lua chon cua ban :"); std::cin >> choice; cin.ignore();
		if (choice < 0 || choice>1)
		{
			throw Exception("INVALID VALUE");
		}
	}
	//-------------------------------------MENU TT CHO TM KIEM ----------------------------------
	void MenuTTTK(int &choice)
	{
		CenterPrint(TITLE, WIDTH);
		std::cout << "\n\n" << '+'; DrawLine(WIDTH - 2, '='); std::cout << '+' << "\n\n";
		LeftPrint("Ban muon tiep tuc"); std::cout << '\n';
		LeftPrint("1.Tiep tuc voi truy xuat cu"); std::cout << '\n';
		LeftPrint("2.Tiep tuc voi truy xuat moi"); std::cout << '\n';
		LeftPrint("0.Quay lai"); std::cout << '\n';
		LeftPrint("Lua chon cua ban :"); std::cin >> choice; cin.ignore();
		if (choice < 0 || choice>2)
		{
			throw Exception("INVALID VALUE");
		}
		if (choice == 2 || choice == 0)
		{
			search_mnu::ptrAns_List_For_Search = NULL;
			search_mnu::cnt_Search = 0;
		}
	}
	//---------------------------Create Menu Tree----------------------------------------
	struct Node
	{
		void(*ptr) (int&);
		void(*ptr1) (DList<Product>&, int&);
		void(*ptr2) (const DList<Product>&, int&);
		int num_child;
		Node ** child;
		Node(void(*ptr) (int&), int num)
			:ptr(ptr), ptr1(NULL), ptr2(NULL), num_child(num)
		{
			this->child = new Node*[this->num_child]{NULL};
		}
		Node(void(*ptr1) (DList<Product>&, int&), int num)
			:ptr(NULL), ptr1(ptr1), ptr2(NULL), num_child(num)
		{
			if (this->num_child > 0)
				this->child = new Node*[this->num_child]{NULL};
			else this->child = NULL;
		}
		Node(void(*ptr2) (const DList<Product>&, int&), int num)
			:ptr(NULL), ptr1(NULL), ptr2(ptr2), num_child(num)
		{
			if (this->num_child > 0)
				this->child = new Node*[this->num_child]{NULL};
			else this->child = NULL;
		}
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
	Node *TMenu1_1 = new Node(&Menu1_1, 3);
	Node *TMenu1_2 = new Node(&Menu1_2, 4);
	Node *TMenu1_2_all = new Node(&Search, 3);
	Node *TMenu1_2_all_TTTK = new Node(&MenuTTTK, 3);
	Node *TMenu1_2_all_TT = new Node(&MenuTT, 2);
	Node *TMenu1_1_1 = new Node(&Nhap, 2);
	Node *TMenu1_1_1_TT = new Node(&MenuTT, 2);
	void InitMenu()
	{
		TMainMenu->AddChild(TMenu1, 1);
		TMenu1->AddChild(TMenu1_1, 1);
		TMenu1_1->AddChild(TMenu1_1_1, 1);
		TMenu1_1_1->AddChild_TT(TMenu1_1_1_TT,1);
		TMenu1->AddChild(TMenu1_2, 2);
		for (int i = 1; i <= 3; i++)
		{
			TMenu1_2->AddChild(TMenu1_2_all, i);
		}
		TMenu1_2_all->AddChild_TTTK(TMenu1_2_all_TTTK, 1);
		TMenu1_2_all->AddChild_TT(TMenu1_2_all_TT, 2);
	}
	void DeleteMenu()
	{
		delete TMenu1_1_1_TT;
		delete TMenu1_2_all_TTTK;
		delete TMenu1_2_all_TT;
		delete TMenu1_1_1;
		delete TMenu1_2_all;
		delete TMenu1_2;
		delete TMenu1_1;
		delete TMenu1;
		delete TMainMenu;
	}
}
#endif
