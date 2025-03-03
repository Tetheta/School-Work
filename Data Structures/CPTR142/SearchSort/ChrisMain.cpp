#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <ctime>
//Code by Travis Crumely March 2014

//Note! You must move the files charbits.txt and marbles.txt to
//your project folder from the CPTR Class searchData folder first

using namespace std;

inline void primeSearch(string key, string file, size_t result[], size_t pos, int a)
{
    pos = 0;
    while((pos = file.find(key, pos)) != std::string::npos)
    {
        //std::cout << "key found at position: " << pos << std::endl;
        result[a]=pos;
        a++;
        pos += key.size();
    }
}

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
    int keyInt[28];
    size_t result[40];
    for(int i=0; i<40; i++)
    {
        result[i]=0;
    }
    readFromSearchFile(keyInt,searchData);
    int a = 0;

    //For Chris Implementation:
    const std::string file =
        "101110111110111101100011001101110111000111100101100001111110100101100101010101010101111001001101110001111011001111110111111100111111001110011101100010011101100101100000010101101010011010010011010101001110111001101001110101000001001101010111111001001110111100010011101111010110100011011110110110010011010110000110001011010111110001000101000001100011011011110110101011000101000001111001100101001010010100111100011110101111011000010110100101101111111110100101111100000100000110111111011100000001010000100011011110011000010011011011010011110001001110110111001101011101110010010110110100001101101110010000010100000111010111010110110011010101010010111001000100001100111110000110000010111100011100111100100010101010010000001111001011100010010110111110100110110000011001000100010101010100111001011111100101110100100001010110000011001101111000010110010110001010110100001110001101111011100110101010011111111001110010000011011001011011011011000000111010100001001000000011000101100111010001000011000010110001011011101100100111000100011101010100011111100000100111011101100000110010111000010011000101111001101101000010001011100100110011001101001101111010111011000100101001000010011001011000100101101000101100111101011000111111000011011111110011101101100001100111111011000010000001001010000011010001010001100011000001101100100101100100100100111011000000001111101001100101011101110111110111101100011001000111100010001100001111000100111110100011011001010001010011011110010101010000000011000011011011100110101111100011000010010111001011101011011010110001011001110111000000100000111101101110111110111101100011001100100100111100100110101110000111100100110101100011011100100110011110010111011111011110110001100111011101111101111011000110011100100011100010001110111100010101001010010011001111111001110011100011111011111011010001110000111000010010111101001111011001001110000110111001011010011011000111000101111100110001000111111101000100101011101111101111011000110011001000010011111000110010110101111000000110111111011101110110001101010001101001011100";

    const std::string key = "1011101111101111011000110011";

    std::size_t pos = 0;
    t1=clock();
    for(long int i = 1; i<=1000000; i++)
    {
        //primeSearch(key, file, result, pos, a);
        //routine
        pos = 0;
        while((pos = file.find(key, pos)) != std::string::npos)
        {
            //std::cout << "key found at position: " << pos << std::endl;
            result[a]=pos;
            a++;
            pos += key.size();
        }
    }
    t2=clock();
    //output
    int j=0;
    while(result[j]!=0)
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
