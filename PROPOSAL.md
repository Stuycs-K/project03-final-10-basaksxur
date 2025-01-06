# Final Project Proposal

## Group Members:

Ray Xu
Souvik Basak
       
# Intentions:

We intend to create a pipe networking server/client-based ranked rock paper scissors game. The server will match 2 clients against each other, and they will play 3 rounds of rock-paper scissors. The winner would receive some number of elo, and the loser would lose some. We would have client identification with a username, and their stats stored in separate text files.
    
# Intended usage:

First, the server should be running, then the clients can each log in with their username, and when there are two clients connected to the server, the server will match the clients against each other.
  
# Technical Details:

A description of your technical design. This should include:
   
In order to store and display user data, we will write and read from text files. To have the server connect to different clients, we will have forking subservers. The server and clients will communicate through named pipes. We will use signal handlers to deal with certain client actions; for example, if a client exits in the middle of the match, they will automatically lose.
     
How you are breaking down the project and who is responsible for which parts.
  
What data structures you will be using and how.
     
What algorithms and /or data structures you will be using, and how.
    
# Intended pacing:

A timeline with expected completion dates of parts of the project.
