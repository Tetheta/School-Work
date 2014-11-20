#include <iostream>
#include <iomanip>
using namespace std;

int main() 
{
	double x, y, z;
	x = 4;
	y = 21;
	z = 100000000000000000.;
	double xy = x + y;
	double yz = y + z;
	double sum1 = xy + z;
	double sum2 = x + yz;
	cout << setprecision(20) << sum1 << endl;
	cout << setprecision(20) << sum2 << endl;
	//Output:
	//sum1 = 100000000000000030
	//sum2 = 100000000000000020

	//Stop the window from closing
	char stp;
	cin >> stp;
}