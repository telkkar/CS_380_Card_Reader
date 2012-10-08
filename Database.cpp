#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "Database.h"

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

void Database::addMember(char* idNumber, char* name)  // Get parameters later
{
    // Prepare sqlStatement
    char sqlStatement[256] = "";
    strcat(sqlStatement, "insert into Members values(");
    strcat(sqlStatement, idNumber);
    strcat(sqlStatement, ", '");
    strcat(sqlStatement, name);
    strcat(sqlStatement, "')");

    // Use sqlStatement
    sqlite3_prepare(db, sqlStatement, -1, &dbStatement, NULL);
    sqlite3_step(dbStatement);

    // Close dbStatement
    sqlite3_finalize(dbStatement);
}

void Database::addAttendance(char* idNumber, char* name) // Get parameters later
{
    // Prepare sqlStatement
    char sqlStatement[256] = "";
    strcat(sqlStatement, "insert into Attendance values(");
    strcat(sqlStatement, idNumber);
    strcat(sqlStatement, ", '");
    strcat(sqlStatement, name);
    strcat(sqlStatement, "')");

    // Use sqlStatement
    sqlite3_prepare(db, sqlStatement, -1, &dbStatement, NULL);
    sqlite3_step(dbStatement);

    // Close dbStatement
    sqlite3_finalize(dbStatement);
}

bool Database::isMember(char* idNumber)  // Get parameters later
{
    // Convert from char* to int
    int compare_this_number = atoi(idNumber);
    bool found = false;
    int continueStep = 100;  //sqlite3_step() returns 100 if there is another row to be read

    // Prepare dbStatement
    sqlite3_prepare(db, "select ID from Members", -1, &dbStatement, NULL);

    // While the number isn't found and there are more lines to read
    while(found == false &&
          continueStep == 100)
	{
		continueStep = sqlite3_step(dbStatement);  //sqlite3_step() returns 100 if there is another row to be read after current

		if(sqlite3_column_int(dbStatement, 0) == compare_this_number)
			found = true;
	}

    // Close dbStatement
	sqlite3_finalize(dbStatement);

    // Did we find the number?
    return found;
}

bool Database::isAttending(char* idNumber)
{
        // Convert from char* to int
    int compare_this_number = atoi(idNumber);
    bool found = false;
    int continueStep = 100;  //sqlite3_step() returns 100 if there is another row to be read

    // Prepare dbStatement
    sqlite3_prepare(db, "select ID from Attendance", -1, &dbStatement, NULL);

    // While the number isn't found and there are more lines to read
    while(found == false &&
          continueStep == 100)
	{
		continueStep = sqlite3_step(dbStatement);  //sqlite3_step() returns 100 if there is another row to be read after current

		if(sqlite3_column_int(dbStatement, 0) == compare_this_number)
			found = true;
	}

    // Close dbStatement
	sqlite3_finalize(dbStatement);

    // Did we find the number?
    return found;
}
