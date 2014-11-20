/*
Program file name : Travis.Crumley.cpp		OS: Windows 8          		Assignment # : 6
Programmer : Travis Crumley				    Class : CPTR 143			Date : 5/16/2014
Compiler : Visual Studio 2013

Assistance / references :
Lectures posted on common drive(K : \common)
Lectures in K drive, Dr. Klein via email

Description : A C++ Program that tests three different probing methods for hash tables
The methods are: Linear, Random, and Prime
Each is implemented as its own function completely independent of anything else
and called in main.

Inputs : None
Outputs : Probing Results for each of the different methods

Special Comments : 

~~~~~~~~~~~~~~~~~~~~~~~~~~Grading Criteria~~~~~~~~~~~~~~~~~~~~~~~~~~
Assignment Requirements ___ / 3.0
Code Format / Cosmetics ___ / 3.0
Header & Code Comments : ___ / 2.0
Output Format / Cosmetics ___ / 2.0

***Does Not Compile*** : ___(-10.0)
***Late Work Deduction*** : ___(-0.5 / day)
Total Grade : ___ / 10.0

*****************************************************************************/

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const int tableSize = 1009;
bool hashTable[tableSize];

inline void clearHashTable()
{
	for (int i = 0; i < tableSize; i++)
	{
		hashTable[i] = false;
	}
}

void linearStore()
{
	int key, endKey;
	long int probes;
	cout << "Linear Probing\n";
	//Vary the Hash table's loading factor
	for (float alpha = 0; alpha < 0.95; alpha += 0.05)
	{
		//Initialize no. of probes
		probes = 0;
		//Simulate 1000 times
		for (int times = 1; times <= 1000 ; times++)
		{
			clearHashTable(); //Clear the hash table
			//Populate the hash table to alpha level
			for (int i = 1; i <= int(alpha*tableSize); i++)
			{
				key = rand() % tableSize;
				endKey = (key - 1) % tableSize;
				while ((hashTable[key] == true) && (key != endKey))
				{
					key = (key + 1) % tableSize;
				}
				hashTable[key] = true;
			}
			//Now simulate 1000 hashes for this particular table state
			for (int times2 = 1; times2 <= 1000; times2++)
			{
				key = rand() % tableSize;
				endKey = (key - 1) % tableSize;
				while ((hashTable[key] == true) && (key != endKey))
				{
					key = (key + 1) % tableSize;
					probes++;
				}
			} //End 1000 hashes for a given table state
		} // End 1000 simulations of tables at a given load factor
		cout << setiosflags(ios::showpoint) << setprecision(2); //Output avg no. of probes.
		cout << char(224) << " = " << alpha << " probes = " << probes / 1000000. << endl;
	} //End alpha load factor
}

void primeStore()
{
	int key, endKey;
	long int probes;
	cout << "Prime Probing\n";
	//Vary the Hash table's loading factor
	for (float alpha = 0; alpha < 0.95; alpha += 0.05)
	{
		//Initialize no. of probes
		probes = 0;
		//Simulate 1000 times
		for (int times = 1; times <= 1000; times++)
		{
			clearHashTable(); //Clear the hash table
			//Populate the hash table to alpha levels
			for (int i = 1; i <= int(alpha*tableSize); i++)
			{
				key = rand() % tableSize;
				endKey = (key - 1) % tableSize;
				while ((hashTable[key] == true) && (key != endKey))
				{
					key = (key + 7) % tableSize; //7 for prime probing
				}
				hashTable[key] = true;
			}
			//Now simulate 1000 hashes for this particular table state
			for (int times2 = 1; times2 <= 1000; times2++)
			{
				key = rand() % tableSize;
				endKey = (key - 1) % tableSize;
				while ((hashTable[key] == true) && (key != endKey))
				{
					key = (key + 7) % tableSize; //7 for prime probing
					probes++;
				}
			} //End 1000 hashes for a given table state
		} // End 1000 simulations of tables at a given load factor
		cout << setiosflags(ios::showpoint) << setprecision(2); //Output avg no. of probes.
		cout << char(224) << " = " << alpha << " probes = " << probes / 1000000. << endl;
	} //End alpha load factor
}

void randomStore()
{
	int key, endKey;
	long int probes;
	cout << "Random Probing\n";
	//Vary the Hash table's loading factor
	for (float alpha = 0; alpha < 0.95; alpha += 0.05)
	{
		//Initialize no. of probes
		probes = 0;
		//Simulate 1000 times
		for (int times = 1; times <= 1000; times++)
		{
			clearHashTable(); //Clear the hash table
			//Populate the hash table to alpha level
			for (int i = 1; i <= int(alpha*tableSize); i++)
			{
				key = rand() % tableSize;
				endKey = (key - 1) % tableSize;
				//Set up random probing
				srand(key);
				while ((hashTable[key] == true) && (key != endKey))
				{
					key = (key + rand()) % tableSize; //rand() for random probing
				}
				hashTable[key] = true;
			}
			//Now simulate 1000 hashes for this particular table state
			for (int times2 = 1; times2 <= 1000; times2++)
			{
				key = rand() % tableSize;
				endKey = (key - 1) % tableSize;
				//Set up random probing
				srand(key);
				while ((hashTable[key] == true) && (key != endKey))
				{
					key = (key + rand()) % tableSize; //rand() for random probing
					probes++;
				}
			} //End 1000 hashes for a given table state
		} // End 1000 simulations of tables at a given load factor
		cout << setiosflags(ios::showpoint) << setprecision(2); //Output avg no. of probes.
		cout << char(224) << " = " << alpha << " probes = " << probes / 1000000. << endl;
	} //End alpha load factor
}

int main()
{
	linearStore();
	primeStore();
	randomStore();
	system("PAUSE");
	return EXIT_SUCCESS;
}