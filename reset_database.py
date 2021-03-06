# Script to normalize the database before pushing to github
# (mainly because we're having trouble with git and binary files)

import sqlite3

def main():
    conn = sqlite3.connect("database.db")
    c = conn.cursor()

    c.execute("DELETE FROM Attendance")
    c.execute("DELETE FROM Members")

    for i in range(0, 100):
        purchases = [str(i), "Person " + str(i), "100" + str(i), "Courses " + str(i)]
        c.execute("INSERT INTO Members VALUES(?, ?, ?, ?)", purchases)

    conn.commit()

	## Display Members table
    #for row in c.execute("SELECT * FROM Members"):
    #    print row
	
	## Display Attendance table
    #for row in c.execute("SELECT * FROM Attendance"):
    #    print row
    
    conn.close()

main()
