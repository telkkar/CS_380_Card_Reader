
#ifndef _DATABASE_H
#define _DATABASE_H

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
	void getMemberInfo(char* cardNumber, char* name, char* idNumber, char* courses);


private:
    sqlite3* db;
    sqlite3_stmt* dbStatement;


};

#endif // _DATABASE.H
