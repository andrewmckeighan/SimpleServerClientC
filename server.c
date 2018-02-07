#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "StringEncoder.c"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>
//#include <stdlib.h>

int main(void){
    pid_t pid;
    char buffer[1024]={0};
    char encrypted[1024]={0};
    char final[1024]={0};
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress;
    struct sockaddr_storage servStore;
    socklen_t addr_size;

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(7605);//check if matches client.
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddress.sin_zero, '\0', sizeof(serverAddress.sin_zero));
    bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    
    if(listen(serverSocket, 100)==0){
        printf("Listening\n");
    }else{
        printf("Error\n");
    }
    //both checks are to see if client disconnected. recv will return 0 or -1 if so.
    int check1;
    int check2;
    //loop for parent to run through. Allows server to gain other clients.
    while(1){
        addr_size = sizeof(servStore);
        //Fork service allows for multiple clients to communicate.
        pid=fork();
        //Accepts connection from client. Creates new socket for the client.
        clientSocket = accept(serverSocket, (struct sockaddr *) &servStore, &addr_size);
        
        printf("CLIENT CONNECTED.\n");
        //Second loop to constantly recieve more than one message from client.
        while(1){
            check1 = recv(clientSocket, buffer, sizeof(buffer), 0);
            check2 = recv(clientSocket, encrypted, sizeof(buffer), 0);
            //checks if client disconnected.
            if(check1<=0 || check2<=0){
                exit(pid);
                printf("CLIENT DISCONNECTED.\n");
                break;
            }
            //printf("received Buffer: %s\nAnd Encrypted: %s\n", buffer, encrypted);
            //Hash and encrypt the message
            SHA1(buffer, 1024, final);
            stringToAscii(final);
            stringToReverseAscii(final);
            stringToEncodedAscii(final);
            //printf("\nBuffer Encoded is: %s\n",final);
            //Compare both messages. Sends "True" if it is.
            if(strcmp(encrypted, final) == 0){
                printf("True\n");
                send(clientSocket, "True\n", 7, 0);
            }else{
                printf("False\n");
                send(clientSocket, "False\n", 7, 0);
            }
        }
        //exit(pid);
    }
    return 0;
}
