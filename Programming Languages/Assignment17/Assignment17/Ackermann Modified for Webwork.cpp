#include <iostream>
#include <cmath>
#include <time.h> 
#include <stdio.h>
using namespace std;

int A(int, int);

int main() {
	clock_t t;
	/*
	int highestnum;
	t = clock();
	for (int n = 0; n < 11; n++)
	{
		highestnum = A(3, n);
	}
	t = clock() - t;
	cout << "Highest Reached: " << highestnum << endl;
	printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	*/
	cout << A(2, 2) << endl;
	char stop;
	cin >> stop;
}

int A(int m, int n){
	if (m == 0)
	{
		return 2*n;
	}
	else if (n == 0 && m >= 1)
	{
		return 0;
	}
	else if (n == 1 && m >= 1)
	{
		return 2;
	}
	else
	{
		A(m - 1, A(m, n - 1));
	}
}