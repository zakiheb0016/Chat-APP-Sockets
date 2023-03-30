#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
int main(){
    char message[255];
    struct sockaddr_in informations;
    informations.sin_family=AF_INET;
    informations.sin_port=htons(6666);
    informations.sin_addr.s_addr=inet_addr("105.107.43.179");
    int socketID = socket(AF_INET,SOCK_STREAM,0);
    if (socketID==-1){
        perror("socket");
        exit(-1);
    }
    if((connect(socketID,(struct sockaddr_in *) &informations,sizeof( struct sockaddr_in) )) ==-1) {
        perror("connect");
        exit(-1);
    }
    do{
        printf("Enter the message you wanna send\n");
        scanf("%s",message);
        if ((send(socketID,message,strlen(message),0))==-1) perror("send");
        if(strcmp(message,"EXIT")!=0){
            memset(message,0,255);
            recv(socketID,message,255,0);
            printf("Received message : %s\n",message);
        }
    }while(strcmp(message,"EXIT") !=0);
    shutdown(socketID,SHUT_RDWR);
    return 0;
}