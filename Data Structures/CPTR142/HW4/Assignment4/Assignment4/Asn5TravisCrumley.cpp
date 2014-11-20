#include <iostream>
#include <cstdlib>

using namespace std;

template <class T>
class Stack
{
private:
	T *stk;
	int top, size;
public:
	Stack(void);
	Stack(int);
	bool empty();
	bool full();
	void push(T);
	T pop();
	void writeStack();

};

template <class T>
Stack<T>::Stack(void)
{
	size = 10;
	stk = new T[size];
	top = -1;
}

template <class T>
Stack<T>::Stack(int setSize)
{
	size = setSize;
	stk = new T[size];
	top = -1;
}

template <class T>
bool Stack<T>::empty() {
	if (top < 0)
		return true;
	else
		return false;
}

template <class T>
bool Stack<T>::full()
{
	if (top >= size - 1)
		return true;
	else
		return false;
}
template <class T>
void Stack<T>::push(T data)
{
	if (!full())
		stk[++top] = data;
	else
		cout << "Stack is full\n";
}

template <class T>
T Stack<T>::pop()
{
	static T nothing;
	if (empty())
	{
		cout << "Stack underflow\n";
		return nothing;
	}
	else
		return stk[top--];
}

template <class T>
void Stack<T>::writeStack()
{
	int i = top;
	if (i == -1) cout << "Stack is empty\n";
	else
	while (i >= 0) cout << stk[i--] << endl;
}

class StkEval
{
private:
	string expr, token;

public:
	StkEval(void);
	string nextToken();
	int eval(string);
};

StkEval::StkEval(void)
{
	expr = token = "";
}

string StkEval::nextToken()
{
	if (expr == "")
		return "";
	else
	{
		int n = expr.find(',', 0); //find first comma
		token = expr.substr(0, n); //get the first n characters
		expr.erase(0, n + 1); // erase the first n+1 characters
		return token;
	}
}

int StkEval::eval(string expression)
{
	Stack<int> s(10);
	expr = expression;
	token = nextToken();
	while (token != "")
	{
		if (isdigit(token[0]))
			s.push(atoi(token.c_str()));
		else
		{
			int temp2 = s.pop();
			int temp1 = s.pop();
			switch (token[0])
			{
			case '-': s.push(temp1 - temp2); break;
			case '+': s.push(temp1 + temp2); break;
			case '*': s.push(temp1*temp2); break;
			case '/': if (temp2 != 0)
			{
						  s.push(temp1 / temp2);
						  break;
			}
					  else
					  {
						  cout << "Cannot divide by zero!\n";
						  s.push(101);
						  break; //Whatever you want to push.
					  }
			default: cout << "Invalid Operator." << endl;
			}
		}
		token = nextToken();
	}
	return s.pop();
}

int main()
{ 
	StkEval rpn;
	string expr[] = { "60,3,*,", "19,9,/,", "25,134,+,", "3,1,-,", "7,0,/,", "22,31,*,9,/,", "9,7,/,5,-,2,3,*,+,9,6,*,-,"};
	for (int i = 0; i < 7; i++)
	{
		cout << rpn.eval(expr[i]) << endl;
	}

	char stop;
	cin >> stop;

	return 0;
}
