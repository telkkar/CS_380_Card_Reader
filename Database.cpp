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

#include <stdlib.h>
#include <string.h>

#include "sqlite3.h"
#include "Database.h"
#include "defines.h"

Database::Database()
{
	// Need to add error checking here
	// What if this doesn't open the DB?
	sqlite3_open("database.db", &db);
}

Database::~Database()
{
	sqlite3_close(db);
}

void Database::addMember(char* cardNumber, char* name, char* idNumber, char* courses)
{
	// Prepare sqlStatement
	char sqlStatement[28 +
	                  (LENGTH_CARD_NUMBER + 1) + 4 +
	                  (LENGTH_NAME + 1) + 4 +
	                  (LENGTH_MSU_ID + 1) + 4 +
	                  (LENGTH_COURSES + 1) + 2] = "";
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
	                  (LENGTH_CARD_NUMBER + 1) + 4 +
	                  (LENGTH_NAME + 1) + 4 +
	                  (LENGTH_MSU_ID + 1) + 4 +
	                  (LENGTH_COURSES + 1) + 2] = "";
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

	char sqlQuery[49 + (LENGTH_CARD_NUMBER + 1) + 1] = "SELECT cardNumber FROM Members WHERE cardNumber='";
	strcat(sqlQuery, cardNumber);
	strcat(sqlQuery, "'");

	// Prepare dbStatement
	sqlite3_prepare(db, sqlQuery, -1, &dbStatement, NULL);

	found_value = sqlite3_step(dbStatement);
	// sqlite3_step returns SQLITE_ROW if an entry was found, SQLITE_DONE if not found

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

	char sqlQuery[52 + (LENGTH_CARD_NUMBER + 1) + 1] = "SELECT cardNumber FROM Attendance WHERE cardNumber='";
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
	char sqlQuery[74 + (LENGTH_CARD_NUMBER + 1) + 1] = "SELECT cardNumber, name, idNumber, courses FROM Members WHERE cardNumber='";
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

void Database::editInformation(char* cardNumber, char* name, char* idNumber, char* courses)
{
	editMembers(cardNumber, name, idNumber, courses);
	editAttendance(cardNumber, name, idNumber, courses);
}

void Database::editAttendance(char* cardNumber, char* name, char* idNumber, char* courses)
{
	char sqlStatement[28 +
	                  (LENGTH_NAME + 1) + 13 +
	                  (LENGTH_MSU_ID + 1) + 12 +
	                  (LENGTH_COURSES + 1) + 20 +
					  (LENGTH_CARD_NUMBER + 1) + 1] = "";
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

void Database::editMembers(char* cardNumber, char* name, char* idNumber, char* courses)
{
	char sqlStatement[25 +
	                  (LENGTH_NAME + 1) + 13 +
	                  (LENGTH_MSU_ID + 1) + 12 +
	                  (LENGTH_COURSES + 1) + 20 +
					  (LENGTH_CARD_NUMBER + 1) + 1] = "";
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

int Database::getAttendanceCount()
{
	int count = 0;

	char sqlStatement[] = "SELECT COUNT(*) FROM Attendance";

	sqlite3_prepare(db, sqlStatement, -1, &dbStatement, NULL);
	sqlite3_step(dbStatement);
	
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

char*** Database::getAttendanceTable()
{
	int attendanceCount = getAttendanceCount();

	char ***data;
	data = new char**[attendanceCount];

	for(int i = 0; i < attendanceCount; i++)
	{
		data[i] = new char*[3]; 
	}

	char sqlStatement[] = "SELECT name, idNumber, courses FROM Attendance";

	sqlite3_prepare(db, sqlStatement, -1, &dbStatement, NULL);

	for(int i = 0; i < attendanceCount; i++)
	{
		sqlite3_step(dbStatement);
		char *returnText = NULL;
		
		returnText = new char[LENGTH_NAME];
		strcpy(returnText, (char *)sqlite3_column_text(dbStatement, 0));
		data[i][0] = returnText;

		returnText = new char[LENGTH_MSU_ID];
		strcpy(returnText, (char *)sqlite3_column_text(dbStatement, 1));
		data[i][1] = returnText;

		returnText = new char[LENGTH_COURSES];
		strcpy(returnText, (char *)sqlite3_column_text(dbStatement, 2));
		data[i][2] = returnText;
	}

	sqlite3_finalize(dbStatement);

	return data;
}