#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "Database.h"
#include "defines.h"

using namespace std;

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

	char sqlQuery[50 + LENGTH_CARD_NUMBER + 1] = "SELECT cardNumber FROM Members WHERE cardNumber = ";
	//+ 1 for the null terminator on string length
	strcat(sqlQuery, cardNumber);

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

	char sqlQuery[53 + LENGTH_CARD_NUMBER + 1] = "SELECT cardNumber FROM Attendance WHERE cardNumber = ";
	//+ 1 for the null terminator on string length
	strcat(sqlQuery, cardNumber);

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
	bool found = false;

	// Prepare query
	sqlite3_prepare(db, "SELECT cardNumber, name, idNumber, courses FROM Members", -1, &dbStatement, NULL);

	// Find the person (we've already checked that they are a Member from the isMember function!)
	
	/*** NOTE ***
	 * Use the new code from the isMember functions to improve searching in this function
	 */


	while(found == false)
	{
		sqlite3_step(dbStatement);

		if(strcmp((char*)sqlite3_column_text(dbStatement, 0), cardNumber) == 0)
		{
			found = true;
		}
	}

	// Insert values we want into the strings we passed in
	strcat(name, (char*)sqlite3_column_text(dbStatement, 1));
	strcat(idNumber, (char*)sqlite3_column_text(dbStatement, 2));
	strcat(courses, (char*)sqlite3_column_text(dbStatement, 3));

	// Close statement
	sqlite3_finalize(dbStatement);

}
