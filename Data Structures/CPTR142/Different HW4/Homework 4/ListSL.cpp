#include "ListSL.h"

template <class T>
ListSL<T>::ListSL(void)
{
    headptr = NULL;
    saveLocation = "savedList.txt";
}

template <class T>
void ListSL<T>::fillNode(void)
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
void ListSL<T>::insertNode(void)
{
    node<T> *p, *q;
    if(headptr == NULL)
        headptr = ptr;
    else if(ptr->data <= headptr->data)
    {
        ptr->link = headptr;
        headptr = ptr;
    }
    else
    {
        q = p = headptr;
        while((p!=NULL) && (p->data <= ptr->data))
        {
            q = p;
            p = p->link;
        }
        ptr->link = p;
        q->link = ptr;
    }
}

template <class T>
void ListSL<T>::deleteNode(void)
{
    node<T> *current, *first, *next;
    int akey;

    current = headptr;

    next = current->link;

    cout<<"Input Data You Would Like To Delete"<<endl;
    cin>>akey;

    while (current->data == akey)
    {

        delete current;
        // Update current for the while loop
        current = next;
        // update next too.
        next = current->link;
    }
    first = current;

    while(next != NULL)  // This should be enough
    {
        if(next->data == akey)
        {
            current->link = next->link;
            // delete the node.
            delete next;
            // Make the next pointer point to the new next.
            next = current->link;
        }
               // Otherwise advance both current and next.
               else
        {
            current = next;
            next = next->link;
        }
    }

// Use this to test it.
//    current = first;
//    while(current)
//    {
//        cout<<current->data<<", ";
//        current = current->ptr;
//    }
}

template <class T>
void ListSL<T>::buildList(void)
{
    string finish;
    cout << "Enter node data.\n"
         << "Hit # to quit.\n\n";
    do
    {
        fillNode();
        finish = ptr->data.stop();
        if(finish != "#") //End of list symbol
            insertNode();
    }
    while(finish != "#");
}

template <class T>
void ListSL<T>::writeList(void)
{
    if(headptr == NULL)
        cout << "\nList is Empty\n";
    else
    {
        ptr = headptr;
        while(ptr != NULL)
        {
            cout << ptr->data;
            ptr = ptr->link;
        }
    }
}

template <class T>
void ListSL<T>::clearList(void)
{
    ptr = headptr;
    while(headptr != NULL)
    {
        /*ptr-> = ""; define a method operator=
          in class Record that handles this. */
        headptr = headptr->link;
        ptr->link = NULL;
        delete ptr;
        ptr = headptr;
    }
}

template <class T>
void ListSL<T>::saveListToFile()
{
    node<T> *p;
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
void ListSL<T>::loadListFromFile()
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
