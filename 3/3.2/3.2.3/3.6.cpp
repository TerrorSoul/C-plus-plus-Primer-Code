#include <iostream>
#include <string>

using std::string;
using std::cin; using std::cout; using std::endl;

int main()
{
	string s;
	
	cout << "请输入您要处理的字符串：";
	cin >> s;
	
	for (auto &c : s)
	    c = 'X';
	
	cout << s << endl;
	
	return 0;
}
