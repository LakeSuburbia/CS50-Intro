from cs50 import get_string
import re

text = get_string("Text: ")
totaalAantalLetters = 0
totaalAantalWoorden = 1
totaalAantalZinnen = 0
n = int(len(text))

for c in text:
    if (c.isalpha()):
        totaalAantalLetters += 1
    
    if (c == " "):
        totaalAantalWoorden += 1
    
    if (c == "." or c == "!" or c == "?"):
        totaalAantalZinnen += 1
        
multiplier = totaalAantalWoorden / 100
L = totaalAantalLetters / multiplier
S = totaalAantalZinnen / multiplier
index = round((0.0588 * L) - (0.296 * S) - 15.8)

if (index < 1):
    print("Before Grade 1")
elif (index > 16):
    print("Grade 16+")
else:
    print("Grade", index)