/**
 *	Course:					CS 380
 *	Group:					Group 2 - Card Reader Application Group
 *	Group Members:			Dylan, John, William
 *	Description of Project:
 *		This is a card scanning program that accepts input in the form of card
 *		numbers. When a user scans his/her card, the program will record his/
 *		her attendance. If the program doesn't know who the user is, the user
 *		is prompted for his/her information.
 */

/**
 *	Header Block: PrintFile Implementation
 *	Module Name: 
 *		PrintFile Implementation
 *	Authors:
 *		Dylan, John, William
 *	Where it fits:
 *		See PrintFile.h header block
 *	When it was written, and revised:
 *		Continuous revision, and revisement (see github commit history)
 *	Why it exists:
 *		See Database.h header block
 *	How it uses datastructures, algorithms, and control:
 *		See Database.h header block
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "PrintFile.h"
#include "defines.h"

using namespace std;
	
void PrintFile::printToHumanFormatted(char ***data, int numberOfRows)
{
//	data[numberOfRows][3];
	ofstream students("studentsHRF.txt", ios::out); //file for students to be recorded to.
	
	int x = 0;
	students << left << setw(LENGTH_NAME) << "Name" << "|" << setw(LENGTH_MSU_ID + 3) << "ID Number" << "|" << setw(LENGTH_COURSES) << "Classes" << "\n";

	for(int i = 0; i < (LENGTH_NAME + (LENGTH_MSU_ID + 3) + LENGTH_COURSES + 2); i++)
	{
		students << "=";
	}
	students << endl;

	while (x != numberOfRows)//while not past the last row in the array.
	{
		students << left << setw(LENGTH_NAME) << data[x][0] << "|" << setw(LENGTH_MSU_ID+ 3) << data[x][1] << "|" << setw(LENGTH_COURSES) << data[x][2] << "\n";
		x++;
	}

	freeArray(data, numberOfRows);
	
	students.close()
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

	freeArray(data, numberOfRows);

	students.close();
}

void PrintFile::freeArray(char ***array, int numberOfRows)
{
	for(int i = 0; i < numberOfRows; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			delete array[i][j];
		}

		delete array[i];
	}

	delete array;

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