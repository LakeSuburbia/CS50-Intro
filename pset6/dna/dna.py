#!/usr/bin/python
# -*- coding: utf-8 -*-
from sys import argv, exit
import csv

# invalid input? abort!

sequenties = {}
mensenData = {}
repeats = []
match = False

if len(argv) != 3:
    print('Er was een foutje met de input')
    exit(1)

# Lees de database in en plaats
with open(argv[1]) as data_file:
    database = csv.reader(data_file, delimiter=',')
        
    i = 0
    for row in database:
        if i == 0:
            sequenties = row
            sequenties.pop(0)
        else:
            dezeRij = row
            mensenData[dezeRij[0]] = [int(j) for j in dezeRij[1:]]
        i += 1

with open(argv[2], 'r') as DNA_data:
    DNA_data = DNA_data.read()
    
    # Overloop de dna data en vergelijk met de sequenties
        
    i = 0
    for seq in sequenties:
        teller = 0
        hoogste = 0
        j = 0
        while j < len(DNA_data):
            partitie = DNA_data[j:j + len(seq)].strip()
            if partitie == seq:
                teller = teller + 1
                j = j + len(seq)
        
                # print("part: ",partitie, teller, hoogste)
        
                if teller > hoogste:
                    hoogste = teller
            else:
                teller = 0
                j += 1
        repeats.append(hoogste)
        i += 1
    
for (name, data) in mensenData.items():

    # print(data, repeats)

    if data == repeats:
        print(name)
        match = True
if match == False:
    print('No match')
