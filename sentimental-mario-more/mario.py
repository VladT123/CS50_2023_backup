import cs50
while (True):
    input = cs50.get_int("Input an integer: ")
    if input>0 and input<9:
        break

for x in range(input):
    for y in range (input-1, x, -1):
        print(" ", end = '')
    for y in range (x+1):
        print("#", end = '')
    print("  ", end = '')
    for y in range (x+1):
        print("#", end = '')
    print()
print()