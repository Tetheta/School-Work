//Code written by Travis Crumley 3/12/15 for Computer Architecture.
//This code assembles a custom instruction set my team developed to 
//implement Booth's Multiplication Algorithm on a virtual processor
//It's input is a text file (assembly.txt) and it outputs a 
//.coe file (machine.coe) that Xilinx can read into ROM and feed
//to our VHDL code
//Other project team members: Dane Purkeypile and Greg Salsbery

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <bitset>

using namespace std;

//Input is assembly code
//Output is binary, in 16 bit
//Op code 3 bits, then 3 registers of 3 bits (unless immediate, then 2 registers and the rest is a number)

//Register 0 is Z and always contains zero, 1 is A, 2 is B and so forth

string binaryToNegative(string token)
{
	cout << "binaryToNegative: " << token << endl;
	//First need to get it to 7 bits
	cout << "token.size: " << token.size() << endl;
	while (token.size() < 7)
	{
		token.insert(0, "0");
	}
	//Need to flip all the bits and add one
	for (size_t i = 0; i < token.size(); i++)
	{
		cout << "token[" << i << "]: " << token[i] << endl;
		if (token[i] == '0')
		{
			token[i] = '1';
		}
		else
		{
			token[i] = '0';
		}
	}
	//Here we "add one" which actually means checking for the LSB that's 0, then setting it to 1 and everything after to 0
	//The case of all 1's is handled afterwards
	cout << "Inverted token: " << token << endl;
	for (size_t i = token.size() - 1; i >= 0; i--) //Start at the end of the string and move backwards
	{
		if (token[i] == '0')
		{
			//Sweet, we found the LSB 0, now change it to a 1 then break
			token[i] = '1';
			cout << "Should break now \n";
			break;
		}
		else if (i == 0)
		{
			//Came to the end of the string, it was all 1's so let's keep this as a 1 -- break!
			cout << "Ended now \n";
			break;
		}
		else
		{
			token[i] = '0'; //Haven't found the LSB 0 yet, so this will swap to a zero
			cout << "Else statement \n";
		}
	}
	//At this point, the string should've been changed to negative, can just return the token now
	cout << "Result: " << token << endl;
	return token;
}

string numbersToBinary(string token)
{
	cout << "Entered numbers to binary\n";
	cout << "token length: " << token.length() << endl;
	int tokenNum = 0;
	cout << "token[0]: " << token[0] << endl;
	if (token[0] == '-')
	{
		cout << "Negative\n";
		//It's a negative number, will need to do some special stuff
		tokenNum = 1;
		cout << token << endl;
		token.erase(token.begin());
		cout << token << endl;
	}
	if (token[0] == 'b') //It's already binary, just return the string!
	{
		token.erase(token.begin());
		cout << "token: " << token << endl;
		if (tokenNum > 0)
		{
			return binaryToNegative(token);
		}
		else
		{
			return token;
		}
	}
	else if (token[0] == 'h') //It's hexadecimal
	{
		string answer;
		token.erase(token.begin());
		cout << "token: " << token << endl;
		for (int i = token.length() - 1; i >= 0; i--)
		{
			switch (toupper(token[i]))
			{
			case '0': answer.append("0000");
			case '1': answer.append("0001");
			case '2': answer.append("0010");
			case '3': answer.append("0011");
			case '4': answer.append("0100");
			case '5': answer.append("0101");
			case '6': answer.append("0110");
			case '7': answer.append("0111");
			case '8': answer.append("1000");
			case '9': answer.append("1001");
			case 'A': answer.append("1010");
			case 'B': answer.append("1011");
			case 'C': answer.append("1100");
			case 'D': answer.append("1101");
			case 'E': answer.append("1110");
			case 'F': answer.append("1111");
			default: cout << "Error converting hex\n"; return NULL;
			}
		}
		cout << "answer: " << answer << endl;
		if (tokenNum > 0)
		{
			return binaryToNegative(answer); //Need the negative, so call this
		}
		return answer;
	}
	else //It's decimal
	{
		string answer;
		cout << "Converting decimal to binary: " << token << endl;
		int value = stoi(token);
		cout << "Decimal: " << value << endl;
		while (value != 0)
		{
			answer = (value % 2 == 0 ? "0" : "1") + answer;
			value /= 2;
		}
		cout << "Answer: " << answer << endl;
		if (tokenNum > 0)
		{
			return binaryToNegative(answer);
		}
		return answer;
	}
}

