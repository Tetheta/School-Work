//#include <iostream>
//#include <vector>
//using namespace std;
//
//vector<int> pegVector;
//int moves = 0;
//
//void move_top_disk(int source, int dest)
//{
//	cout << "Moving disk " << source << "to " << dest << endl;
//}
//
//void move(int number_of_disks, int source, int dest, vector<int> free_peg)
//{
//	int p, middle, g;
//
//	if (1 == number_of_disks)
//	{
//		moves++;
//		move_top_disk(source, dest);
//	}
//
//	else
//	{
//		moves++;
//
//		if (free_peg.size() >= 2)
//			p = number_of_disks / 2;
//		else
//			p = number_of_disks - 1;
//
//		//Move top "p" disks from peg 1 to peg i
//		middle = free_peg.back();
//		free_peg.pop_back();
//		free_peg.push_back(dest);
//		move(p, source, middle, free_peg);
//
//		//Move "n - p " disks from peg 1 to another peg
//		free_peg.pop_back();
//		move(number_of_disks - p, source, dest, free_peg);
//
//		//Move p from current peg to the final peg
//		free_peg.push_back(source);
//		move(p, middle, dest, free_peg);
//	}
//}
//
//int main()
//{
//	pegVector.push_back(1);
//	//pegVector.push_back(2);
//	move(3, 0, 2, pegVector);
//	cout << "Moves: " << moves << endl;
//}

#include <iostream>
#include <tuple>
#include <stack>
#include <vector>

std::stack<int> to132(std::stack<int> s) {
	int first = s.top();
	s.pop();
	int second = s.top();
	s.pop();
	int third = s.top();
	s.pop();

	s.push(second);
	s.push(third);
	s.push(first);

	return s;
}

std::stack<int> to12(std::stack<int> s) {
	int first = s.top();
	s.pop();
	int second = s.top();
	s.pop();

	s.pop();

	s.push(second);
	s.push(first);

	return s;
}

std::stack<int> to321(std::stack<int> s) {
	int first = s.top();
	s.pop();
	int second = s.top();
	s.pop();
	int third = s.top();
	s.pop();

	s.push(first);
	s.push(second);
	s.push(third);

	return s;
}

constexpr int kparam(int t, int size) {
	return (size <= 3) ? t - 1 : t / 2;
}

template<int T, int SIZE>
class Hanoi {
private:
	std::stack<int> pegs;

public:
	Hanoi(std::stack<int> v) : pegs(v) {}

	std::vector<std::tuple<int, int>> toString() {
		const int k = kparam(T, SIZE);

		Hanoi<k, SIZE> l{ to132(pegs) };
		auto left = l.toString();
		Hanoi<T - k, SIZE - 1> c{ to12(pegs) };
		auto center = c.toString();
		Hanoi<k, SIZE> r{ to321(pegs) };
		auto right = r.toString();

		left.insert(left.end(), center.begin(), center.end());
		left.insert(left.end(), right.begin(), right.end());

		return left;
	}
};

template<int SIZE>
class Hanoi<0, SIZE> {
private:
	std::stack<int> pegs;

public:
	Hanoi(std::stack<int> v) : pegs(v) {}

	std::vector<std::tuple<int, int>> toString() {
		std::vector<std::tuple<int, int>> res{};

		return res;
	}
};

template <int SIZE>
class Hanoi<1, SIZE> {
private:
	std::stack<int> pegs;

public:
	Hanoi(std::stack<int> v) : pegs(v) {}

	std::vector<std::tuple<int, int>> toString() {
		std::vector<std::tuple<int, int>> res{};

		auto first = pegs.top();
		pegs.pop();
		auto second = pegs.top();
		pegs.pop();

		res.push_back(std::make_tuple(first, second));

		return res;
	}
};

int main() {
	std::stack<int> p;
	p.push(7); //added
	p.push(6); //added
	p.push(5);
	p.push(4);
	p.push(3);
	p.push(2);
	p.push(1);

	//Hanoi<6, 5> hanoi{ p };
	Hanoi<6, 6> hanoi{ p };

	auto res = hanoi.toString();

	for (auto r : res) {
		std::cout << std::get<0>(r) << ", " << std::get<1>(r) << std::endl;
	}
}