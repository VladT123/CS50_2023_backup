import cs50

cardid = []     # stores card id number
cardid2 = []    # stores first part of luhn algorithm
print("Number: ", end='')
cardid = input()
x = 2
temp = ''
rev = ''
luhn = 0
try:    # try except used in case for loop tries to access digit beyond card number
    for i in cardid:
        temp = (int(cardid[-x]))*2  # multiply every second digit by 2
        rev = str(temp)+rev  # rev appends every second digit multiplied by 2 as a string
        x = x+2
except:
    y = 1
x = 0
for i in rev:
    cardid2.append(rev[x])  # using string makes it easier to separate 2 digit numbers like 12 into separate digits
    x = x+1
print(cardid2)

x = 0
for i in cardid2:
    luhn = int(cardid2[x])+luhn
    x = x+1

x = 1
try:
    for i in cardid:
        temp = int(cardid[-x])
        luhn = luhn+temp
        x = x+2
except:
    y = 2

if str(luhn)[-1] != '0':
    print("INVALID")
    exit()


if len(cardid) == 15 and cardid[0] == '3' and (cardid[1] == '4' or cardid[1] == '7'):
    print("AMEX")
elif len(cardid) == 16 and cardid[0] == '5' and cardid[1] in ['1', '2', '3', '4', '5']:
    print("MASTERCARD")
elif (len(cardid) == 13 or len(cardid) == 16) and cardid[0] == '4':
    print("VISA")
else:
    print("INVALID")
