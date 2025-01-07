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
   
In order to store and display user data, we will write and read from files. To have the server connect to different clients, we will have forking subservers. The server and clients will communicate through named pipes. We will use signal handlers to deal with certain client actions; for example, if a client exits in the middle of the match, they will automatically lose.
     
We'll start with client (Ray)/server (Souvik) handshake and setting up basic communication. Then we'll implement client-to-client via server communication (Souvik) and install initial RPS game (Ray). Then we'll add additional features like storing information to files (Souvik) and adding abilities (Ray).
       
Structs may be employed to handle the storing of data easily.
    
# Intended pacing:

Jan 9 - Client to client via server communication established.
Jan 13 - Rock paper scissors game implemented.
Jan 17 - Additional features implemented.
