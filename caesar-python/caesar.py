import cs50
import sys

key = int(sys.argv[1])

message = cs50.get_string("Enter string: ")
letter = 0
intmessage = []

for i in range(len(message)):
    if str.isalpha(message[i]):
        if str.isupper(message[i]):
            letter = ord(message[i]) - 65
            letter = ((letter + key) % 26) + 65
            intmessage.append(chr(letter))

        if str.islower(message[i]):
            letter = ord(message[i]) - 97
            letter = ((letter + key) % 26) + 97
            intmessage.append(chr(letter))

    else:
        intmessage.append(message[i])

print("ciphertext: ", end = "")

for n in range(len(message)):
    print(intmessage[n], end = "")

print()