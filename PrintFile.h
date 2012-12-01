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
 *	Header Block: PrintFile Header
 *	Module Name: 
 *		PrintFile Module
 *	Authors:
 *		Dylan, John, William
 *	Where it fits:
 *		This module is the class that houses the methods that write the
 *		the attendance array (from the Attendance table in the database)
 *		to files.
 *	When it was written, and revised:
 *		Continuous revision, and revisement (see github commit history)
 *	Why it exists:
 *		This is the module that handles printing information to files.
 *		This is so we can keep records of attendance throughout the use
 *		of this program.
 *	How it uses datastructures, algorithms, and control:
 *		Everything is a bit messy, so everything is unpolished. See the state
 *		diagrams if you you want to know.
 */

class PrintFile
{
public:
	void printToHumanFormatted(char***, int);
	void printToCSV(char***, int);

};