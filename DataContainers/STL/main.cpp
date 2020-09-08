#include <iostream>
#include<list>
//using namespace std;

void main()
{
	setlocale(LC_ALL, "");
	std::list<int> my_list = { 4, 5, 6, 78, 4 };
	for (std::list<int>::iterator it = my_list.begin(); it != my_list.end(); it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
	for (std::list<int>::reverse_iterator it = my_list.rbegin(); it != my_list.rend(); it--)
	{
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
}