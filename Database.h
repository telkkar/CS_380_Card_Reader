
#ifndef _DATABASE_H
#define _DATABASE_H

#include "sqlite3.h"

class Database
{
public:
    Database();
    ~Database();
    void addAttendance(char* idNumber, char* name);
    void addMember(char* idNumber, char* name);
    bool isMember(char* idNumber);
    bool isAttending(char* idNumber);


private:
    sqlite3* db;
    sqlite3_stmt* dbStatement;


};

#endif // _DATABASE.H
