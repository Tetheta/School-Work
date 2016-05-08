//// Code by Travis Crumley for CPTR 454 Assignment 4, 10/14/2015
//
#include<iostream>
#include<chrono>
//
////unsigned long long numSteps = 0;
//
//void TowersOfHanoi(uint_fast8_t n, uint_fast8_t x, uint_fast8_t y, uint_fast8_t z)
//{
//	if (n) {
//		TowersOfHanoi(n - 1, x, z, y);
//		//std::cout << "Move top disk from tower " << x << "to top of tower " << y << std::endl;
//		//cout << "numSteps: " << numSteps;
//		TowersOfHanoi(n - 1, z, y, x);
//	}
//}
//
//int main()
//{
//	int n;
//	std::cout << "Enter n: ";
//	std::cin >> n;
//	for (int i = 1; i <= 32; i++)
//	{
//		auto start_time = std::chrono::high_resolution_clock::now();
//		TowersOfHanoi((int)i, 1, 2, 3);
//		auto end_time = std::chrono::high_resolution_clock::now();
//		std::cout << "Results for n = " << i << std::endl;
//		std::cout << "Seconds: " << std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() << std::endl;
//		std::cout << "Microseconds: " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << std::endl;
//		std::cout << "Done" << std::endl;
//	}
//
//	//cout << "NumSteps: " << numSteps << endl;
//	std::cin >> n; // Just to stop the program
//}
//int numMoves = 0;
using namespace std;
//void Hanoi4(int nDisks, char source, char intermed1, char intermed2, char dest)
//{
//	if (nDisks == 1)
//	{
//		cout << source << " --> " << dest << endl;
//		numMoves++;
//	}
//	else if (nDisks == 2)
//	{
//		cout << source << " --> " << intermed1 << endl;
//		numMoves++;
//		cout << source << " --> " << dest << endl;
//		numMoves++;
//		cout << intermed1 << " --> " << dest << endl;
//		numMoves++;
//	}
//	else
//	{
//		Hanoi4(nDisks - 2, source, intermed2, dest, intermed1);
//		cout << source << " --> " << intermed2 << endl;
//		numMoves++;
//		cout << source << " --> " << dest << endl;
//		numMoves++;
//		cout << intermed2 << " --> " << dest << endl;
//		numMoves++;
//		Hanoi4(nDisks - 2, intermed1, source, intermed2, dest);
//	}
//}
//
//int main()
//{
//	Hanoi4(4, 'A', 'B', 'C', 'D');
//	cout << "numMoves: " << numMoves << endl;
//
//	return 0;
//}

// the counter for the number of moves from the 
// start state 
int cnt = 0;
// the current minimum moves to the end state
int current_min = INT_MAX;
// a hash table to remember the visited states
hash_table ht;

void dfs()
{
	if (cnt >= current_min) return;
	// get the current state of disks   
	string stat = get_state()

		// if stat is not in hashtable
		if (!ht.has_key(stat))
		{
			ht[stat] = cnt;
		}
		else
		{
			// if we take more moves to 
			// visit this state, we just
			// return
			if (ht[stat] <= cnt) return;
			ht[stat] = cnt;
		}

	// if we reach the end state
	if (stat == end_state)
	{
		if (current_min > cnt)
			current_min = cnt;
		return;
	}

	for (int i = 0; i<K; i++)
	{
		current_disk = peg[i].top();
		// iterate all the possible moves
		// current_disk can make
		for move in possible_move_set
		{
			make the move;
		cnt++;
		dfs();
		rewind the move;
		cnt--;
		}
	}

}