[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Vh67aNdh)
# EPICGAMES Rock Paper Scissors (TM)

### Epic Games Developers [21]

Ray Xu
Souvik Basak
       
### Project Description:

This project is ranked rock paper scissors, where two users login through clients and play a 3 round game of rock paper scissors. A main server creates a subserver to handle each set of two clients, and the subserver handles all the game logic. Players login to their profiles through their username, and stats like games played, rating, rank, etc. are saved.
  
### Instructions:
In order to run this game, clone the repository and run `make compile`. Then, go to the `/tmp` directory (or ssh into it), run `make server` once, and have each client run `make client`. Both clients need to have run client in order for the game between them to start. The game walks you through the rest.
