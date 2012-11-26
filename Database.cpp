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
 *	Header Block: Database Implementation
 *	Module Name: 
 *		Database Implementation
 *	Authors:
 *		Dylan, John, William
 *	Where it fits:
 *		See Database.h header block
 *	When it was written, and revised:
 *		Continuous revision, and revisement (see github commit history)
 *	Why it exists:
 *		See Database.h header block
 *	How it uses datastructures, algorithms, and control:
 *		See Database.h header block
 */

/**
 *	NOTES/TODO: 
 *	- Refactor some of the code in getMemberInfo()
 *
 */

#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "Database.h"
#include "defines.h"


Database::Database()
{
	// Need to add error checking here
	// What if this doesn't open the DB?
	sqlite3_open("database.db", &db);   // Open the database
}

Database::~Database()
{
	sqlite3_close(db);
}

void Database::addMember(char* cardNumber, char* name, char* idNumber, char* courses)
{
	// Prepare sqlStatement
	char sqlStatement[28 +
	                  LENGTH_CARD_NUMBER + 4 +
	                  LENGTH_NAME + 4 +
	                  LENGTH_MSU_ID + 4 +
	                  LENGTH_COURSES + 2] = "";
	strcat(sqlStatement, "INSERT INTO Members VALUES('");
	strcat(sqlStatement, cardNumber);
	strcat(sqlStatement, "', '");
	strcat(sqlStatement, name);
	strcat(sqlStatement, "', '");
	strcat(sqlStatement, idNumber);
	strcat(sqlStatement, "', '");
	strcat(sqlStatement, courses);
	strcat(sqlStatement, "')");

	// Use sqlStatement
	sqlite3_prepare(db, sqlStatement, -1, &dbStatement, NULL);
	sqlite3_step(dbStatement);

	// Close dbStatement
	sqlite3_finalize(dbStatement);
}

void Database::addAttendance(char* cardNumber, char* name, char* idNumber, char* courses)
{
	// Prepare sqlStatement
	char sqlStatement[31 +
	                  LENGTH_CARD_NUMBER + 4 +
	                  LENGTH_NAME + 4 +
	                  LENGTH_MSU_ID + 4 +
	                  LENGTH_COURSES + 2] = "";
	strcat(sqlStatement, "INSERT INTO Attendance VALUES('");
	strcat(sqlStatement, cardNumber);
	strcat(sqlStatement, "', '");
	strcat(sqlStatement, name);
	strcat(sqlStatement, "', '");
	strcat(sqlStatement, idNumber);
	strcat(sqlStatement, "', '");
	strcat(sqlStatement, courses);
	strcat(sqlStatement, "')");

	// Use sqlStatement
	sqlite3_prepare(db, sqlStatement, -1, &dbStatement, NULL);
	sqlite3_step(dbStatement);

	// Close dbStatement
	sqlite3_finalize(dbStatement);
}

bool Database::isMember(char* cardNumber)
{
	bool found = false;
	int found_value = 0;

	char sqlQuery[50 + LENGTH_CARD_NUMBER + 1] = "SELECT cardNumber FROM Members WHERE cardNumber='";
	//+ 1 for the null terminator on string length
	strcat(sqlQuery, cardNumber);
	strcat(sqlQuery, "'");

	// Prepare dbStatement
	sqlite3_prepare(db, sqlQuery, -1, &dbStatement, NULL);

	found_value = sqlite3_step(dbStatement);
	// sqlite3_step returns SQLITE_ROW if an entry was found, SQLITE_DONE if not found
	// SQLITE_ROW == 100, SQLITE_DONE = 101 (from defines on sqlite website.)

	if(found_value == SQLITE_ROW)
	{
		found = true;
	}
	else
	{
		found = false;
	}

	// Close dbStatement
	sqlite3_finalize(dbStatement);

	return found;
}

bool Database::isAttending(char* cardNumber)
{
	bool found = false;
	int found_value = 0;

	char sqlQuery[53 + LENGTH_CARD_NUMBER + 1] = "SELECT cardNumber FROM Attendance WHERE cardNumber='";
	//+ 1 for the null terminator on string length
	strcat(sqlQuery, cardNumber);
	strcat(sqlQuery, "'");

	// Prepare dbStatement
	sqlite3_prepare(db, sqlQuery, -1, &dbStatement, NULL);

	found_value = sqlite3_step(dbStatement);
	// sqlite3_step returns SQLITE_ROW if an entry was found, SQLITE_DONE if not found
	// SQLITE_ROW == 100, SQLITE_DONE = 101 (from defines on sqlite website.)

	if(found_value == SQLITE_ROW)
	{
		found = true;
	}
	else
	{
		found = false;
	}

	// Close dbStatement
	sqlite3_finalize(dbStatement);

	return found;
}

