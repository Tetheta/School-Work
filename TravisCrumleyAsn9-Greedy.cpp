/*****************************************************************************
Program file name: TravisCrumleyAsn9-Greedy.cpp	  OS: Windows 10  Assignment: #9
Programmer: Travis Crumley Class: WWU CPTR 454    Date: 11/01/2015
Compiler: Visual Studio 2015

Assistance/references:
Description: Implement Greedy Algorithm
Inputs:
Outputs: 

Special Comments:

~~~~~~~~~~~~~~~~~~~~~~~~~~Grading Criteria~~~~~~~~~~~~~~~~~~~~~~~~~~

Assignment Requirements: ___/3.0

Code Format/Cosmetics: ___/3.0

Header & Code Comments: ___/2.0

Output Format/Cosmetics: ___/2.0
***Does Not Compile***: ___ (-10.0)
***Late Work Deduction***: ___ (-0.5/day)
Total Grade: ___/10.0

*****************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



void greedyKnapsack(vector<int> s, vector<int> p, vector<float> x, int n, int M) 
{
	// Probably not the most efficient solution, but I have a test to study
	// for and I wanted to mess with lambda functions and in-function structs.

	// s: Size vector
	// p: Profit vector
	// x: Solution vector
	// n: Number of items
	// M: Knapsack Capacity

	// Created so I can easily sort but keep track of locations
	// Float fraction, int location
	struct ratio {
		float fraction;
		int location;
	};

	// Need to sort the items according to non-increasing values of p[i]/s[i]
	// First make a vector of those values
	vector<ratio> ratios;
	for (int i = 0; i < n; i++)
	{
		ratio r;
		r.fraction = (float)p[i] / (float)s[i];
		r.location = i;
		ratios.push_back(r);
	}
	// Now sort it, using a lambda function because they're neat
	sort(ratios.begin(), ratios.end(), [](ratio i, ratio j) {return (i.fraction > j.fraction); });
	// Just to make sure my ratio vector is correct
	for (int i = 0; i < n; i++) {
		cout << "ratios[" << i << "]: " << ratios[i].fraction << " loc: " << ratios[i].location << endl;
	}

	// Set all solution vector to zeroes
	x.assign(n, 0.0f);

	// Set up variables to decide on the order
	float r = M;
	int i = 0;
	// Go through the ratio vector subtracting the sizes from r
	// This should give the right capacities for the solution vector
	while (s[ratios[i].location] <= r && i < n)
	{
		x[ratios[i].location] = 1;
		r = r - s[ratios[i].location];
		i++;
	}
	// The fractional capacity is left over, set it
	if (i < n)
	{
		x[ratios[i].location] = ((float)r / (float)s[ratios[i].location]);
	}
	// Output the solution
	for (int i = 0; i < n; i++) {
		cout << "x[" << i << "]: " << x[i] << endl;
	}
}

int main() 
{
	vector<int> s = { 2, 3, 5, 7, 1, 4, 1 };
	vector<int> p = { 10, 5, 15, 7, 6, 18, 3 };
	vector<float> x;
	greedyKnapsack(s, p, x, 7, 15);
}