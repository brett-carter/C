/**
Brett Carter
brett.carter@wsu.edu
CS360
Ok assignment.
 **/



#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

//#define DICTIONARY "/cs_Share/class/cs360/lib/webster"
#define DICTIONARY "webster"

//*****function declarations******//
int Ok(int fp, char* word);
//********************************//

int main(int argc, char* argv[]){
  int fp;
  char buffer[15];
  
  if( (fp = open(DICTIONARY, O_RDONLY, 0)) < 0){
    fprintf(stderr, "could not open dictionary\n");
    exit(1);
  }
  if(argc == 2){
    int length = strlen(argv[1]);
    if(length > 15){
      fprintf(stderr, "word length must not exceed 15 characters\n");
      exit(1);
    }
    for(int i = 0; i < length; i++){
      buffer[i] = argv[1][i];
    }
    int space = 16 - length;
    for(int j = 0; j < space; j++){
      buffer[length+j] = ' ';
    }
    buffer[15] = '\0';
    int In = Ok(fp, buffer);
    if(In == 1){
      printf("Yes\n");
    }else{
      printf("No\n");
    }
    return 0;
  }else{
    fprintf(stderr, "usage: %s word\n", argv[0]); 
    exit(1);
  }
  
}


int Ok(int fp, char* word){
  int ending = 0;
  int bot = 0;
  int top = 0;
  int check;
  char wb[15];
  ending = lseek(fp,ending,SEEK_END);
  //find the number of lines//
  int lines = ending/16;
  top = lines;
  while(top > bot){
    int mid = (bot+top)/2;
    lseek(fp, mid*16, SEEK_SET);
    read(fp,wb,16);
    wb[15] = '\0';
    check = strcmp(wb, word);
    if(check == 0){
      return 1;
    }else if(check < 0){
      bot = mid+1;
    }else{
      top = mid-1;
    }
  }
  return 0;
}