int main()
{
	ifstream assembly;
	ofstream machine;

	assembly.open("assembly.txt", ios::in);
	if (!assembly.is_open())
	{
		cout << "txt file load error\n";
		return 0;
	}
	machine.open("machine.coe", ios::out);
	if (!machine.is_open())
	{
		cout << "coe load error\n";
		return 0;
	}

	string line; //The line we're parsing
	string token; //Our current token
	bool isFirst = true; //It's the first on the line, so it's the op code
	bool isImmediate = true;
	int instrSize = 0; //Keep track of the instruction size
	int instrMax = 16;

	machine << "memory_initialization_radix=2;\nmemory_initialization_vector =\n";

	while (getline(assembly, line))
	{
		for (size_t i = 0; i < line.length(); i++)
		{
			cout << line[i] << endl; //Testing
			if (line[i] == ' ' || line[i] == ',' || line[i] == '\n')
			{
				cout << "token: " << token << endl;
				//Got a token, now process it
				//Processing for op code, will need a way to tell if it's the first on the line or not
				//Processing immediates
				if (isFirst)
				{
					cout << "Entered first\n";
					//Reset the flags
					isImmediate = true;

					if (token == "addi")
					{
						machine << "000";
					}
					else if (token == "andi")
					{
						machine << "001";
					}
					else if (token == "sll")
					{
						machine << "010";
					}
					else if (token == "sra")
					{
						machine << "011";
					}
					else if (token == "beq")
					{
						machine << "100";
					}
					//Done processing immediates, now for registers. They have highest bit as 1
					else if (token == "add")
					{
						machine << "101";
						isImmediate = false;
					}
					else if (token == "inv")
					{
						machine << "110";
						isImmediate = false;
					}
					else
					{
						cout << "Error, unrecognized op code\n";
						break;
					}
					isFirst = false;
					instrSize += 3;
					cout << "isImmediate: " << isImmediate << endl;
				}
				else
				{
					cout << "Not first\n";
					//It's an argument, parse the registers now
					cout << "instrSize: " << instrSize << endl;
					if (instrSize < 10)
					{
						cout << "Entered first two registers parse\n";
						if (token == "Z" || token == "z")
						{
							machine << "000";
						}
						else if (token == "A" || token == "a")
						{
							machine << "001";
						}
						else if (token == "B" || token == "b")
						{
							machine << "010";
						}
						else if (token == "C" || token == "c")
						{
							machine << "011";
						}
						else if (token == "D" || token == "d")
						{
							machine << "100";
						}
						else if (token == "E" || token == "e")
						{
							machine << "101";
						}
						else if (token == "F" || token == "f")
						{
							machine << "110";
						}
						//111 is the PC
						else
						{
							cout << "Error parsing first two registers\n";
						}
						instrSize += 3;
					}
				}
				token = ""; //Null the string
			}
			else
			{
				token += line[i]; //If not a delimiter, add it to our string
			}
		} //End processing that line

		//It's the last command, process either immediate or register
		if (isImmediate)
		{
			cout << "Entered immediate\n";
			string immediate = numbersToBinary(token);
			cout << "immediate: " << immediate << endl;
			instrSize += immediate.length();
			while (instrSize < instrMax) //Fill non-filled bits with zeroes
			{
				machine << "0";
				instrSize++;
			}
			machine << immediate; //Now add the immediate value
		}
		else //isRegister
		{
			cout << "Entered register last parse\n";
			if (token == "Z" || token == "z")
			{
				machine << "000";
			}
			else if (token == "A" || token == "a")
			{
				machine << "001";
			}
			else if (token == "B" || token == "b")
			{
				machine << "010";
			}
			else if (token == "C" || token == "c")
			{
				machine << "011";
			}
			else if (token == "D" || token == "d")
			{
				machine << "100";
			}
			else if (token == "E" || token == "e")
			{
				machine << "101";
			}
			else if (token == "F" || token == "f")
			{
				machine << "110";
			}
			//111 is the PC
			else
			{
				cout << "Error parsing last register\n";
			}
			instrSize += 3;
			while (instrSize < instrMax) //Fill non-filled bits with zeroes
			{
				machine << "0";
				instrSize++;
			}
		}
		token = ""; //Null the string
		cout << "End of line\n";
		machine << ",\n";
		instrSize = 0;
		isFirst = true;
	}
	long pos = machine.tellp(); //Get position of output
	machine.seekp(pos - 3); //Go back so we can replace comma
	machine << ";"; //Close off the format with semicolon
	assembly.close();
	machine.close();


	//For testing
	// int x;
	// std::cin >> x;
}