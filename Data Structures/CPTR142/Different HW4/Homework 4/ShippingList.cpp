#include "ShippingList.h"

ShippingList::ShippingList()
{
}

bool ShippingList::operator<=(const ShippingList& shipList)
{
    if(lastName <= shipList.lastName)
        return true;
    else if(lastName == shipList.lastName)
    {
        if(firstName <= shipList.firstName)
            return true;
        else
            return false;
    }
    else
        return false;
}

string ShippingList::stop(void)
{
    return firstName;
}

ostream& operator<<(ostream& out, const ShippingList& shipList)
{
    return out << "Name: " << shipList.firstName << " "
           << shipList.lastName
           << "\n Address: " << shipList.address << endl
           << "City: " << shipList.city << endl
           << "State: " << shipList.state << endl
           << "Zip: " << shipList.zip << endl
           << "Item: " << shipList.item << endl
           << "Shipping Type: " << shipList.shippingType << endl;
}

istream& operator>>(istream& in, ShippingList& shipList)
{
    cout << "\nFirstName: ";
    in >> shipList.firstName;
    if(shipList.firstName == "#") //End of list symbol
    {
        return in;
    }
    cout << "Last name: ";
    in >> shipList.lastName;
    cout << "Address: ";
    in >> shipList.address;
    cout << "City: ";
    in >> shipList.city;
    cout << "State: ";
    in >> shipList.state;
    cout << "Zip: ";
    in >> shipList.zip;
    cout << "Item: ";
    in >> shipList.item;
    cout << "Shipping Type: ";
    in >> shipList.shippingType;
    cout << endl;
    return in;
}

ofstream& operator<<(ofstream& fout, const ShippingList& shipList)
{
    fout << endl << shipList.firstName;
    fout << endl << shipList.lastName;
    fout << endl << shipList.address;
    fout << endl << shipList.city;
    fout << endl << shipList.state;
    fout << endl << shipList.zip;
    fout << endl << shipList.item;
    fout << endl << shipList.shippingType;
    return fout;
}


ifstream& operator>>(ifstream& fin, ShippingList& shipList)
{
    getline(fin, shipList.firstName);
    getline(fin, shipList.lastName);
    getline(fin, shipList.address);
    getline(fin, shipList.city);
    getline(fin, shipList.state);
    getline(fin, shipList.zip);
    getline(fin, shipList.item);
    getline(fin, shipList.shippingType);
    return fin;
}
