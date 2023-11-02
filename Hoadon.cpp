#include<iostream>
#include "Hoadon.h"
using namespace std;
Hoadon::Hoadon(const string& id_HD, const string& NgaymuaHD)
    : id_HD(id_HD), NgaymuaHD(NgaymuaHD)
{
    this->Tongtien = 0;
}
Hoadon::~Hoadon(){

}
string Hoadon::getid_HD()
{
    return this->id_HD;
}
ostream& operator<<(ostream& o, const Hoadon& HD)
{
    o << HD.id_HD << " " << HD.NgaymuaHD << endl;
    return o;
}
istream& operator>>(istream& i, Hoadon& HD)
{
    cout << "Nhap ma hoa don: ";
    i >> HD.id_HD;
    cout << "Nhap ngay cua hoa don: ";
    i >> HD.NgaymuaHD;
    cout << "Tong tien cua hoa don: ";
    i >> HD.Tongtien;
    return i;
}