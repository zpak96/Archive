#!/usr/bin/python3

# Zane Paksi
# This is a text adventure game I made in fall of 2017. The goal is to defeat the
# the NPC named Fred. Enjoy!

import random
import pickle
import os
import sys


class Room():
    """Class for instantiating each room, this includes room name, exits, objects within, and items within."""
    
    def __init__(self, name):
        """ Characteristics of each room instance """

        self.name = name
        self.exits = {}
        self.inventory= []
        self.objects = []
        self.description = ''

    def __str__(self):
        """Describe the room in terms on the name, exits, and the items in the room """

        descr = "You are in the " + self.name + "\n"
        for key in self.exits:
            descr += "You can go " + key + " to the " + self.exits[key].name + "\n"
        for item in self.inventory:
            descr += "There is a " + item.name + " here.\n"
        for item in self.objects:
            descr += item.name + " is here."
        return descr

    def name(self, name):
        """ Returns the name of the room """

        return self.name
    

class Player():
    """Class for instantiating the player, this includes the players name, location, inventories, and health"""
    
    def __init__(self, name, location, health):
        """ Characteristics of the player """
        self.name = name
        self.location = location
        self.inventory = []
        self.weapon = []
        self.health = health

        
    def __str__(self):
        """Returns the player's health """

        descr = ("Your health is " + str(self.health))
        return descr

    def helpme(self):
        """Prints all commands usable by the player """

        print("{}{}{}".format('    ', 'Commands', ' '))
        print("{}{}{}".format('    ', '--------', ' '))
        print("{} {} {}".format('help   ', '|', 'Display all usable commands'))
        print("{} {} {}".format('look   ', '|', 'Explore the room to find current location, exits and potential items.'))
        print("{} {} {}".format('go     ', '|', 'The prefix required to navigate your player.'))
        print("{} {} {}".format('get    ', '|', 'The prefix for picking up items.'))
        print("{} {} {}".format('drop   ', '|', 'The prefix for dropping items.'))
        print("{} {} {}".format('inv    ', '|', 'Displays the player inventory'))
        print("{} {} {}".format('health ', '|', 'Displays player health'))
        print("{} {} {}".format('eat    ', '|', 'Allows the player to use consumables to gain health'))
        print("{} {} {}".format('equip  ', '|', 'Equip a weapon in your inventory'))
        print("{} {} {}".format('unequip', '|', 'Unequip a current weapon'))
        print("{} {} {}".format('attack ', '|', 'Allows the player to attack a non-player'))
        print("{} {} {}".format('push   ', '|', 'Returns NPC to spawn'))
        print("{} {} {}".format('save   ', '|', 'Save current player progress'))
        print("{} {} {}".format('load   ', '|', 'Load a previous character'))
    
    def get(self, command):
        """Command for picking up items """

        for item in self.location.inventory:
            if item.name == command[1]:
                self.inventory.append(item)
                self.location.inventory.remove(item)
                print("You picked up a", item.name)
                return
        print(command[1] + " is not here!")
               
    def drop(self, command):
        """Command for dropping items """
        
        for item in self.inventory:
            if item.name == command[1]:
                self.location.inventory.append(item)
                self.inventory.remove(item)
                print("You dropped a", item.name)
                return            
        print(command[1] + " is not here!")

    def inv(self, command):
        """prints the inventory. But mine is in a box because im cool"""

        side = '|'
        blank = 30 * " "
        line = 30 *  "-"
        diff2 = 11 * " "
        if not self.inventory:
        #check to see if the inventory is empty and if there is a weapon equipped
            if not self.weapon:
                print("Your inventory is empty and you have nothing in your hands.")
            else:
                print('Your inventory is empty and you have a ' + self.weapon[0].name + ' in your hands')
        else:
            print("{}{}{}".format('+', line, '+'))
            print("{}{}{} {}{}".format(side, (" " * 12), 'Items', (" " * 12), side))
            for item in self.inventory:
                diff = (30 - len(item.name)) * " "
                print("{}{}{}{}".format(side, item.name, diff, side))
            for thing in self.weapon:
                diff3 = (30 - len(thing.name)) * " "
                print("{}{}{}".format('+', line, '+'))
                print("{}{}{}{}{}".format(side, diff2, 'Equipped', diff2, side))
                print("{}{}{}{}".format(side, thing.name, diff3, side))
            print("{}{}{}".format('+', line, '+'))
                
    def equip(self, command):
        """Command for equipping weapons """

        if len(command) > 1:
            if not self.weapon:
                for item in self.inventory:
                    if item.name == command[1]:
                        if command[1] == 'knife' or command[1] == 'rock' or command[1] == 'stick' or command[1] == 'lamp':
                            self.inventory.remove(item)
                            self.weapon.append(item)
                            print("You equipped a " + item.name)
                            return
                        else:
                            print("You can't equip that")
            else:
                print('You cannot equip two items \nYou must unequip the ' + self.weapon[0].name + ' first.')
        else:
            print("Equip what?")

            
    def unequip(self, command):
        """Command for unequipping weapons"""

        if len(command) > 1:
            for item in self.weapon:
                if command[1] == item.name:
                    if command[1] == 'knife' or command[1] == 'stick' or command[1] == 'rock':
                        self.weapon.remove(item)
                        self.inventory.append(item)
                        print("You unequipped a " + item.name)
                        return
                    else:
                        print("You don't have anything equipped")
        else:
            print("Unequip what?")

            
    def attack(self, command):
        """Command for attacking the NPC"""
        
        if len(command) < 2:
            print("Attack what??")
        else:
            for item in self.location.objects:
                if command[1] == item.name:
                    if not self.weapon:
                        print("You aren't armed with a weapon!")
                    else:
                        if random.randint(1,3) == 1 or random.randint(1,3) == 3:
                            item.health -= self.weapon[0].damage
                            print('HIT!\nEnemy health at ' + str(item.health))
                        else:
                            print("MISSED!")
                #check if the enemy is dead
                if item.health <= 0:
                    print(item.name + ' is dead!')
                    self.location.objects.remove(item)
                    self.location.inventory.append(b)
                    if fred_lives:
                        print("fred grows stronger")
                        seven.objects.append(a)
                        a.location = seven
                        a.health = fred_lives[0]
                        fred_lives.pop(0)
                    else:
                        print('CONGRATS!\nYou have defeated your captor and escaped!')
                        p.win()
                break
                        
    def eat(self, command):
        """Allows the player to consume food to add to his health"""
        
        if len(command) > 1:
            if self.inventory:
                for item in self.inventory:
                    if item.name == command[1] and item.name != 'stick' and item.name != 'rock' and item.name != 'lamp' and item.name != 'stick':
                        self.health += item.food
                        if item.name == 'body':
                            print("That's just gross..")
                        elif item.name == 'thing':
                            print('It tasted like bacon..')
                        elif item.name == 'plunger':
                            print("+5 health, for effort..")
                        else:
                            print('You consumed a ' + item.name)
                        self.inventory.remove(item)    
                        print('Your health is now ' + str(self.health))
            else:
                print("You have no consumables in your inventory")
        else:
            print('Consume what?')
                
    def push(self, command):
        """Pushes the NPC back to his spawn point, in this case, the basement"""
        
        if len(command) > 1: 
            if p.location == a.location:
                for item in p.location.objects:
                    if command[1] == item.name:
                        item.location.objects.remove(a)
                        item.location = seven  
                        seven.objects.append(a)
                        print('You pushed ' + item.name + '!')
        else:
            print("Push who?")

    def win(self):
        """Winning function, the player is taken here if they defeat each of fred's lives"""
        
        print("You have won!\nWould you like to play again (y/n)")
        x = input('> ')
        if x == 'y':
            python = sys.executable
            os.execl(python, python, * sys.argv)
        elif x == 'n':
            sys.exit()
        
            
