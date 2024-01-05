#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;
vector<string> productNames = {"Banh Orea", "Keo chupachup", "Ca rot", "Hanh tay", "Ot chuong", "Hat de", "Ngu Coc",
                            "Nho kho","Sua chua","Nuoc ngot 7Up","Nuoc ngot Cocacola","Bo", "Banh custas", "Chocolate"};
vector<string> origin = {"VN","China","USA","ENG","JAP","KOR"};
vector<string> batchIDs = {"L001", "L002","L003","L004","L005"};
vector<string> mfgDate = {"31/10/2022", "1/10/2022", "1/11/2022", "1/12/2022", "1/1/2022", "1/2/2023", "1/3/2023", "1/4/2023", "1/5/2023"};
vector<string> expDate = {"1/10/2024", "1/11/2024", "1/12/2024", "21/12/2024", "1/1/2025", "15/1/2025", "14/4/2025", "16/8/2025", "1/1/2024", "1/2/2026"};
vector<int> prices = {13000, 20000, 10000, 46000, 1000, 70000, 90000, 5000};
vector<int> quantities = {5000, 2000, 1000, 500, 200, 100, 50, 30,20};
string randomProductID()
{
    int k = rand();
    string ID = "MH";
    k%=100000;
    string t=string("00000")+to_string(k);
    int i=t.length();
    ID+=t.substr(i-5,5);
    k=k%2;
    ID+=string("0")+to_string(k);
    return ID;
}
string randomProductName()
{
    int k = rand();
    return productNames[k % productNames.size()];
}
string randomOrigin()
{
    int k = rand();
    return origin[k % origin.size()];
}
string randomBatchID()
{
    int k = rand();
    return batchIDs[k % batchIDs.size()];
}
string randomMfgDate()
{
    int k = rand();
    return mfgDate[k % mfgDate.size()];
}
string randomExpDate()
{
    int k = rand();
    return expDate[k % expDate.size()];
}
int randomPrice()
{
    int k = rand();
    return prices[k % prices.size()];
}
int randomQuantity()
{
    int k = rand();
    return quantities[k % quantities.size()];
}
int main()
{
    cout << "Nhap so ban ghi muon khoi tao ngau nhien: ";
	int n; cin >> n;
	getchar();
	cout << "Nhap ten file muon khoi tao: ";
	string filename; getline(cin,filename);
	filename += ".txt";
    srand(time(0)); // Khởi tạo seed cho hàm rand()
    ofstream file(filename);
    string BatchID = randomBatchID();
    file << "Product ID(VD:MH-----0-)" << "," << "ProductName()" << "," << "Origin()" << "," << "Batch ID(VD:L---)" << "," 
    << "MFG(dd/mm/yyyy)" << "," << "EXP(dd/mm/yyyy)" << "," << "Price" << "," << "Quantity/Weight" << endl;
    for (int i = 0; i < n-1; i++)
    {
        file << randomProductID() << "," << randomProductName() << "," << randomOrigin() << "," << BatchID << "," 
        << randomMfgDate() << "," << randomExpDate() << "," << randomPrice() << "," << randomQuantity() << endl;
    }
    file << randomProductID() << "," << randomProductName() << "," << randomOrigin() << "," << BatchID << "," 
    << randomMfgDate() << "," << randomExpDate() << "," << randomPrice() << "," << randomQuantity();
    file.close();
    return 0;
}