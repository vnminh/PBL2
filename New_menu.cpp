#include<iostream>
void Menu1(int &choice) //Menu san pham
{
	CenterPrint(TITLE, width);
	cout << "\n\n" << '+'; DrawLine(width - 2, '='); cout << '+' << "\n\n";
	int leftspace = floor((width - TITLE.GetLength()) / 2);
	LeftPrint("1.Them san pham", leftspace); cout << '\n';
	LeftPrint("2.Tim kiem san pham", leftspace); cout << '\n';
	LeftPrint("0.Quay lai", leftspace);
	LeftPrint("Lua chon cua ban :", leftspace); cin >> choice;
	if (choice < 0 || choice>2)
	{
		throw Exception("INVALID VALUE");
	}
}
void Menu2(int &choice)
{
	CenterPrint(TITLE, width);
	cout << "\n\n" << '+'; DrawLine(width - 2, '='); cout << '+' << "\n\n";
	int leftspace = floor((width - TITLE.GetLength()) / 2);
	LeftPrint("1.Them khach hang", leftspace); cout << '\n';
	LeftPrint("2.Tim kiem khach hang", leftspace); cout << '\n';
    LeftPrint("3.Chinh sua thong tin khach hang", leftspace); cout << '\n';
	LeftPrint("4.Xoa khach hang khoi danh sach", leftspace); cout << '\n';
    LeftPrint("5.Hien thi danh sach khach hang", leftspace); cout << '\n';
    LeftPrint("0.Quay lai", leftspace);
	LeftPrint("Lua chon cua ban :", leftspace); cin >> choice;
	if (choice < 0 || choice>5)
	{
		throw Exception("INVALID VALUE");
	}
}
void Menu3(int &choice)
{
	CenterPrint(TITLE, width);
	cout << "\n\n" << '+'; DrawLine(width - 2, '='); cout << '+' << "\n\n";
	int leftspace = floor((width - TITLE.GetLength()) / 2);
	LeftPrint("1.Tinh hoa don", leftspace); cout << '\n';
	LeftPrint("2.Tinh doanh thu", leftspace); cout << '\n';
    LeftPrint("3.Truy xuat hoa don", leftspace); cout << '\n';
    LeftPrint("0.Quay lai", leftspace);
	LeftPrint("Lua chon cua ban :", leftspace); cin >> choice;
	if (choice < 0 || choice>3)
	{
		throw Exception("INVALID VALUE");
	}
}
void Menu_Timkiemsanphan(int& choice)
{
	LeftPrint("1.Tim kiem theo ma san pham", leftspace); cout << '\n';
	LeftPrint("2.Tim kiem theo ten san pham", leftspace); cout << '\n';
	LeftPrint("3.Tim kiem theo ten nha san xuat", leftspace); cout << '\n';
	LeftPrint("4.Tim kiem theo gia san pham", leftspace); cout << '\n';
	LeftPrint("0.Quay lai", leftspace);
	LeftPrint("Lua chon cua ban :", leftspace); cin >> choice;
	if (choice < 0 || choice>4)
	{
		throw Exception("INVALID VALUE");
	}
}

void Menu_Timkiemkhachhang(int& choice)
{
    LeftPrint("1.Tim kiem theo ma khach hang", leftspace); cout << '\n';
	LeftPrint("2.Tim kiem theo ten khach hang", leftspace); cout << '\n';
	LeftPrint("0.Quay lai", leftspace);
	LeftPrint("Lua chon cua ban :", leftspace); cin >> choice;
	if (choice < 0 || choice>2)
	{
		throw Exception("INVALID VALUE");
	}
}
void Menu_Timkiemhoadon(int& choice)
{
	LeftPrint("1.Tim kiem theo ma khach hang", leftspace); cout << '\n';
	LeftPrint("2.Tim kiem theo ngay mua", leftspace); cout << '\n';
	LeftPrint("3.Tim kiem theo mat hang",leftspace); cout <<"\n";
	LeftPrint("0.Quay lai", leftspace);
	LeftPrint("Lua chon cua ban :", leftspace); cin >> choice;
	if (choice < 0 || choice>3)
	{
		throw Exception("INVALID VALUE");
	}
}