#!/usr/bin/python3.6

import string

def get_input():
    str1 = str(input())
    str_split(str1) 

def str_split(str1):
    reverse = str()
    str1 = str1.split()
    for i in str1:
        reverse += i[::-1] + ' ' 
    print(reverse)
    get_input()
    

    
get_input()
