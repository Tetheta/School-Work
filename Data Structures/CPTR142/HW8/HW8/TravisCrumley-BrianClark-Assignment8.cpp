/*
Program file name : Assignment #8 			OS: Windows 8          		Assignment # : 8
Programmer : Travis Crumley 			Class : Data Structures II			Date : 2 / 26 / 2014
Compiler : Visual Studio 2013

Assistance / references : In class work posted on common drive(K : \common)
Description : A C++ Class for singly linked lists called ListSL

Inputs : Menu Selections and Data entered by user
Outputs : Data from nodes as well as commands or notifications

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

#include <iostream>
#include <cstdlib>

using namespace std;


//Assisting classes:
//Stack
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
	void push(T*);
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
void Stack<T>::push(T* data)
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

//Queue:
template<class T>
class Queue
{
private:
	T* Q;
	int size;
	int front;
	int rear;
public:
	Queue(int = 10);
	bool emptyQ();
	bool fullQ();
	void addQ(T);
	void addQ(T*);
	T delQ();
	int lengthQ();
	void writeQ();
	void clrQ();
};

template<class T>
Queue<T>::Queue(int setSize)
{
	size = setSize;
	Q = new T[size];
	front = rear = 0;
}

template<class T>
bool Queue<T>::emptyQ()
{
	return front == rear;
}

template<class T>
bool Queue<T>::fullQ()
{
	return front == (rear + 1) % size;
}

template<class T>
void Queue<T>::addQ(T data)
{
	if (fullQ())
		cout << " Queue is full. \n";
	else
	{
		rear = (rear + 1) % size;
		Q[rear] = data;
	}
}

template<class T>
void Queue<T>::addQ(T* data)
{
	if (fullQ())
		cout << " Queue is full. \n";
	else
	{
		rear = (rear + 1) % size;
		Q[rear] = data;
	}
}

template<class T>
T Queue<T>::delQ()
{
	if (emptyQ())
	{
		cout << "Queue is empty.\n";
		return Q[0];
	}
	front = (front + 1) % size; // eqv. front++; front %= size;
	return Q[front];
}

template<class T>
int Queue<T>::lengthQ()
{
	return (rear - front + size) % size;
}

template<class T>
void Queue<T>::writeQ()
{

	cout << "Queue:  ";
	for (int i = 0; i < size; i++)
	{
		//The following is logic for determining if the data in the element
		//is still relevant to us (aka in our queue)
		if ((i > front && i <= rear) || (i < front && i <= rear && rear < front) || (i > front && front > rear))
		{
			cout << Q[i] << " ";
		}
		else
			cout << "@ ";
	}

	cout << endl;

}

template<class T>
void Queue<T>::clrQ()
{
	front = rear = 0;
}
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
//Need to create a node class to handle our nodes with two links
template <class T>
class node
{
public:
	T data;
	int tag;
	node *Lson, *Rson;
};

template <class T>
//Create the actual tree class
class Binsrchtree
{
private:
	//Calling one node Tree instead of T because I'm trying to use templates
	node<T> *Tree, *ptr, *ptr1, *ptr2;
	Stack<node<T>*> stk;
	Queue<node<T>*> queue;
public:
	Binsrchtree(void);
	bool isEmpty();
	void insert(T);
	void insert(T, string);
	bool findData(T);
	void del(T);
	void inOrder();
	void inOrder(node<T>*);
	void postOrder();
	void levelOrder();
	void clear();
	void clear(node<T>*);
};


template <class T>
Binsrchtree<T>::Binsrchtree()
{
	Tree = ptr = ptr1 = ptr2 = NULL;
}

template <class T>
void Binsrchtree<T>::inOrder() {
	cout << "In-Order:" << endl;
	inOrder(Tree);
	cout << endl;
}

template <class T>
void Binsrchtree<T>::inOrder(node<T>* curPtr) {
	if (curPtr != NULL)
	{
		inOrder(curPtr->Lson);
		cout << curPtr->data << " ";
		inOrder(curPtr->Rson);
	}
}

template <class T>
void Binsrchtree<T>::postOrder() {
	cout << "Post-Order" << endl;
	if (!isEmpty())
	{


		ptr = Tree;
		ptr->tag = 1;
		stk.push(ptr);
		while (!stk.empty())
		{
			ptr = stk.pop();
			switch (ptr->tag)
			{
			case 1:
				ptr->tag = 2;
				stk.push(ptr);
				if (ptr->Lson != NULL)
				{
					ptr->Lson->tag = 1;
					stk.push(ptr->Lson);
				}
				break;
			case 2:
				ptr->tag = 3;
				stk.push(ptr);
				if (ptr->Rson != NULL)
				{
					ptr->Rson->tag = 1;
					stk.push(ptr->Rson);
				}
				break;
			case 3:
				cout << ptr->data << " ";
				break;
			default:
				cout << "Default Selected" << endl;
			}
		}
		cout << endl;
	}
	else
	{
		cout << "Empty List" << endl;
	}
}

template <class T>
void Binsrchtree<T>::levelOrder() {
	cout << "Level-Order" << endl;
	ptr = Tree;
	if (ptr != NULL)
	{
		queue.clrQ();
		queue.addQ(ptr);
		while (!queue.emptyQ())
		{
			ptr = queue.delQ();
			cout << ptr->data << " ";
			if (ptr->Lson != NULL)
			{
				queue.addQ(ptr->Lson);
			}
			if (ptr->Rson != NULL)
			{
				queue.addQ(ptr->Rson);
			}
		}
	}
	else {
		cout << "Empty Tree" << endl;
	}
}

template <class T>
bool Binsrchtree<T>::isEmpty() {
	if (Tree == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}


template <class T>
void Binsrchtree<T>::insert(T dataItem, string relation)
{
	if (findData(dataItem) == false)
	{
		//Filling the node
		ptr = new node<T>;
		ptr->data = dataItem;
		ptr->Lson = NULL;
		ptr->Rson = NULL;
		//Inserting the node
		if (isEmpty())
		{
			Tree = ptr1 = ptr2 = ptr;
		}
		else
		{
			if (dataItem < ptr1->data)
			{
				ptr1->Lson = ptr;
			}
			else
			{
				ptr1->Rson = ptr;
			}
			if (relation == "Lson")
			{
				ptr->Lson = ptr2;
			}
			else
			{
				ptr->Rson = ptr2;
			}
		}
	}

}

template <class T>
void Binsrchtree<T>::insert(T dataItem)
{
	//No specification for son type
	if (findData(dataItem) == false)
	{
		//Filling the node
		ptr = new node<T>;
		ptr->data = dataItem;
		ptr->Lson = NULL;
		ptr->Rson = NULL;
		//Inserting the node
		if (isEmpty())
		{
			Tree = ptr1 = ptr2 = ptr;
		}
		else
		{
			if (dataItem < ptr1->data)
			{
				ptr1->Lson = ptr;
			}
			else
			{
				ptr1->Rson = ptr;
			}
		}
	}
}

template <class T>
void Binsrchtree<T>::del(T dataItem)
{
	if (!isEmpty())
	{
		if (findData(dataItem) == false)
		{
			cout << "Data not found" << endl;
		}
		else //Case 1: Leaf node
		{
			if (ptr2->Lson == NULL && ptr2->Rson == NULL)
			{
				if (ptr1->Lson == ptr2)
				{
					ptr1->Lson = NULL;
				}
				else
				{
					ptr1->Rson = NULL;
				}
				cout << "Case 1 pointer to be deleted" << endl;
				//node<T> *trashPtr;
				//trashPtr = ptr2;
				//ptr2 = Tree;
				//delete trashPtr;
				delete ptr2;
			}
			else //Case 2: A node with 1 son
			{
				if (ptr2->Lson == NULL || ptr2->Rson == NULL)
				{
					if (ptr1->Lson == ptr2)
					{
						if (ptr2->Lson == NULL)
						{
							ptr1->Lson = ptr2->Rson;
						}
						else
						{
							ptr1->Lson = ptr2->Lson;
						}
					}
					else
					{
						if (ptr2->Lson == NULL)
						{
							ptr1->Rson = ptr2->Rson;
						}
						else
						{
							ptr1->Rson = ptr2->Lson;
						}
					}
					cout << "Case 2 pointer to be deleted" << endl;
					//node<T> *trashPtr;
					//trashPtr = ptr2;
					//ptr2 = Tree;
					//delete trashPtr;
					cout << "Ptr 2 Data %i" << ptr2->data << endl;
					delete ptr2;
					cout << "Pointer 2 Deleted" << endl;
				}
				else //Case 3: A node with 2 sons
				{
					cout << "Case 3 Start" << endl;
					node<T> *r = ptr2->Rson;
					if (r->Lson == NULL)
					{
						ptr2->data = r->data;
						ptr2->Rson = r->Rson;
						cout << "Ptr 2 Data %i" << ptr2->data << endl;
						delete r;
					}
					else
					{
						node<T> *q;
						do
						{
							q = r;
							r = r->Lson;
						} while (r->Lson != NULL);
						ptr2->data = r->data;
						q->Lson = r->Rson;
						delete r;
					}
				}
			}
		}
		cout << "Del function worked" << endl;
	}
	else
	{
		cout << "Empty List" << endl;
	}
}

template <class T>
bool Binsrchtree<T>::findData(T dataItem)
{
	if (!isEmpty())
	{
		ptr1 = Tree;
		ptr2 = Tree;
		cout << "Ptr 2 Data %i" << ptr2->data << endl;
		while (ptr2 != NULL)
		{
			if (dataItem < ptr2->data)
			{
				cout << "find1";
				ptr1 = ptr2;
				ptr2 = ptr2->Lson;
			}
			else
			{
				if (dataItem > ptr2->data)
				{
					cout << "find2";
					ptr1 = ptr2;
					ptr2 = ptr2->Rson;
					cout << "find2Fin";
				}
				else
				{
					cout << "find3";
					//cout << "Data Found: " << ptr2->data << endl;
					return true;
				}
			}
		}
		cout << "find4";
		//cout << "Data not found" << endl;
		return false;
	}
	else
	{
		cout << "List is Empty" << endl;
		return false;
	}
}

template <class T>
void Binsrchtree<T>::clear()
{
	clear(Tree);
}

template <class T>
void Binsrchtree<T>::clear(node<T>* curPtr)
{
	if (ptr != NULL)
	{
		clear(ptr->Lson);
		clear(ptr->Rson);
		delete ptr;
	}
	Tree = ptr = NULL;
}

int main()
{
	char stop;

	Binsrchtree<int> srchtree;
	srchtree.insert(1);
	srchtree.insert(2);
	srchtree.insert(2);
	srchtree.insert(3);
	srchtree.insert(6);
	srchtree.insert(5);
	srchtree.insert(4);
	srchtree.inOrder();
	srchtree.postOrder();
	srchtree.levelOrder();
	cout << "First Insertion Over" << endl;
	srchtree.del(1);
	cout << "Del1";
	//srchtree.del(2);
	cout << "Del2";
	srchtree.del(6);
	cout << "Deletions Done" << endl;
	srchtree.inOrder();
	srchtree.postOrder();
	srchtree.levelOrder();
	srchtree.clear();
	cout << "Cleared" << endl;
	srchtree.inOrder();
	cin >> stop;


	cin >> stop;

	return 0;
}
