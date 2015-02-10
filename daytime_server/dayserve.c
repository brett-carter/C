/**
Brett Carter
brett.carter@wsu.edu
CS360 Assign 8
dayserve
 **/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define MY_PORT_NUMBER 49999



int main(int argc, char** argv){
  int connectfd;
  socklen_t length = sizeof(struct sockaddr_in);
  struct sockaddr_in clientAddr;
  struct hostent* hostEntry;
  char* hostName;
  time_t Time;
  char* Date;
  struct sockaddr_in servAddr;

  //create a socket.
  int listenfd;
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if(listenfd < 0){
    perror("Error: ");
    exit(1);
  }

  //bind a socket to a port.
  memset(&servAddr, 0, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons(MY_PORT_NUMBER);
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  if(bind(listenfd,(struct sockaddr*)&servAddr, sizeof(servAddr)) < 0){
    perror("bind");
    exit(1);
  }
  while(1){
    //connection queue.
    if((listen( listenfd, 1)) < 0){
      perror("Error: ");
      exit(1);
    }
    printf("listening....\n");    
    //wait until a connection occurs. connection descriptor returned.
    connectfd = accept(listenfd, (struct sockaddr*) &clientAddr, &length);
    
    //getting the host name.    
    hostEntry = gethostbyaddr(&(clientAddr.sin_addr),
			      sizeof(struct in_addr), AF_INET);
    hostName = hostEntry->h_name;
    printf("client: %s\n", hostName);
    if(hostName == NULL){
      herror("Error: ");
      exit(1);
    }
    //return date/time over the connection.
    Time = time(NULL);
    Date = ctime(&Time); 
    //send the data through the socket.
    write(connectfd, Date, strlen(Date));
  }
  return 1;
}
