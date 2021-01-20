# tcp-based-threaded-server-for-each-client
A new server thread is created for every new client connection (upto 3, can be changed). The demo client also spawns three client threads to simulate multiple clients.

TCP based implementation

Client to Server: Array of numbers

Server to Client : Even number array

Thread implemented on both Server and Client

Singleton Logger implemented

run on linux

requires g++ compiler

Compilation command: 
g++ fileName.cpp -o outputFileName -lpthread

To Run (run client_thread and server on seperate terminals):
./outputFileName

Log file name:
log.txt

Output file name:
Output.png
