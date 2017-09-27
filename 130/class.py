#!/usr/bin/python3
# Zane Paksi

def gc(a, b):
    r = a % b
    a = a - r
    return a

print(gc(a=int(input('a: ')), b=3))
