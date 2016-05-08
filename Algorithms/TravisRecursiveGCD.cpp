/*
Code by Travis Crumley 9/29/2015
A recursive implementation of the
additive version of Euclid's Algorithm
*/
#include <iostream>
using namespace std;

int GCD(int m, int n)
{
	if (m != n)
	{
		if (m > n)
		{
			m = GCD(m - n, n);
		}
		else
		{
			m = GCD(m, n - m);
		}
	}
	return m;
}

void main()
{
	int num1, num2;
	while (true)
	{
		cout << "Enter the two numbers:" << endl;
		cin >> num1;
		cout << endl;
		cin >> num2;
		cout << "GCD: " << GCD(num1, num2) << endl;
	}
}