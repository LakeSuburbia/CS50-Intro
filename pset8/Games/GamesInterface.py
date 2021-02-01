import os
import re

print("WELCOME TO SANDER'S GAMES")
print ("\n")

NogEens = True




while(NogEens):

    print("We've got:")
    print("- Mario\n- Pong\n- Tic Tac Toe\n- Snake")
    print ("\n")

    game = raw_input("Which game do you want to play?\n")
    print ("\n")

    while game.upper() != "MARIO" and game.upper() != "PONG" and game.upper() !="TIC TAC TOE" and game.upper() != "SNAKE":
        print("This is input is not a game we've got")
        print("Try again!")
        print ("\n")
        print("We've got:")
        print("- Mario\n- Pong\n- Tic Tac Toe\n- Snake")
        print ("\n")
        game = raw_input("Which game do you want to play?\n")
    print ("\n")


    if game.upper() == "MARIO":
        print("You want to play Mario!")
        print("Here we go!") 
        os.system('open -n -a love "Documents/GitHub/EigenProjecten/Games/mario.love"')


    if game.upper() == "PONG":
        print("You want to play Pong!")
        print("Here we go!")
        os.system('open -n -a love "Documents/GitHub/EigenProjecten/Games/pong.love"') 
        

    if game.upper() == "TIC TAC TOE":
        print("You want to play Tic Tac Toe!")
        print("Here we go!") 
        os.system('python Documents/GitHub/EigenProjecten/Games/tictactoe.py')

    if game.upper() == "SNAKE":
        print("You want to play Snake!")
        print("Here we go!") 
        os.system('python Documents/GitHub/EigenProjecten/Games/snake.py')

    print("\n\n\n")

    Herhaling = raw_input("Do you want to play again?\n")

    regex = re.compile(r'y(es)?$', flags=re.IGNORECASE)
    if regex.match(Herhaling):
        NogEens = True
    else:
        NogEens = False
        print("\n\nGoodbye!\nWe had a fun time!\n\n")
exit()