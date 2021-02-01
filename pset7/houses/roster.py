import sys
from cs50 import SQL


db = SQL("sqlite:///students.db")


if len(sys.argv) != 2:
    print("FOUTIEVE INPUT!")
    exit(1)
    
cursor = db.execute("SELECT first, middle, last, birth FROM students WHERE house LIKE? ORDER BY last, first", sys.argv[1])


for row in cursor:
    if row['middle'] == None:
        print(row['first']+" "+row['last']+", born "+str(row['birth']))
    else:
        print(row['first']+" "+row['middle']+" "+row['last']+", born "+str(row['birth']))