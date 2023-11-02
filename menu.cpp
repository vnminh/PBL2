#include <iostream>
using namespace std;
void Menu()
{
    int luachon;
    do
    {
        cout << "==========MENU==========\n";
        cout << "1. Doc danh sach khach hang\n";
        cout << "2. Them khach hang\n";
        cout << "3. Tim kiem khach hang\n";
        cout << "4. Xoa khach hang\n";
        cout << "5. Xuat ra danh sach khach hang\n";
        cout << "6. Sua thong tin khach hang\n";
        cout << "7. Them mat hang vao kho\n";
        cout << "8. Xoa mat hang\n";
        cout << "9. Tim mat hang\n";
        cout << "10. Xuat ra danh sach mat hang\n";
        cout << "11. Tinh hoa don\n";
        cout << "12. Tinh doanh thu\n";
        cout << "13. Xuat hoa don\n";
        cout << "Chon 0 de thoat\n";
        cout << "========================\n";
        cout << "Lua chon cua ban la: ";
        cin >> luachon;
        if (luachon < 0 || luachon > 20)
        {
            cout << "Moi nhap lai lua chon tu 1 -> 20\n";
            system("pause");
            system("cls");
        }
        switch (luachon)
        {
            case 1: //Doc danh sach khach hang tu file
            {
                break; 
            }
            case 2:
            {
                cout << "Nhap thong tin cua khach hang\n";
                // Xu ly trhop id da ton tai, id ko hop le
                // Luu thong tin vao file khachhang.txt
                break;
            }
            case 3:
            {
                cout << "1. Tim kiem theo id cua khach hang\n";
                cout << "2. Tim kiem theo ten cua khach hang\n";
                cout << "Nhap lua chon cua ban: ";
                int choice;
                cin >> choice;
                if (choice == 1)
                {
                    getchar();
                    string id_search;
                    cout << "Nhap vao ma khach hang can tim kiem: ";
                    getline(cin, id_search);
                    cout << id_search;
                    system("pause");
                }
                else if (choice == 2)
                {
                    getchar();
                    string name_search;
                    cout << "Nhap vao ten khach hang can tim kiem: ";
                    getline(cin, name_search);
                    cout << name_search;
                    system("pause");
                }
                getchar();
                break;
            }
            case 4: //Xoa khach hang
            {
                cout << "1. Xoa theo id cua khach hang\n";
                cout << "2. Xoa theo ten cua khach hang\n";
                int choice;
                cin >> choice;
                if (choice == 1)
                {
                    getchar();
                    cout << "Nhap vao id ma ban muon xoa\n";
                    string id_delete;
                    getline(cin, id_delete);
                    cout << id_delete;
                    //Kiem tra trong danh sach co khach hang co id_KH = id_delete ko
                    cout << "Ban co muon xoa khong?\n";
                    cout << "An phim N de huy thao tac xoa\n";
                    char kt; cin >> kt;
                    if(kt != 'N')
                    {
                        //Thao tac xoa.
                    }
                    else break;
                    system("pause");
                }
                else if (choice == 2)
                {
                    getchar();
                    string name_delete;
                    getline(cin, name_delete);
                    cout << name_delete;
                    system("pause");
                }
                break;
            }
            case 5:     //In ra danh sach khach hang
            {

                break;
            }
            case 6:     //Chinh sua thong tin khach hang
            {
                getchar();
                cout << "Nhap Id cua khach hang can duoc chinh sua: \n";
                string id_update;
                getline(cin,id_update);
                //Check trong danh sach co khach hang co id = id_update hay ko
                //Trhop co id trong danh sach
                //Nhap thong tin ma ban muon thay doi
                //Co muon thay doi khong => Co => Thay doi danh sach va luu vao file Khachhang.txt | => Ko => break;
                break;
            }
            case 7: 
            {   
                // Them lo hang tu file vao kho
                // In ra kho hang sau khi da nhap them
                break;
            }
            case 8: 
            {
                //Xoa mat hang khi het han su dung
                break;
            }
            case 9:
            {
                cout << "1. Tim kiem mat hang theo ma mat hang\n";
                cout << "2. Tim kiem mat hang theo ten mat hang\n";
                cout << "3. Tim kiem mat hang theo ten nha cung cap\n";
                cout << "4. Tim kiem mat hang sap het han\n";
                int choice; cin >> choice;
                if(choice == 1)
                {
                    getchar();
                    string id_search;
                    getline(cin,id_search);
                    //Tim kiem va hien thi danh sach. Neu ko co in ra ko co trong danh sach mat hang
                }
                else if(choice == 2)
                {
                    getchar();
                    string name_search;
                    getline(cin,name_search);
                    //Tim kiem va hien thi danh sach. Neu ko co in ra ko co trong danh sach mat hang
                }
                else if(choice == 3)
                {
                    getchar();
                    string ncc_search;
                    getline(cin,ncc_search);
                    //Tim kiem va hien thi danh sach. Neu ko co in ra ko co trong danh sach mat hang
                }
                else
                {
                    cout << "Nhap so ngay ma ban muon kiem tra: ";
                    bool check;
                    int date;
                    do
                    {
                        check = false;        
                        cin >> date;
                        if(date < 0)
                        {
                            cout << "So ngay nhap vao la 1 so khong am!\n";
                            cout << "Moi ban nhap lai: ";
                            check = true;
                        }
                    } while(check);
                    cout << "Nhung mat hang sap het han trong " << date << "ngay nua la:\n"; 
                }
                break;
            }
            case 10:
            {
                cout << "Danh sach mat hang:\n";
                // Doc file mathang.txt
                break;
            }
            case 11:
            {
                //Tinh hoa don
                //Khach hang (idKH) va mathang (idMathang)
                //Tien can tra, tu khau tru va them khach hang vao danh sach KH neu mua lan dau tien
                break;
            }
            case 12:
            {
                //Tinh doanh thu
                cout << "Tinh doanh thu tu ngay .. toi ngay ..\n";
                break;
            }
            case 13:
            {
                //Xuat hoa don
                cout << "Xuat hoa don theo khach hang\n";
                cout << "Xuat hoa don theo mat hang\n"; //? 
                cout << "Xuat hoa don cu the\n";    //?
                break;
            }
            //     cout << "11. Tinh hoa don\n";
            // cout << "12. Tinh doanh thu\n";
            // cout << "13. Xuat hoa don\n";
        }
    } while (luachon);
}
int main()
{
    Menu();
}