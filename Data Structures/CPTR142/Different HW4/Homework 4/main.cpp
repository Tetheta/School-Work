#include "ListSL.h"
#include "ShippingList.h"

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
    cin  >> option;
    getwchar(); //Delete Enter char.
    return option;
}

int main()
{
    ListSL<ShippingList> L1;
    char option = menu();
    while(option != '8')
    {
        switch(option)
        {
        case '1':
            L1.buildList()        ;
            break;
        case '2':
            L1.fillNode()         ;
            break;
        case '3':
            L1.insertNode()       ;
            break;
        case '4':
            L1.writeList()        ;
            break;
        case '5':
            L1.clearList()        ;
            break;
        case '6':
            L1.saveListToFile()   ;
            break;
        case '7':
            L1.loadListFromFile() ;
            break;
        case '8':
            exit(0)               ;
            break;
        default :
            cout << "\nERROR: Nothing for the option = " << option << "\n\n";
        }
        option = menu();
    }
    return 0;
}

