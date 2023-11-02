#include<iostream>
using namespace std;
class Hoadon
{
    private:
        string id_HD;
        string NgaymuaHD;
        long long Tongtien;
    public:
        Hoadon(const string&,const string&);
        ~Hoadon();
        void Thongtinhoadon();
        string getid_HD();
        friend ostream& operator<<(ostream&, const Hoadon&);
        friend istream& operator>>(istream&, Hoadon&);
};