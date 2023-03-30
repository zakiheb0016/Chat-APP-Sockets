#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
int main(){
    struct sockaddr_in information_server;
    struct sockaddr_in information_client;
    int socketID=socket(AF_INET,SOCK_STREAM,0);
    int connection=0;
    char message[255];
    socklen_t len =sizeof(struct sockaddr_in);
    if (socketID==-1){
        perror("socket");
        exit(-1);
    }
    memset(&information_server,0,sizeof(struct sockaddr_in));
    information_server.sin_port=htons(6666);
    information_server.sin_family=AF_INET;
    if ((bind(socketID,(struct sockaddr *) &information_server,sizeof(struct sockaddr)))==-1){
        perror("bind");
        exit(-1);
    }
    if ((listen(socketID,5))==-1){
        perror("listen");
        exit(-1);
    }
    memset(&information_client,0,sizeof(struct sockaddr_in));
    connection=accept(socketID,(struct sockaddr *)&information_client,&len);
    if (connection==-1){
        perror("accept");
        exit(-1);
    }
    printf("sucess");
    printf("connection accepted from %s\n",inet_ntoa(information_client.sin_addr));
    
    do{
        memset(message,0,255);
        recv(connection,message,255,0);
        printf("Received message : %s\n",message);
        if(strcmp(message,"EXIT")!=0){
            printf("Enter the message you wanna send\n");
            scanf("%s",message);
            if ((send(connection,message,strlen(message),0))==-1) perror("send");
        }
    }while (strcmp(message,"EXIT")!=0);
    shutdown(socketID,SHUT_RDWR);
    return 0;
}