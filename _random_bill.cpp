#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
vector<int> DoM{0,31,28,31,30,31,30,31,31,30,31,30,31};


int main()
{
    string p_name,c_name,f;
    cout<<"ten file product : ";getline(cin,p_name);
    cout<<"ten file customer: ";getline(cin,c_name);
    cout<<"ten file out     : ";getline(cin,f);
    ifstream p(p_name),c(c_name);
    ofstream fo(f);
    string t;
    getline(c,t);
    getline(p,t);
    for (int i=0;i<10;i++)
    {
        int m=rand()%12+1;
        int d=rand()%DoM[m]+1;
        fo<<to_string(d)+"/"+to_string(m)+"/2023"<<endl;// ngay
        fo<<"00:00:00"<<endl;// gio
        getline(c,t); 
        stringstream ss(t);
        string name,phone,add;
        getline(ss,name,',');
        getline(ss,phone,',');
        getline(ss,add);
        fo<<phone+"\n"+name+"\n"+add+"\n";// thong khach hang
        int product=rand()%10+1;
        fo<<product<<"\n";// so sp
        for (int i=0;i<product;i++)
        {
            getline(p,t);
            stringstream ss1(t);
            string id,name,xs,lo,nsx,hsd,price,sl;
            getline(ss1,id,',');
            getline(ss1,name,',');
            getline(ss1,xs,',');
            getline(ss1,lo,',');
            getline(ss1,nsx,',');
            getline(ss1,hsd,',');
            getline(ss1,price,',');
            getline(ss1,sl);
            fo<<id+lo+"\n";
            int SL=rand()%stoi(sl)+1;
            fo<<SL<<endl;
        }
    }
    
    return 0;
}