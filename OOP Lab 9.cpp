#include<iostream>

#include"List.h"

using namespace std;

int main() {
	system("chcp 1251 > null");
	List<int> list;
	try
	{
		list(5);
	}
	catch (const char* a)
	{
		cout << a;
	}
	List<int>::iterator a(list);
	list[4] = 5;

	try
	{
		cout << (a + 4)->data;
		
	}
	catch (const char* a)
	{
		cout << a;
	}
	return 0;
}