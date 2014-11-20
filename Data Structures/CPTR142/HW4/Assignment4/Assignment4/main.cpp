#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

class Record
{
private:
	string firstName;
	string lastName;
	string ssn;

public:
	Record();
	bool operator<= (const Record&);
	string stop();

	friend ostream& operator<<(ostream&, const Record&);
	friend istream& operator>>(istream&, Record&);

	friend ofstream& operator<<(ofstream&, const Record&);
	friend ifstream& operator>>(ifstream&, Record&);
};

Record::Record()
{
}

bool Record::operator<=(const Record& rec)
{
	if (lastName <= rec.lastName)
		return true;
	else
	if (lastName == rec.lastName)
	if (firstName <= rec.firstName)
		return true;
	else
		return false;
	else
		return false;
}

string Record::stop(void)
{
	return firstName;
}

ostream& operator<<(ostream& out, const Record& rec)
{
	return out << "name: " << rec.firstName << " "
		<< rec.lastName
		<< "\n ssn: " << rec.ssn << endl << endl;
}

istream& operator>>(istream& in, Record& rec)
{
	cout << "\nFirst name: ";
	in >> rec.firstName;
	if (rec.firstName == "#") //End of list symbol
	{
		return in;
	}
	cout << "Last name: ";
	in >> rec.lastName;
	cout << "Soc. Sec. No. ";
	in >> rec.ssn;
	cout << endl;
	return in;
}

ofstream& operator<<(ofstream& fout, const Record& rec)
{
	fout << endl << rec.firstName;
	fout << endl << rec.lastName;
	fout << endl << rec.ssn;
	return fout;
}


ifstream& operator>>(ifstream& fin, Record& rec)
{
	getline(fin, rec.firstName);
	getline(fin, rec.lastName);
	getline(fin, rec.ssn);
	return fin;
}


template <class T>
class node
{
public:
	T data;
	node<T> *link;
};

template <class T>
class List
{
private:
	node<T> *headptr;
	node<T> *ptr;
	string saveLocation;
public:
	List(void);
	void fillNode(void);
	void insertNode(void);
	void buildList(void);
	void writeList(void);
	void clearList(void);
	void saveListToFile(void);
	void loadListFromFile(void);
};

template <class T>
List<T>::List(void)
{
	headptr = NULL;
	saveLocation = "savedList.txt";
}

template <class T>
void List<T>::fillNode(void)
{
	static int i = 0;
	ptr = new node<T>;
	cout << "Enter Record " << ++i;
	//getline(cin, ptr->data);
	//overload getline to handle
	//input of type Record&
	cin >> ptr->data;
	ptr->link = NULL;
}

template <class T>
void List<T>::insertNode(void)
{
	node<T> *p, *q;
	if (headptr == NULL)
		headptr = ptr;
	else
	if (ptr->data <= headptr->data)
	{
		ptr->link = headptr;
		headptr = ptr;
	}
	else
	{
		q = p = headptr;
		while ((p != NULL) && (p->data <= ptr->data))
		{
			q = p;
			p = p->link;
		}
		ptr->link = p;
		q->link = ptr;
	}
}

template <class T>
void List<T>::buildList(void)
{
	string finish;
	cout << "Enter node data.\n"
		<< "Hit # to quit.\n\n";
	do{
		fillNode();
		finish = ptr->data.stop();
		cout << "finish = " << finish << endl;
		if (finish != "#") //End of list symbol
			insertNode();
	} while (finish != "#");
}

template <class T>
void List<T>::writeList(void)
{
	if (headptr == NULL)
		cout << "\nList is Empty\n";
	else
	{
		ptr = headptr;
		while (ptr != NULL)
		{
			cout << ptr->data;
			ptr = ptr->link;
		}
	}
}

template <class T>
void List<T>::clearList(void)
{
	ptr = headptr;
	while (headptr != NULL)
	{ /*ptr-> = ""; define a method operator=
	  in class Record that handles this. */
		headptr = headptr->link;
		ptr->link = NULL;
		delete ptr;
		ptr = headptr;
	}
}

template <class T>
void List<T>::saveListToFile()
{
	node<T> *p;
	string filename;
	cout << "Please enter a name for the file" << endl;
	cin >> saveLocation;
	saveLocation.append(".txt");
	ofstream fout;
	fout.open(saveLocation.c_str());
	if (!fout)
	{
		cerr << " Failure trying to create file: "
			<< saveLocation.c_str() << endl;
		exit(0);
	}
	p = headptr;
	while (p != NULL)
	{
		fout << p->data;
		p = p->link;
	}
	fout.close();
}

template <class T>
void List<T>::loadListFromFile()
{
	ifstream fin;
	cout << "Please enter the name of the file to load" << endl;
	cin >> saveLocation;
	saveLocation.append(".txt");
	fin.open(saveLocation.c_str());
	if (!fin)
	{
		cerr << " Failure trying to read file: "
			<< saveLocation.c_str() << endl;
		exit(0);
	}
	fin.ignore(1); //ignore the first endl
	while (!fin.eof())
	{
		ptr = new node<T>;
		fin >> ptr->data;
		ptr->link = NULL;
		insertNode();
	}
	fin.close();
}


char menu(void)
{
	char option;
	cout << "\nEnter an option:\n\n";
	cout << "1) Build a list.\n";
	cout << "2) Fill a node.\n";
	cout << "3) Insert a node.\n";
	cout << "4) Write the list.\n";
	cout << "5) Clear list.\n";
	cout << "6) Save list to a file.\n";
	cout << "7) Load list from a file.\n";
	cout << "8) Exit program.\n\n";
	cin >> option; getwchar(); //Delete Enter char.
	return option;
}

int main()
{
	List<Record> L1;
	char option = menu();
	while (option != 4)
	{
		switch (option)
		{
		case '1': L1.buildList(); break;
		case '2': L1.fillNode(); break;
		case '3': L1.insertNode(); break;
		case '4': L1.writeList(); break;
		case '5': L1.clearList(); break;
		case '6': L1.saveListToFile(); break;
		case '7': L1.loadListFromFile(); break;
		case '8': exit(0); break;
		default: cout << "\nERROR: Nothing for the option = " << option << "\n\n";
		}
		option = menu();
	}
	return 0;
}