class Item():
    """The Class for instantiating all items"""
    
    def __init__(self, name, food):
        """ Characteristics of items """
        self.name = name
        self.food = food
        
    def name(self, name):
        """ returns the name of an item """
        return self.name
    
class Weapon():
    """Class for instantiating weapons. In this case, the knife, the rock and the stick"""

    def __init__(self, name, damage):
        """ Characteristics of weapons. Only 3 in the game. Sub-class of items """
        self.name = name
        self.damage = damage

    def damage(self, damage):
        """ Returns the damage of the weapon """
        return self.damage
    

class NonPlayer(Player):

    def __init__(self, name, location, health):
        """ Characteristics of NPC, sub-class of player """
        super().__init__(name, location, health)
        
    def move1(self):
        """ The first class for NPC movement. NPC randomly chooses on of their available exits """

        options = self.location.exits.keys()
        self.location.objects.remove(a)
        print('fred is moving..')
        self.location = self.location.exits[random.choice(list(options))]
        self.location.objects.append(a)

    def move2(self):
        """ Second class for NPC movement. If the player is in an adjacent room to the NPC, the NPC moves to the player and attacks """

        options = self.location.exits.keys()
        for key in options:
            if self.location.exits[key] == p.location:
                self.location.objects.remove(a)
                self.location = p.location
                self.location.objects.append(a)
                print('fred entered the room')
                self.attack(['attack', str(p.name)])
                break
        else:
            self.move1()

    def attack1(self, command):
        """ Attack function for the NPC. Like player, they have a 2/3 chance of getting a successful hit. """

        if random.randint(1,3) == 1 or random.randint(1,3) == 3:
            p.health -= self.weapon[0].damage
            print("You've been hit! \nHealth at " + str(p.health))
        else:
            print('Enemy tried to attack, missed!')
                
