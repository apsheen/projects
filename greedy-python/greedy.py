import cs50
import math

while True:
    change = cs50.get_float("Oh hello! How much change is owed?\n")

    if change > 0:
        break

change = change * 100
change = round(change)

coins = 0

while True:
    while change >= 25:
        coins = math.trunc(change / 25)
        change = change % 25

    while change >= 10:
        coins = coins + math.trunc(change / 10)
        change = change % 10

    while change >= 5:
        coins = coins + math.trunc(change / 5)
        change = change % 5

    while change >= 1:
        coins = coins + math.trunc(change / 1)
        change = change % 1

    if change == 0:
        print(coins)
        break
