#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	const int ROW_NUMS = 10000000;
	ofstream os("bookList.csv");
	
	string line = "";
	
	for (int i = 0; i < ROW_NUMS; i++)
	{
		line = "";
		
		//id
		line += to_string(i) + string(",");
		
		//title
		line += string("title") + to_string(i) + string(",");
		
		//author 
		line += string("author") + to_string(i % 10000);
		
		os << line << endl;
		if (i % 100000 == 0)
			cout << "write:" << line << endl;
	}

	os.close();

	ifstream is("bookList.csv");
	char tmp[255];

	for (int i = 0; i < ROW_NUMS; i++)
	{
		is.getline(tmp, 254);

		if (i % 100000 == 0)
		{
			cout << "read:" << tmp << endl;
		}
		
	}
	
	is.close();
	return 0;
}