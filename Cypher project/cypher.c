#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char encrypt(char c, int ith, char *key, int keyLen) {
  return (c - 32 + key[ith % keyLen]) % 95 + 32;  //algorithm to encrypt the txt.
}

char decrypt(char c, int ith, char *key, int keyLen) {
  return (c - 32 - key[ith % keyLen] + 3 * 95) % 95 + 32; //algorith yo decrypt.
}

int main(int argc, char **argv) 
{
  char *key; // Encryption string
  char mode;
  int keyLen = 0;
  int i = 0;
  int c;

  // no arguments
  if(argc < 3) {
    fprintf(stderr, "Invalid number of arguments\n");  //no e, d, or file.
    return -1;
  }

  if(argv[1][0] != 'e' && argv[1][0] != 'd') {    //user entered wrong char.
    fprintf(stderr, "First argument must be 'e' or 'd'\n");
    return -1;
  }

  mode = argv[1][0];   //E or D.
  key = argv[2];       //encryption pad.
  keyLen = strlen(key);// length of the pad.

  while(1) {
    if((c = fgetc(stdin)) == EOF) break;   //nothing left, done.
    
    if(c == '\n'){
      fputc('\n',stdout);
      continue;
    }
    
    if(mode == 'e') {          //encrypt
      fputc(encrypt(c, i, key, keyLen), stdout);
    } else if(mode == 'd') {   //decrypt
      fputc(decrypt(c, i, key, keyLen), stdout);
    }
    i++;
  }

  return 0;
}
