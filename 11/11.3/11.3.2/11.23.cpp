#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

using std::multimap;
using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::istringstream;

int main()
{
	multimap<string, vector<string>> family;
	string line;
	vector<string> lastname;
	while(getline(cin, line))
	{
		string surname, name;
		istringstream record(line);
		record >> surname;
		while(record >> name)
		{
			lastname.push_back(name);
		}
		family.insert({surname, lastname});
	}
	cout << "定义的map如下：" << endl;
	for(const auto &f : family)
	{
		cout << f.first << " ";
		for(const auto &s : f.second)
		{
			cout << s << " ";
		}
		cout << endl;
	}
	return 0;
}
