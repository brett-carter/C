/**
Brett Carter
brett.carter@wsu.edu
CS360 Assign 8
daytime
 **/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <string.h>
#include <unistd.h>

#define MY_PORT_NUMBER 49999

int main(int argc, char** argv){
  int socketfd;
  struct sockaddr_in servaddr;
  struct hostent* hostEntry;
  struct in_addr **pptr;
  char buff[255];

  for( int i = 0; i < 255; i++){
    buff[i] = NULL;
  }

  //make an internet socket using TCP protocol.
  socketfd = socket(AF_INET, SOCK_STREAM, 0);

  //set-up server address.
  memset( &servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(MY_PORT_NUMBER);

  //get the numeric server address and store it in the address struct
  hostEntry = gethostbyname(argv[1]);
  if(hostEntry < 0 ){
    herror("Error: ");
    exit(1);
  }
  pptr = (struct in_addr **) hostEntry->h_addr_list;
  memcpy(&servaddr.sin_addr, *pptr, sizeof(struct in_addr));
  int cn = connect(socketfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
  if(cn < 0){
    perror("Error: ");
    exit(1);
  }
  //read from the socket until there are no more bytes to read.
  read(socketfd, buff, 255); 
  printf("Date & Time : %s", buff);
  return 1;
}
