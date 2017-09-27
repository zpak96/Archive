#!/usr/bin/python3

def first(word):
    return word[0]


def last(word):
    return word[-1]


def middle(word):
    return word[1:-1]

# print(middle('Pi'))
#print(middle('I'))
#print(middle(''))
# These statements return empty strings

def is_palindrome():
    palin = str(input())
    drome = palin[::-1]

    if palin == drome:
        return True
    else:
        return False

print(is_palindrome())
