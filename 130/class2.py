#!/usr/bin/python3

""" This is a program that will print a box around any string that is less than 80 characters."""


def border_box():
    string = input(str())
    blank = len(string) * " "
    line = len(string) * "-"
    side = '|'
    if len(string) < 80:
        print("{}{}{}".format('+', line, '+'))
        print("{}{}{}".format(side, blank,  side))
        print("{}{}{}".format(side, string, side))
        print("{}{}{}".format(side, blank,  side))
        print("{}{}{}".format('+', line, '+'))
    else:
        print('String is too long')
border_box()
        
