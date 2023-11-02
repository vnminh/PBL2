#include<iostream>
#include<string>
using namespace std;
class Khachhang
{
    private:
        string MaKH;
        string TenKH;
        string Diachi;
        string Gioitinh;
        string Sdt;
    public:
        Khachhang(const string&,const string&,const string&,const string&,const string&);
        ~Khachhang();
        void Thongtin();
        string get_MaKH();
        friend ostream& operator<<(ostream&, const Khachhang&);
        friend istream& operator>>(istream&, Khachhang&);
};