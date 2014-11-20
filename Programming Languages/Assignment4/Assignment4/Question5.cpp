#include <iostream>
using namespace std;

/*
Results (1 = pass, 0 = fail)
a= 0, b= 0, c= 1, d= 0
aa= 0, ab= 1, ac= 1, ad= 0, ba= 0, bb= 1, bc=0 , bd=0 ,
ca= 0, cb= 0,  cc= 0, cd= 0, da= 0, db= 0, dc= 0, dd= 0,
aabbb= 1, aaabbbccc= 0, aaacc= 0, aacccd= 1, aaad= 0, aadd= 0,
bbbb= 1, bbcc= 0, bbbd= 1,
cccc= 0, ccbb= 0, cccd= 1

*/
string str = "bbbd";
char token(int i)
{
	return str[i];
}

int main()
{
	int i = 0;
	//While a
	while (token(i) == 'a' && token(i + 1) != 'd')
	{
		i++;
	}
	if (token(i) == 'a' && token(i + 1) == 'd')
	{
		cout << "Failure" << endl;
		goto stop;
	}
	if (token(i) == 'c' && token(i + 1) == '\0')
	{
		cout << "Success" << endl;
		goto stop;
	}
	//while c case 1
	while (token(i) == 'c' && token(i + 1) == 'c')
	{
		i++;
	}
	if (token(i) == 'c' && token(i + 1) != 'd')
	{
		cout << "Failure" << endl;
		goto stop;
	}
	if (token(i) == 'b' && token(i + 1) == 'd')
	{
		cout << "Failure" << endl;
		goto stop;
	}

	//While b
	while (token(i) == 'b' && token(i + 1) != '\0')
	{
		i++;
	}
	if (token(i) == 'b' && token(i + 1) == '\0')
	{
		cout << "Success" << endl;
		goto stop;
	}

	//While c case 2
	while (token(i) == 'c')
	{
		i++;
	}
	if (token(i) == 'd' && token(i+1) == '\0')
	{
		cout << "Success" << endl;
		goto stop;
	}
	else
	{
		cout << "Failure" << endl;
		goto stop;
	}
	stop:
	//stop window from closing
	char stp;
	cin >> stp;
}