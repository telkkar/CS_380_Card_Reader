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
 *	Header Block: Database Module
 *	Module Name: 
 *		Database Module
 *	Authors:
 *		Dylan, John, William
 *	Where it fits:
 *		This module is the wrapper around the database that we use for
 *		information storage.
 *	When it was written, and revised:
 *		Continuous revision, and revisement (see github commit history)
 *	Why it exists:
 *		This is the module that handles the transactions with the database.
 *		If the GUI wants information, it interfaces with this class.
 *	How it uses datastructures, algorithms, and control:
 *		Everything is a bit messy, so everything is unpolished. See the state
 *		diagrams if you you want to know.
 */

/**
 *	NOTES/TODO: 
 *	- Missing some methods that are listed in the Class Diagram
 *
 */


#ifndef H_DATABASE
#define H_DATABASE

#include "sqlite3.h"

class Database
{
public:
	Database();
	~Database();
	void addAttendance(char* cardNumber, char* name, char* idNumber, char* courses);
	void addMember(char* cardNumber, char* name, char* idNumber, char* courses);
	bool isMember(char* cardNumber);
	bool isAttending(char* cardNumber);
	int getAttendanceCount(); // NEW
	void getMemberInfo(char* cardNumber, char* name, char* idNumber, char* courses);
	void editInformation(char* cardNumber, char* name, char* idNumber, char* courses);

private:
	sqlite3* db;
	sqlite3_stmt* dbStatement;
	void editMembers(char* cardNumber, char* name, char* idNumber, char* courses);
	void editAttendance(char* cardNumber, char* name, char* idNumber, char* courses);

};

#endif // H_DATABASE