void Database::getMemberInfo(char* cardNumber, char* name, char* idNumber, char* courses)
{
	char sqlQuery[74 + LENGTH_CARD_NUMBER + 1] = "SELECT cardNumber, name, idNumber, courses FROM Members WHERE cardNumber='";
	//+ 1 for the '
	strcat(sqlQuery, cardNumber);
	strcat(sqlQuery, "'");

	// Prepare dbStatement
	sqlite3_prepare(db, sqlQuery, -1, &dbStatement, NULL);

	// Execute the statement
	sqlite3_step(dbStatement);

	// Insert values we want into the strings we passed in
	strcat(name, (char*)sqlite3_column_text(dbStatement, 1));
	strcat(idNumber, (char*)sqlite3_column_text(dbStatement, 2));
	strcat(courses, (char*)sqlite3_column_text(dbStatement, 3));

	// Close statement
	sqlite3_finalize(dbStatement);
}

//********************* NEW ***************
//*****************************************
void Database::editInformation(char* cardNumber, char* name, char* idNumber, char* courses)
{

	editMembers(cardNumber, name, idNumber, courses);
	editAttendance(cardNumber, name, idNumber, courses);
	
}

// 2 private /////////////////////

//editAttendance

void Database::editAttendance(char* cardNumber, char* name, char* idNumber, char* courses)
{
	char sqlStatement[28 +
	                  LENGTH_NAME + 13 +
	                  LENGTH_MSU_ID + 12 +
	                  LENGTH_COURSES + 20 +
					  LENGTH_CARD_NUMBER + 1] = "";
	strcat(sqlStatement, "UPDATE Attendance SET name='");
	strcat(sqlStatement, name);
	strcat(sqlStatement, "', idNumber='");
	strcat(sqlStatement, idNumber);
	strcat(sqlStatement, "', courses='");
	strcat(sqlStatement, courses);
	strcat(sqlStatement, "' WHERE cardNumber='");
	strcat(sqlStatement, cardNumber);
	strcat(sqlStatement, "'");



	sqlite3_prepare(db, sqlStatement, -1, &dbStatement, NULL);
	sqlite3_step(dbStatement);

	// Close dbStatement
	sqlite3_finalize(dbStatement);
}


//editMembers
void Database::editMembers(char* cardNumber, char* name, char* idNumber, char* courses)
{
	char sqlStatement[25 +
	                  LENGTH_NAME + 13 +
	                  LENGTH_MSU_ID + 12 +
	                  LENGTH_COURSES + 20 +
					  LENGTH_CARD_NUMBER + 1] = "";
	strcat(sqlStatement, "UPDATE Members SET name='");
	strcat(sqlStatement, name);
	strcat(sqlStatement, "', idNumber='");
	strcat(sqlStatement, idNumber);
	strcat(sqlStatement, "', courses='");
	strcat(sqlStatement, courses);
	strcat(sqlStatement, "' WHERE cardNumber='");
	strcat(sqlStatement, cardNumber);
	strcat(sqlStatement, "'");



	sqlite3_prepare(db, sqlStatement, -1, &dbStatement, NULL);
	sqlite3_step(dbStatement);

	// Close dbStatement
	sqlite3_finalize(dbStatement);
}

	/* NEW

	This method retrieves the total # of
	attendees from the Attendance table.

	*/

int Database::getAttendanceCount()
{
	int count = 0;

	char sqlStatement[] = "SELECT COUNT(*) FROM Attendance";

	sqlite3_prepare(db, sqlStatement, -1, &dbStatement, NULL);
	sqlite3_step(dbStatement);
	
	/* 
		Put return statements here *in progress*
		Returns int data type
	*/
	count = sqlite3_column_int(dbStatement, 0);
	sqlite3_finalize(dbStatement);

	return count;
}

void Database::clearAttendance()
{
	char sqlStatement[] = "DELETE FROM Attendance";

	sqlite3_prepare(db, sqlStatement, -1, &dbStatement, NULL);

	sqlite3_step(dbStatement);

	sqlite3_finalize(dbStatement);
}
