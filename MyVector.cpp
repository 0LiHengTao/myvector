#include<iostream>
#include"MyVector.hpp"
using namespace std;

int main()
{
	MyVector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	v.insert(v.begin(), 10);
	//cout<<v[0]<<endl;

	v.erase(v.begin());
	//cout << v[0] << endl;

	v.pop_back();
	//cout << v[2] << endl;
	//cout << v[3] << endl;
	int flag = 0;

	flag=v.empty();
	//cout << flag << endl;
	return 0;
}