#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

class ShippingList
{
private:
    string firstName;
    string lastName;
    string address;
    string city;
    string state;
    string zip;
    string item;
    string shippingType;

public:
    ShippingList();
    bool operator<= (const ShippingList&);
    string stop();

    friend ostream& operator<<(ostream&, const ShippingList&);
    friend istream& operator>>(istream&, ShippingList&);

    friend ofstream& operator<<(ofstream&, const ShippingList&);
    friend ifstream& operator>>(ifstream&, ShippingList&);
};
