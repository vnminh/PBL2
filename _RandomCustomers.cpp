#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstring>
using namespace std;
vector<string> firstNames = {"Nguyen", "Tran", "Le", "Ho", "Dang", "Ly", "Vuong", "Trinh"};
vector<string> midNames1 = {"", "Van", "Thi", "Quy", "Huong", "Thai", "Nhat", "Huu", "Dinh", "Phi", "Vo"};
vector<string> midNames2 = {"", "Ngoc", "Thanh", "Quoc", "Manh", "Quy"};
vector<string> lastNames = {"Ba", "Cuong", "Duyen", "Phuc", "Minh", "Hai", "Bao", "Danh", "Lam", "Khoa", "Nga", "Le", "Quyen", "Tien"};
vector<string> areaCodes = {"09", "08", "07", "05", "03"};
vector<string> districts = {"Lien Chieu", "Thanh Khe", "Son Tra", "Ngu Hanh Son", "Hai Chau"};
vector<string> streets = {"Nguyen Chanh", "Nguyen Luong Bang", "Nam Cao", "Ngo Si Lien", "Ton Duc Thang", "Hoang Thi Loan","Ho Tung Mau","Ngo Thi Nham","Ngo Van So"};
vector<string> houseNumbers = {"", "K119/20", "K22/41", "K14/36"};
string randomName()
{
	int k = rand();
	// cout << k << "\n";
	string firstName = firstNames[k % firstNames.size()];
	string midName1 = midNames1[k % midNames1.size()];
	string midName2 = midNames2[k % midNames2.size()];
	string lastName = lastNames[k % lastNames.size()];
	if (midName1 == "" && midName2 == "")
	{
		return firstName + " " + lastName;
	}
	else if (midName1 != "" && midName2 != "")
	{
		return firstName + " " + midName1 + " " + midName2 + " " + lastName;
	}
	else
	{
		string tmp = max(midName1, midName2);
		return firstName + " " + tmp + " " + lastName;
	}
}
string randomPhoneNumber()
{
	string number = areaCodes[rand() % areaCodes.size()];
	for (int i = 0; i < 7; i++)
	{
		number += to_string(rand() % 10);
	}
	return number;
}
string randomAddress()
{
	int k = rand();
	string houseNumber = houseNumbers[k % houseNumbers.size()];
	string street = streets[k % streets.size()];
	string district = districts[k % districts.size()];
	string HN;
	if( houseNumber == "" )
	{
		int m = 1 + rand() % (120);
		HN = to_string(m);	
		return HN + " " + street;
	}
	else return houseNumber + " " + street;
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
	file << "NameOfCustomer," << "PhoneNumber(10character),"<<"AddressOfCustomer"<< endl;
	for (int i = 0; i < n-1; i++)
	{
		// file << randomName() << "\n";
		file << randomName() << "," << randomPhoneNumber() << "," << randomAddress() << endl;
		// file << rand() << "\n";
	}
	file << randomName() << "," << randomPhoneNumber() << "," << randomAddress();
	file.close();
	return 0;
}
