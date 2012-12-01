
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "PrintFile.h"

using namespace std;
	
void printFile::printToHumanFormatted(char **data, int numberOfRows)
{
//	data[numberOfRows][3];
	ofstream students("studentsHRF.txt", ios::out); //file for students to be recorded to.
	
	int x = 0;
	students << setw(10) << "Name" << "|" << setw(10) << "ID Number" << "|" << setw(20) << "Classes" << "\n";
	while (x != numberOfRows)//while not past the last row in the array.
	{
		students << left << setw(10) << data[x][0] << "|" << setw(10) << data[x][1] << "|" << setw(20) << data[x][2] << "\n";
		x++;
	}
}

void printFile::printToCSV(char **data, int numberOfRows)//I may need to format this some more...kinda hard to read in the CSV file
{
	ofstream students("studentsCSV.txt", ios::out); //CSV file for students to be recorded to.
	int x = 0;
	while (x != numberOfRows)//while not past the last row in the array.
	{
		students << left << data[x][0] << "," << data[x][1] << "," << data[x][2] << "\n";
		x++;	
	}
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