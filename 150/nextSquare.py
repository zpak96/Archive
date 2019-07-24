#!/usr/bin/python3

# Zane Paksi
# This program takes a number in as input and then returns the next square 
# of that number.

import math

def main():
    n = int(input())
    print(find_next_square(n))
    main()
    
def find_next_square(n):
    """Return the next largest square if n is a square, return -1 if not"""
    x = n
    n = math.floor(math.sqrt(n))
    
    #Check if n is a perfect square
    if x == n**2:
        upsqr = (n + 1)**2
        return(upsqr)
    else:
        return -1



        
main()
