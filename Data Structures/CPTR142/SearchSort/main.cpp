#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <ctime>
//Code by Travis Crumely March 2014

//Note! You must move the files charbits.txt and marbles.txt to
//your project folder from the CPTR Class searchData folder first

using namespace std;

inline void primeSearch(int key[], int searchData[], int result[], int a)
{
    a=0;
    for(int j=0; j<1972; j++)
    {
        if(searchData[j]==key[0])
            if(searchData[j+1]==key[1])
                if(searchData[j+2]==key[2])
                    if(searchData[j+3]==key[3])
                        if(searchData[j+4]==key[4])
                            if(searchData[j+5]==key[5])
                                if(searchData[j+6]==key[6])
                                    if(searchData[j+7]==key[7])
                                        if(searchData[j+8]==key[8])
                                            if(searchData[j+9]==key[9])
                                                if(searchData[j+10]==key[10])
                                                    if(searchData[j+11]==key[11])
                                                        if(searchData[j+12]==key[12])
                                                            if(searchData[j+13]==key[13])
                                                                if(searchData[j+14]==key[14])
                                                                    if(searchData[j+15]==key[15])
                                                                        if(searchData[j+16]==key[16])
                                                                            if(searchData[j+17]==key[17])
                                                                                if(searchData[j+18]==key[18])
                                                                                    if(searchData[j+19]==key[19])
                                                                                        if(searchData[j+20]==key[20])
                                                                                            if(searchData[j+21]==key[21])
                                                                                                if(searchData[j+22]==key[22])
                                                                                                    if(searchData[j+23]==key[23])
                                                                                                        if(searchData[j+24]==key[24])
                                                                                                            if(searchData[j+25]==key[25])
                                                                                                                if(searchData[j+26]==key[26])
                                                                                                                    if(searchData[j+27]==key[27])
                                                                                                                    {
                                                                                                                        result[a]=j;
                                                                                                                        a++;
                                                                                                                        j=j+27;
                                                                                                                    }


    }
}

//Not necessary anymore
void marbleSort(char searchData[], int searchDataSize, int low, int high, int p)
{
    p = -1;
    for (int i = 0; i < searchDataSize;)
    {
        if (searchData[i] == 'R') //Low case
        {
            swap(searchData[i], searchData[++p]);
            ++i;
        }
        else if (searchData[i] == 'B') //High case
        {
            swap(searchData[i], searchData[--searchDataSize]);
        }
        else
        {
            ++i;
        }
    }
}

void readFromSearchFile(int searchData1[], int searchData2[])
{
    ifstream myfile ("charbits.txt");
    if (myfile.is_open())
    {
        int i = 0;
        while ( myfile.good() && i<28)
        {
            searchData1[i] = myfile.get() - '0';
            i++;
        }
        i=i-28;
        while ( myfile.good() )
        {
            searchData2[i] = myfile.get() - '0';
            i++;
        }
        myfile.close();
    }

    else cout << "Unable to open file";
}

void readFromSortFile(char searchData[])
{
    ifstream myfile ("marbles.txt");
    if (myfile.is_open())
    {
        //cout << "Sort Open" << endl;
        int i = 0;
        while ( myfile.good() )
        {
            searchData[i] = myfile.get();
            i++;
        }
        myfile.close();
    }

    else cout << "Unable to open file";
}

int main()
{
    clock_t t1, t2;
    //Input initializations

    //Search
    cout << "Search Function" << endl;
    int searchData[2000];
    int key[28];
    int result[40];
    for(int i=0; i<40; i++)
    {
        result[i]=-1;
    }
    readFromSearchFile(key,searchData);
    int a = 0;
    t1=clock();
    for(long int i = 1; i<=1000000; i++)
    {
        primeSearch(key, searchData, result, a);
        //routine
    }
    t2=clock();
    //output
    int j=0;
    while(result[j]!=-1)
    {
        cout << "Match occurs starting at bit position " << result[j] << "\n";
        j++;
    }
    cout << "Time difference is " << (double)(t2-t1)/CLK_TCK << " " << " micro seconds." << endl;

    ////////////////////////////////////////////////////////////////////////////////
    //Sort
    cout << "Sort Function" << endl;
    char sortData[2000];
    readFromSortFile(sortData);
    int searchDataSize = 2000;
    int low = 0;
    int high = 2;
    int p;
    cout << "Starting Clock" << endl;
    t1=clock();
    for(long int i = 1; i<=1000000; i++)
    {
        //routine
        //marbleSort(sortData, searchDataSize, low, high, p);
        p = -1;
        for (int i = 0; i < searchDataSize;)
        {
            if (searchData[i] == 'R') //Low case
            {
                swap(searchData[i], searchData[++p]);
                ++i;
            }
            else if (searchData[i] == 'B') //High case
            {
                swap(searchData[i], searchData[--searchDataSize]);
            }
            else
            {
                ++i;
            }
        }
    }
    t2=clock();
    //output
    cout << "Time difference is " << (double)(t2-t1)/CLK_TCK << " " << " micro seconds." << endl;
}
