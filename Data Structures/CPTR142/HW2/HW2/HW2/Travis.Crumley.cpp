/*****************************************************************************
Program file name: Assignment #3 			OS: windows 8          		Assignment #: 3
Programmer: Travis Crumley 			Class: 	Data Structures II			Date: 1/24/2014
Compiler: Visual Studio 2013

Assistance/references: In class work posted on common drive (K:\common)
Description: A C++ Class for singly linked lists called ListSL

Inputs: Menu Selections and Data entered by user
Outputs: Data from nodes as well as commands or notifications

Special Comments:

~~~~~~~~~~~~~~~~~~~~~~~~~~Grading Criteria~~~~~~~~~~~~~~~~~~~~~~~~~~
Assignment Requirements ___/3.0
Code Format/Cosmetics ___/3.0
Header & Code Comments: ___/2.0
Output Format/Cosmetics ___/2.0

***Does Not Compile***: ___ (-10.0)
***Late Work Deduction***: ___ (-0.5/day)
Total Grade: ___/10.0

*****************************************************************************/

#include <iostream>
#include <string>
using namespace std;

class node
{
public:
	string data;
	node *link;
};

class ListSL
{
private:
	node *headptr;
	node *ptr;
public:

	ListSL();
	void writeList();
	void clearList();
	void searchList();
	void insertNode();
	void fillNode();
	void deleteNode();
};

ListSL::ListSL()
{
	headptr = NULL;
}

void ListSL::writeList()
{
	if (headptr == NULL)
	{
		cout << "The list is empty\n";
	}
	else
	{
		node *ptr = headptr;
		while (ptr != NULL)
		{
			cout << ptr->data << " ";
			ptr = ptr->link;
		}
	}
}

void ListSL::clearList() 
{
	if (headptr == NULL)
	{
		cout << "The list is empty\n";
	}
	else
	{
		ptr = headptr;
		node *delptr = headptr;
		while (ptr != NULL)
		{
			delptr->~node(); //Destroy node
			ptr = ptr->link; //Move to the next
			delptr = ptr;	 //Move to the next
		}
		cout << "List cleared\n";
	}
}

void ListSL::searchList() 
{
	bool isFound = 0;
	string data;
	int index = 0;
	if (headptr == NULL)
	{
		cout << "The list is empty\n";
	}
	else
	{
		cout << "Enter the data you wish to search for\n";
		getline(cin, data);
		ptr = headptr;
		while (ptr != NULL && isFound == 0)
		{
			if (ptr->data == data)
			{
				//At this point ptr is pointing to the node
				//do we want to return the node?
				isFound = 1;
			}
			else
			{
				ptr = ptr->link;
				index++;
			}
		}
		if (!isFound)
		{
			cout << "Node not found\n";
		}
		else
		{
			cout << "Node found at index " << index;
		}
	}	
}

void ListSL::insertNode()
{
	node *p, *q;
	if (headptr == NULL)
	{
		headptr = ptr;
	}
	else if (ptr->data < headptr->data)
	{
		ptr->link = headptr;
		headptr = ptr;
	}
	else
	{
		p = q = headptr;
		while ((p != NULL) && (p->data < ptr->data))
		{
			q = p;
			p = p->link;
		}
		ptr->link = p;
		q->link = ptr;
	}
}

void ListSL::fillNode()
{
	ptr = new node;
	cout << "Please type a name:  ";
	getline(cin, ptr->data);
	ptr->link = NULL;
}

void ListSL::deleteNode()
{
	string data;
	bool isFound = 0;
	int index = 0;
	if (headptr == NULL)
	{
		cout << "The list is empty\n";
	}
	else
	{
		cout << "Enter the data you wish to search for\n";
		cin >> data; 
		cin.ignore();
		ptr = headptr;
		while (ptr != NULL)
		{
			if (ptr->data == data)
			{
				//At this point ptr is pointing to the node
				//do we want to return the node?
				isFound = true;
				//Call the node's destructor
				ptr->~node();
				cout << "Node deleted at index " << index;
			}
			else
			{
				ptr = ptr->link;
				index++;
			}
		}
		if (!isFound)
		{
			cout << "Node not found\n";
		}
	}
}

int main()
{
	//Test harness
	ListSL list;
	char choice;
	while (true)
	{
		cout << "Main Menu\n Enter 1 to add a new node to list\n 2 to see the list\n 3 to delete a node\n 4 to clear list\n 5 to search list\n";
		cin >> choice;
		cin.ignore();
		switch (choice)
		{
		case '1':
			list.fillNode();
			list.insertNode();
			cout << endl;
			break;
		case '2':
			list.writeList();
			cout << endl;
			break;
		case '3':
			list.deleteNode();
			cout << endl;
			break;
		case '4':
			list.clearList();
			cout << endl;
			break;
		case '5':
			list.searchList();
			cout << endl;
			break;
		default:
			cout << "Command Not Recognized, Please Try Again\n";
			break;
		}
	}
	return 0;
}
