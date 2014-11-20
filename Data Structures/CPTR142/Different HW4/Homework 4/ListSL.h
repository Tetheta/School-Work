/*Team of:
Greg
Chris
Blake
Travis
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

template <class T>
class node
{ public:
    T data;
    node<T> *link;
};

template <class T>
class ListSL
{ private:
    node<T> *headptr;
    node<T> *ptr;
    string saveLocation;
  public:
    ListSL(void);
    void fillNode(void);
    void insertNode(void);
    void deleteNode(void);
    void buildList(void);
    void writeList(void);
    void clearList(void);
    void saveListToFile(void);
    void loadListFromFile(void);
};
