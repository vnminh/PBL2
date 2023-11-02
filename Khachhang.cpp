#include<iostream>
#include "Khachhang.h"
using namespace std;
Khachhang::Khachhang(const string& MaKH, const string& TenKH, const string& Diachi, const string& Gioitinh, const string& Sdt)
    : MaKH(MaKH), TenKH(TenKH), Diachi(Diachi), Gioitinh(Gioitinh), Sdt(Sdt)
{ 
}
Khachhang::~Khachhang(){

}
string Khachhang::get_MaKH()
{
    return this->MaKH;
}

ostream& operator<<(ostream& o, const Khachhang& k)
{
    o << k.MaKH << " " << k.TenKH << " " << k.Gioitinh << " "
    << k.Diachi << " " << k.Sdt;
    return o;
}
istream& operator>>(istream& i, Khachhang& k)
{
    cout << "Nhap ma khach hang: ";
    i >> k.MaKH;
    cout << "Nhap ten khach hang: ";
    i >> k.TenKH;
    cout << "Nhap gioi tinh khach hang: ";
    i >> k.Gioitinh;
    cout << "Nhap dia chi khach hang: ";
    i >> k.Diachi;
    cout << "Nhap so dien thoai cua khach hang: ";
    i >> k.Sdt;
    return i;
}