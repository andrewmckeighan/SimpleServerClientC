
A few simple steps are required to run this program.
=========================================================================================

1. Make sure you have two terminal windows open, one for client and the other for server.

2. Compile by typing 'make' into the terminal.
    NOTE: you may have a few warnings.

3. In one of the terminals, type './server' to start the server.

4. In the other terminal, type './client' to start the client.
    NOTE: you may have to give ther server a few seconds, 
          depending on if pyrite is being crabby.
          The server window should read "Connected" if you are 
          properly connected.

5. Type anything into the prompt on the client screen. The StringEncoder.c tends to
   print off of the conversions it does. As of now I haven't disabled that.

6. The client should receive "True" from the server showing a secure connection!

=========================================================================================

