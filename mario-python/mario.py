import cs50

zero = False

while True:
    height = cs50.get_int("number: ")

    if height == 0:
        zero = True

    if height <= 23 and height >= 0:
        break

if zero == False:
    for i in range (height):
        print(" " * (height - 1 - i), end = "")
        print("#" * (i + 2), end = "")
        print()
