import sys
import re
import csv
from cs50 import SQL
import cs50

db = SQL("sqlite:///students.db")

sys.argv[1] = sys.argv[1].lower()
m = re.search(".csv", sys.argv[1])

if len(sys.argv) != 2 or m == None:
    print("FOUTIEVE INPUT!")
    exit(1)


#db.execute("CREATE TABLE students(first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")


with open(sys.argv[1], "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        namen = []

        voornaam = None
        middennaam = None
        achternaam = None
        for i, deelnaam in enumerate(row['name'].split()):
            if i == 0:
                voornaam = deelnaam
            if (len(row['name'].split()) == 2):
                if i == 1:
                    achternaam = deelnaam
            if (len(row['name'].split()) == 3):
                if i == 1:
                    middennaam = deelnaam
                if i == 2:
                    achternaam = deelnaam

        #print (namen)

        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                   voornaam, middennaam, achternaam, row['house'], row['birth'])

        #print (len(namen))