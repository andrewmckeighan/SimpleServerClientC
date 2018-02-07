#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <openssl/sha.h>
#include <arpa/inet.h>
#include <math.h>
#include "StringEncoder.c"



int main(){
    int shouldrun = 1;
    char buffer[1024];
    char encrypted[1024];
    char answer[6];

    int clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    //set up socket settings.
    socklen_t addressSize;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(7605);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddress.sin_zero, '\0', sizeof(serverAddress.sin_zero));
    //connect to the socket.
    addressSize = sizeof(serverAddress);
    connect(clientSocket, (struct sockaddr *) &serverAddress, addressSize);
    //loop to allow you to send more than one message to the server.
    while(shouldrun){
        printf("Input>");
        fflush(stdout);
        fgets(buffer, 1024, stdin);
        //encrypt message.
        SHA1(buffer, 1024, encrypted);
        stringToAscii(encrypted);
        stringToReverseAscii(encrypted);
        stringToEncodedAscii(encrypted);
        //printf("\nSending: '%s'\n", buffer);
        //Send both the plain message and the encrypted message.
        send(clientSocket, buffer, sizeof(buffer), 0);
        send(clientSocket, encrypted, sizeof(encrypted), 0);
        recv(clientSocket, answer, 7, 0);
        printf("\nServer Replied: %s\n", answer);
    }
    return 0;
}


