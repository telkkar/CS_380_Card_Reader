
#include "PrintFile.h"
#include "defines.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;
	
void PrintFile::printToHumanFormatted(char ***data, int numberOfRows)
{
//	data[numberOfRows][3];
	ofstream students("studentsHRF.txt", ios::out); //file for students to be recorded to.
	
	int x = 0;
	students << left << setw(LENGTH_NAME) << "Name" << "|" << setw(LENGTH_MSU_ID + 3) << "ID Number" << "|" << setw(LENGTH_COURSES) << "Classes" << "\n";

	for(int i = 0; i < (LENGTH_NAME + LENGTH_MSU_ID + LENGTH_COURSES); i++)
	{
		students << "=";
	}
	students << endl;

	while (x != numberOfRows)//while not past the last row in the array.
	{
		students << left << setw(LENGTH_NAME) << data[x][0] << "|" << setw(LENGTH_MSU_ID+ 3) << data[x][1] << "|" << setw(LENGTH_COURSES) << data[x][2] << "\n";
		x++;
	}

	for(int i = 0; i < numberOfRows; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			delete data[i][j];
		}

		delete data[i];
	}

	delete data;
}

void PrintFile::printToCSV(char ***data, int numberOfRows)//I may need to format this some more...kinda hard to read in the CSV file
{
	ofstream students("studentsCSV.csv", ios::out); //CSV file for students to be recorded to.
	int x = 0;
	while (x != numberOfRows)//while not past the last row in the array.
	{
		students << left << "\"" << data[x][0] << "\",\"" << data[x][1] << "\",\"" << data[x][2] << "\"\n";
		x++;	
	}

	for(int i = 0; i < numberOfRows; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			delete data[i][j];
		}

		delete data[i];
	}

	delete data;
}









// FOR TESTING PURPOSES ONLY!!!!!

/*int main()
{
	string **data;
	int numberOfRows = 4;
	data = new string*[numberOfRows];

	for(int i = 0; i < 4; i++)
	{
		data[i] = new string[3]; 
		data[i][0] = "Number 1";
		data[i][1] = "00000001";
		data[i][2] = "NUM 001";
	}


	if(true)
	{
		printToHumanFormatted(data, 4);
		printToCSV(data, 4);
	}
	return 0;
}*/