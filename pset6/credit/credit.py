import math
from math import log10
from cs50 import get_int

creditcard = get_int("kaartnummer: ")
mem = creditcard
checksum = int(0)
length = math.floor(log10(creditcard))+1
firstdigits = int(0)
digit =int(0)

for i in range(length):
    digit = int(mem % 10)
    mem = int(mem / 10)
    if (i % 2 == 1):
        digit = 2 * digit
        if (digit > 9):
            checksum = int(checksum + int(digit % 10))
            checksum = int(checksum + int(digit / 10))
        else:
            checksum = int(checksum + digit)
        digit = digit / 2
    else:
        checksum = int(checksum + digit)

    if (i == length - 2):
        firstdigits = firstdigits + digit
    elif (i == length - 1):
        firstdigits = firstdigits + (digit * 10)

if (checksum % 10 != 0):
    print("INVALID")
elif (length == 15 and (firstdigits == 34 or firstdigits == 37)):
    print("AMEX")
elif (length == 13 and digit == 4):
    print("VISA")
elif (length == 16):
    if (firstdigits == 51 or firstdigits == 52 or firstdigits == 53 or firstdigits == 54 or firstdigits == 55):
        print("MASTERCARD")
    elif(digit == 4):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")