#include<iostream>
#include<chrono>
#include<omp.h>
using namespace std;

unsigned long long numSteps = 0;

void TowersOfHanoi(uint_fast8_t n, uint_fast8_t x, uint_fast8_t y, uint_fast8_t z)
{
	if (n) {
		TowersOfHanoi(n - 1, x, z, y);
		//std::cout << "Move top disk from tower " << x << "to top of tower " << y << std::endl;
		//cout << "numSteps: " << numSteps;
		TowersOfHanoi(n - 1, z, y, x);
		/*#pragma omp critical
		{
			numSteps++;
		}*/

	}
}

void parallelTowers(uint_fast8_t n, uint_fast8_t x, uint_fast8_t y, uint_fast8_t z)
{
	//numSteps = 3;
	#pragma omp parallel
	{
		#pragma omp single nowait
		{
			TowersOfHanoi(n - 2, x, y, z);
		}
		#pragma omp single nowait
		{
			TowersOfHanoi(n - 2, y, z, x);
		}
		#pragma omp single nowait
		{
			TowersOfHanoi(n - 2, z, x, y);
		}
		#pragma omp single nowait
		{
			TowersOfHanoi(n - 2, x, y, z);
		}
	}
}

int main()
{
	uint_fast8_t n;
	//std::cout << "Enter n: ";
	//std::cin >> n;
	//std::cout << "You entered: " << n << std::endl;
	auto start_time = std::chrono::high_resolution_clock::now();
	//TowersOfHanoi(20, 2, 3, 4);
	parallelTowers(32, 2, 3, 4);
	auto end_time = std::chrono::high_resolution_clock::now();
	std::cout << "Seconds: " << std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() << endl;
	std::cout << " Milliseconds: " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << endl;
	std::cout << "Done" << endl;
	//cout << "NumSteps: " << numSteps << endl;
	std::cin >> n;
}

//void TowersOfHanoi(int n, int x, int y, int z)
//{
//	if (n) {
//		TowersOfHanoi(n - 1, x, z, y);
//		//std::cout << "Move top disk from tower " << x << "to top of tower " << y << std::endl;
//		TowersOfHanoi(n - 1, z, y, x);
//	}
//}
//
//int main()
//{
//	int n;
//	//std::cout << "Enter n: ";
//	//std::cin >> n;
//	//std::cout << "You entered: " << n << std::endl;
//	auto start_time = std::chrono::high_resolution_clock::now();
//	TowersOfHanoi(32, 0, 1, 2);
//	auto end_time = std::chrono::high_resolution_clock::now();
//	std::cout << std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() << ":";
//	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << ":";
//	std::cout << "Done";
//	std::cin >> n;
//}