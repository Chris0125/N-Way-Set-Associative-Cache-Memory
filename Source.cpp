/**************************************************************
/ Christopher James
/ CMPS 5133 - Advanced Architecture                            
/ Project Assignment - 5 Way Set-Associative Cache Memory
**************************************************************/


#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#define MEM 10240
#define LINESIZE 32

using namespace std;

void PrintHeader();

string HexToBin(string address);

struct block{
	string line[5];
	bool flag[5];
	bool used[5];
};

int main()
{
	PrintHeader();
//	int in;
//	infile >> in;
	/*
	int offset = 0;
	cout << "Enter the size of a line: ";
	cin >> offset;
	cout << endl;
	*/

	const int memory = MEM / (5 * LINESIZE);
	//int set = 1;
	//int tag = 21;
	//int offset = 10;

	block cache[memory];
	for (int j = 0; j < memory; j++)
	{
		cache[j].flag[j] = false;
		cache[j].used[j] = false;
	}

	string address, code;
	int fifo[memory] = { 0 };
	int hit = 0;
	int miss = 0;
	int num = 0;


	ifstream infile;
	infile.open("input.txt");
	while (!infile.eof())
	{
		num++;
		infile >> code;
		if (code == "0" || code == "2")
		{
			infile >> address;
			string bin = HexToBin(address);
			int set = 0;
			int log = log2(memory);
			for (int j = 0; j < log; j++)
				set = (set* 2) + int(bin[21 + j]) - 48;
			string tag = "";
			
			//Strips out the tag that is supposed to go in a line
			for (int j = 0; j < 21; j++)
			{
				tag += bin[j];
			}
			bool setflag = false;
			for (int j = 0; j < 5; j++)
			{
				if ((cache[set].line[j] == tag))
					setflag = true;
			}

			//If the tag is not in any line for it's set,
			//if (!((cache[set].line[0] == tag) || (cache[set].line[1] == tag) || (cache[set].line[2] == tag) || (cache[set].line[3] == tag) || (cache[set].line[4] == tag)))
			if (!setflag)
			{
				if (!cache[set].flag[fifo[set]])
				{
					cache[set].used[fifo[set]] = true;
					cache[set].line[fifo[set]] = tag;
					fifo[set] = (fifo[set] + 1) % 5;
					miss++;
				}
				//We need to write back to main memory because a change occurred.
				else
				{
					//Writeback();
					cache[set].used[fifo[set]] = true;
					cache[set].line[fifo[set]] = tag;
					fifo[set] = (fifo[set] + 1) % 5;
					miss++;
				}
			}
			else
				hit++;
		}//end code 0
		
		else if (code == "1")
		{
			infile >> address;
			string bin = HexToBin(address);
			int set = 0;
			//
			for (int j = 0; j < (log2(memory)); j++)
				set = (set * 2) + int(bin[21 + j]) - 48;
			//
			string tag = "";

			//Strips out the tag that is supposed to go in a line
			for (int j = 0; j < 21; j++)
			{
				tag += bin[j];
			}

			//
			bool setflag = false;
			for (int j = 0; j < 5; j++)
			{
				if ((cache[set].line[j] == tag))
					setflag = true;
			}

			//If the tag is not in any line for it's set,
			//if (!((cache[set].line[0] == tag) || (cache[set].line[1] == tag) || (cache[set].line[2] == tag) || (cache[set].line[3] == tag) || (cache[set].line[4] == tag)))
			
			if (!setflag)
			{
				if (!cache[set].flag[fifo[set]])
				{
					cache[set].used[fifo[set]] = true;
					cache[set].flag[fifo[set]] = true;
					cache[set].line[fifo[set]] = tag;
					fifo[set] = (fifo[set] + 1) % 5;
					miss++;
				}
				//We need to write back to main memory because a change occurred.
				else
				{
					//Writeback();
					cache[set].flag[fifo[set]] = true;
					cache[set].used[fifo[set]] = true;
					cache[set].line[fifo[set]] = tag;
					fifo[set] = (fifo[set] + 1) % 5;
					miss++;
				}
			}
			else
				hit++;
		}//end code 1


	}


	cout << "Number of Hits: " << hit << endl;
	cout << "Number of misses: " << miss << endl;
	cout << hit+miss << " out of " << num << endl;

	infile.close();
	system("pause>0");
	return 0;
}


void PrintHeader()
{
	cout << "Christopher James" << endl << "CMPS 5133 - Advanced Architecture";
	cout << endl << "Project Assignment - 5 Way Set-Associative Cache Memory";
	cout << endl << endl;
}


string HexToBin(string hexaddr)
{
	int i = 0;
	int num = 0;
	string hex = "";
	while (hexaddr[i] != '\0')
	{
		if (hexaddr[i] == '0')
			hex += "0000";
		if (hexaddr[i] == '1')
			hex += "0001";
		if (hexaddr[i] == '2')
			hex += "0010";
		if (hexaddr[i] == '3')
			hex += "0011";
		if (hexaddr[i] == '4')
			hex += "0100"; 
		if (hexaddr[i] == '5')
			hex += "0101"; 
		if (hexaddr[i] == '6')
			hex += "0110"; 
		if (hexaddr[i] == '7')
			hex += "0111"; 
		if (hexaddr[i] == '8')
			hex += "1000";
		if (hexaddr[i] == '9')
			hex += "1001";
		if (hexaddr[i] == 'a')
			hex += "1010";
		if (hexaddr[i] == 'b')
			hex += "1011";
		if (hexaddr[i] == 'c')
			hex += "1100";
		if (hexaddr[i] == 'd')
			hex += "1101";
		if (hexaddr[i] == 'e')
			hex += "1110";
		if (hexaddr[i] == 'f')
			hex += "1111";
		i++;
	}
	while (i < 8)
	{
		hex = "0000" + hex;
		i++;
	}

	return hex;
}
