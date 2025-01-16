# Dev Log:

This document must be updated daily by EACH group member.

## Ray Xu

### 2025-01-06 - Setup program structure
Added basic files and functions needed to get a very basic concept done, nothing filled in yet. ~ 10 minutes

### 2025-01-07 - Basic functionality/template for server
Created forking server with two explicit clients, set up shared memory logic and formatted for easier logic handling by server. ~ 40 minutes

### 2025-01-08 - Added subserver features
Updated shared memory logic to facilitate server processing. Added code to subservers. ~ 35 minutes

### 2025-01-09 - Finished server logic
Added basic server logic for comparing moves/inputs from two clients. Also finished basic server-client read/write exchange. ~ 30 minutes

### 2025-01-10 - Finished basic game.
Finished server-client exchange and tested the basic game. Verified logic of comparing client responses. ~ 35 minutes

### 2025-01-13 - Finished stat logging, tested.
Completed implementation of logging stats by prompting client for username. Tested game to make sure stats updated as desired. ~ 45 minutes

### 2025-01-14 - Added SIGINT handling.
Added server-side and client-side handling for SIGINT occurring on either end. ~ 35 minutes

### 2025-01-15 - Worked on perms & server handling.
Tried to improve server-side handling of errors/SIGINT, tried to fix client perms denied. ~ 40 minutes

### 2025-01-16 - Finished tmp access, updated makefile.
Fixed client perms through adding chmod, updated makefile to allow client to specify subdirectory in tmp to put server/client in. ~ 45 minutes

## Souvik Basak

### 2025-01-06 - Setup stuff
Worked on PROPOSAL.md. ~ 12 minutes

### 2025-01-08 - Big changes to server/subservers
Instead of having shared memory segments for subservers to communicate with each other, each subserver simply has access to both clients once they connect. ~ 30 minutes

### 2025-01-09 - Debugging and stuff
Did a bunch of debugging with server sending and reading from client. ~ 30 minutes

### 2025-01-12 - User data
Created a struct to hold user data and wrote functions to load and create users. ~ 30 minutes

### 2025-01-13 - Fixing stuff and debugging
Did a lot of debugging with loading and creating new users, as well as fine-tuning print statements during the game. Wrote a debugging function in server_util. ~ 41 minutes
