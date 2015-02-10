#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashtable.h"
#include <getWord.h>



//////function to add the nodes to an array to be sorted.

Node** AddToArray(HTable* table, int numentries){
  Node** Array;
  if( (Array =  malloc( sizeof(Node*) * (numentries) ) )== NULL){
    return NULL;
  }
  int i;
  int j = 0;
  Node* lookingat = NULL;
  for(i=0; i <table->Size; i++){
    lookingat = table->listPTR[i];
    while(lookingat != NULL){
      Array[j] = lookingat;
      lookingat = lookingat->next;
      j++;
    }
  }
  return Array;
}

int compare (const void* node1, const void* node2){
  if((((Node*)node1)->count) < (((Node*)node2)->count)){
    return -1;
  }else if((((Node*)node1)->count) > (((Node*)node2)->count)){
    return 1;
  }else{
    return 0;
  }
}

char* concat(char* string1, char* string2){
  char* word = malloc(strlen(string1)+strlen(string2)+2); //+2 for space between.
  strcpy(word,string1);
  strcat(word," ");
  strcat(word,string2);
  return word;
}


int main(int argc, char** argv){
  //vars for the quicksort portion.
  char** array1;
  int arraylen = 0;
  //vars for the hashtable portion of reading in the file.
  FILE *file;
  int*  val;
  int start = 1;
  int buckets = 10;
  HTable* table = HT_init(buckets);  
  //reading the file into the hash table.
  file = fopen(argv[1], "r");
  if (file == NULL){
    fprintf(stderr, "File does not exist or no file was entered\n");
    fprintf(stderr, "Argument should be of the format: Filename.txt\n");
    return -1;
  }
  char* nextWord = NULL;  //grab the first word to initialize nextword.
  char* prevWord = NULL;
  char* word = NULL;
  do{          
    //loop through the file. adding the words to the LL.
    //prevWord = nextWord;
    //nextWord = getNextWord(file);
    //word = concat(prevWord, nextWord);
    nextWord = getNextWord(file);
    if(word != NULL){
      val = HT_search( table, (char*)strdup(word) );
      if(val == 0){
	HT_Insert(table, (char*)strdup(word), (void*)start);
	arraylen++;
      }
    }
    free(word);
  }while(nextWord != NULL);
  array1 = AddToArray(table,arraylen); 
  //sort the array
  qsort(array1, arraylen, sizeof(Node*),compare);
  for (int k = 0; k < 10; k++){
    printf("%s\n",((Node*)*array1[k])->data);
   }
  return 0; 
}
