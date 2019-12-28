#!/usr/bin/python3

# Zane Paksi
#
# 3n + 1 Problem

n = input()
print('')

while n:
    i, j = n.split()
    max = 0
    for k in range(int(i), int(j) + 1):
        count = 1
        while k != 1:
            if k % 2 == 0:
                k = k / 2
            else:
                k = 3 * k + 1
            count += 1
        if count > max:
            max = count
    print("{} {} {}".format(i, j, max))
    try:
        n = input()
    except EOFError:
        break
    
