#include <iostream>
#include <cmath>
#include <time.h> 
using namespace std;

long double A(long double, long double);

int main() {
	clock_t t;
	cout << A(2, 2) << endl;
	/*
	t = clock();
	for (long double n = 0; n < 100000; n++)
	{
		cout << A(3, n) << endl;
	}
	t = clock() - t;
	cout << "Time: " << t;
	*/
	char stop;
	cin >> stop;
}

long double A(long double m, long double n){
	if (m == 0)
	{
		return n + 1;
	}
	else if (m == 1)
	{
		return n + 2;
	}
	else if (m == 2)
	{
		return (2*n + 3);
	}
	else if (m == 3)
	{
		return (pow(2, (n + 3)) - 3);
	}
	else if (n == 0)
	{
		A(m - 1, 1);
	}
	else
	{
		A(m - 1, A(m, n - 1));
	}
}