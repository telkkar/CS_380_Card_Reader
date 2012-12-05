
#include <iostream>
#include <cassert>

#include "Database.h"
#include "defines.h"

using namespace std;

int testCount = 3;

string test[][4] =
{ { "1", "", "", ""},
  { "2", "123456789012345678901234567890", "1234567", "12345678901234567890123456789012345678901234567890123456789012345678901234567890"},
  { "1234567890123456", "123456789012345678901234567890", "1234567", "12345678901234567890123456789012345678901234567890123456789012345678901234567890"}
};

string edit[][3] = 
{ { "1234", "1234", "1234" } };

int main()
{
	Database db;
	
	cout << "Checking lengths on test cases... " << endl;
	for(int i = 0; i < testCount; i++)
	{
		cout << "\tCase " << i+1 << "... ";
		assert(test[i][0].length() <= LENGTH_CARD_NUMBER);
		assert(test[i][1].length() <= LENGTH_NAME);
		assert(test[i][2].length() <= LENGTH_MSU_ID);
		assert(test[i][3].length() <= LENGTH_COURSES);
		cout << "Done." << endl;
	}
	cout << "Done." << endl << endl;
	
	
	cout << "Adding to members and attendance table..." << endl;
	for (int i = 0; i < testCount; i++)
	{
		db.addMember((char *)test[i][0].c_str(), (char *)test[i][1].c_str(), (char *)test[i][2].c_str(), (char *)test[i][3].c_str());
		db.addAttendance((char *)test[i][0].c_str(), (char *)test[i][1].c_str(), (char *)test[i][2].c_str(), (char *)test[i][3].c_str());
	}
	cout << "Done." << endl << endl;
	
	cout << "Checking getAttendanceCount()... " << endl;
	assert(db.getAttendanceCount() == testCount);
	cout << "Done." << endl << endl;
	
	cout << "Checking ifMember() and isAttending()... " << endl;
	for (int i = 0; i < testCount; i++)
	{
		assert(db.isMember((char *)test[i][0].c_str()));
		assert(db.isAttending((char *)test[i][0].c_str()));
	}
	cout << "Done." << endl << endl;
	
	cout << "Checking getMemberInfo() for accuracy... " << endl;
	for (int i = 0; i < testCount; i++)
	{
		char name[LENGTH_NAME] = "";
		char id[LENGTH_MSU_ID] = "";
		char courses[LENGTH_COURSES] = "";
	
		db.getMemberInfo((char *)test[i][0].c_str(), name, id, courses);
		
		assert(test[i][1].compare(name) == 0);
		assert(test[i][2].compare(id) == 0);
		assert(test[i][3].compare(courses) == 0);
	}
	cout << "Done." << endl << endl;
	
	cout << "Checking editInformation... " << endl;
	char name[LENGTH_NAME] = "";
	char id[LENGTH_MSU_ID] = "";
	char courses[LENGTH_COURSES] = "";
	
	db.editInformation((char *)test[0][0].c_str(), (char *)edit[0][0].c_str(), (char *)edit[0][1].c_str(), (char *)edit[0][2].c_str());
	db.getMemberInfo((char *)test[0][0].c_str(), name, id, courses);
	
	assert(!(test[0][1].compare(name) == 0));
	assert(!(test[0][2].compare(id) == 0));
	assert(!(test[0][3].compare(courses) == 0));
	cout << "Done. Changing back..." << endl;
	
	db.editInformation((char *)test[0][0].c_str(), (char *)test[0][1].c_str(), (char *)test[0][2].c_str(), (char *)test[0][3].c_str());
	
	assert((test[0][1].compare(name) == 0));
	assert((test[0][2].compare(id) == 0));
	assert((test[0][3].compare(courses) == 0));
	cout << "Done." << endl << endl;
	
	cout << "Checking getAttendanceTable... " << endl;
	char ***dataArray = db.getAttendanceTable();
	
	for (int i = 0; i < testCount; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			assert(test[i][j].compare(dataArray[i][j]) == 0);
		}
	}
	cout << "Done. Deleteing array." << endl;
	
	for(int i = 0; i < db.getAttendanceCount(); i++)
	{
		for(int j = 0; j < 3; j++)
		{
			delete dataArray[i][j];
		}

		delete dataArray[i];
	}
	delete dataArray;
	cout << "Done." << endl << endl;
	
	cout << "Checking clearAttendance..." << endl;
	db.clearAttendance();
	assert(db.getAttendanceCount() == 0);
	cout << "Done." << endl << endl;
	
	cout << "All methods have been tested, and are working." << endl
		 << "Exiting test driver." << endl << endl;
		
	return 0;
}