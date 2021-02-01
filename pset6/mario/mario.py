from cs50 import get_int

while(1):
    height = get_int("hoogte: ")
    if (height <= 8 and height >= 1):
        break

for i in range(height):
    for j in range(height - i - 1):
        print(" ", end="")

    for j in range(i + 1):
        print("#", end="")

    print("  ", end="")

    for j in range(i + 1):
        print("#", end="")

    print()