class Game():
    """The Class for saving and loading the game"""
    
    def __init__(self):
        """I don't know the purpose of this function honestly. I forget."""
        pass

    def save(self, p):
        """Using Pickle, the character is able to be saved"""
        pickle.dump(p, open('save.dat', 'wb'))
        print("Game Saved!")

    def load_game(self):
        """Using Pickle, a previous save can be loaded"""
        print('Game loaded!')
        return pickle.load(open("save.dat", 'rb'))

    
#directions
n = 'north'
s = 'south'
e = 'east'
w = 'west'

#instances of each room
one = Room("Attic")
two = Room("Hallway")
three = Room("Bedroom")
four = Room("Bathroom")
five = Room("Living Room")
six = Room("Kitchen")
seven = Room("Basement")
eight = Room("Back Yard")
nine = Room("Front Yard")
ten = Room("Closet")
eleven = Room("Master Bedroom")
twelve = Room("Dining Room")

#Exits for The Attic (R1)
one.exits[s] = two

#Exits for The Hallway (R2)
two.exits[e] = three 
two.exits[n] = one
two.exits[w] = four
two.exits[s] = five

#Exits for The Bedroom (R3)
three.exits[w] = two
three.exits[e] = ten

#exits for The Bathroom (R4)
four.exits[e] = two

#exits for The Living Room (R5)
five.exits[n] = two
five.exits[s] = nine
five.exits[w] = six
five.exits[e] = twelve

#Exits for the Kitchen (R6)
six.exits[e] = five
six.exits[w] = eight
six.exits[s] = seven

#Exits for the Basement (R7)
seven.exits[n] = six

#Exits for the Back Yard (R8)
eight.exits[e] = six

#Exits for the Front Yard (R9)
nine.exits[n] = five

#Exits for the Closet (R10)
ten.exits[w] = three

#Exits for the Master Bedroom (R11)
eleven.exits[w] = twelve

#Exits for the Dining Room (R12) 
twelve.exits[w] = five
twelve.exits[e] = eleven
twelve.exits[n] = two

game = Game()
p = Player("me", one, 10)

#Weapons
knife = Weapon("knife", 18)
seven.inventory.append(knife)
rock = Weapon("rock", 5)
nine.inventory.append(rock)
stick = Weapon("stick", 10)
eight.inventory.append(stick)
fists = Weapon('fists', 5)
lamp = Weapon('lamp', 10)
eleven.inventory.append(lamp)

#Items
t = Item("thing", 5)
one.inventory.append(t)
b = Item('body', 25)
cb = Item('snack', 5)
ten.inventory.append(cb)
tp = Item('plunger', 5)
four.inventory.append(tp)


#NPC
# This is if I want fred to respawn a certain number of times.
fred_lives = [50, 75, 100]
a = NonPlayer("fred", seven, fred_lives[0])
seven.objects.append(a)
a.weapon.append(fists)


#Greeting Message
print("\nSurvive.\nFind a weapon.")
print("Your health is " + str(p.health))
print("To begin, type 'help'")
        
command = input("> ").lower().strip().split()

while not command:
    command = input("> ").lower().strip().split()

    
while command[0] != "quit":

    # Player Commands
    if command[0] == "go" and len(command) >= 2:
        if command[1] in p.location.exits.keys():
            p.location = p.location.exits[command[1]]
            print('You are in the ' + p.location.name)
        else:
            print("I do no understand..")
            
    elif command[0] == "help":
        p.helpme()
    elif command[0] == "get" and len(command) >= 2:
        p.get(command)
    elif command[0] == "drop" and len(command) >= 2:
        p.drop(command)
    elif command[0] == "inv":
        p.inv(command)
    elif command[0] == 'equip':
        p.equip(command)
    elif command[0] == 'unequip':
        p.unequip(command)
    elif command[0] == 'attack':
        p.attack(command)
    elif command[0] == 'eat':
        p.eat(command)
    elif command[0] == 'health':
        print(p)
    elif command[0] == 'push':
        p.push(command)
        
    elif command[0] == 'load':
        p = game.load_game()
    elif command[0] == 'save':
        game.save(p)
    elif command[0] == 'look':
        print(p.location)
    print("-" * 15)         

    if a.health > 0:
        #NPC Commands
        if p.location == a.location:
            a.attack1(['attack', p.name])
        else:
            a.move2()        
        
    if p.health <= 0:
        print("You are dead! \nWould you like to play again (y/n)")
        x = input('> ')
        if x == 'y':
            python = sys.executable
            os.execl(python, python, * sys.argv)
        elif x == 'n':
            sys.exit()
    else:
        command = input("> ").lower().strip().split()

    while not command:
        command = input("> ").lower().strip().split()

