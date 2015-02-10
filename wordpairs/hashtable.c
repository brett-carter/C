#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashtable.h"

float HT_loadfactor(HTable* table);
void HT_rehash(HTable* table);


////////////Hash function ////////////////////
unsigned long HT_hash(char* str){
  //bernstien hash - djb2
  unsigned long hash = 5381;
  int c;

  while((c = *str++)){
    hash = ((hash << 5) + hash) + c;   /* hash*33 + c*/
  }
  return hash;
}

///////// Initialize a new hashtable //////////////////
HTable* HT_init(int buckets){
  HTable* table;
  if((table = malloc(sizeof(HTable)))==NULL){  //create the struct,make room
    return NULL;
  }
  // allocates memory for the array.
  if((table->listPTR = malloc(buckets*sizeof(Node*)))== NULL){
    return NULL;
  }
  table->Size = buckets;
  table->Entries = 0;
  return table;
}


///////// search the table for a string and return the value if found. ////

int HT_search(HTable* ht, char* key){
  Node* LL;
  int size = ht->Size;
  int location = (int)HT_hash(key) % size;
  if(ht->listPTR[location] == NULL){
    return 0;
  }else{
    LL = ht->listPTR[location];
    while(LL != NULL){
      if(strcmp(key,LL->data) == 0){
	int num = (int)LL->count++;
	LL->count = num;
	return 1;
      }else{
	LL = LL->next;
      }
    }
  }
  return 0;
}




//////insert a node into the hashtable////////
void HT_Insert(HTable* ht, char* str, void* val){
  //start to the rehash ability of the table/////
  //check the load-factor and resize if necessary.//
  if((HT_loadfactor(ht)) >= 0.8){
    HT_rehash(ht);
    printf("rehashed\n");
    printf("size- %i\n", ht->Size);
  }
  int Loc = HT_hash(str)%(ht->Size);
  printf("found location: %i\n", Loc);
  printf("grabing the LL pointer\n");
  Node *LL = ht->listPTR[Loc];
  printf("have the LL pointer\n");
  if(LL == NULL){
    Node *node = malloc(sizeof(Node));  //allocate memory for the new node
    node->data = str;                   //set the node data.
    node->count = val;
    node->next = NULL;
    ht->listPTR[Loc] = node;            //put the node into the location.
    ht->Entries++;
    printf("new entry\n");
  }
  else{
    Node *new = malloc(sizeof(Node));
    printf("created a new node for the start of the list\n");
    new->data = str;
    new->count = val;
    new->next = LL;
    ht->listPTR[Loc] = new;
    ht->Entries++;
    printf("added the values to the new node\n");
  }
  
 
}


///apply some function to all the nodes in the hashtable//////
void* HT_Apply(HTable* ht, void (*FN)(char* a, void* b)){
  int i = 0;
  Node *LL;
  while(i < ht->Size){              //move through the array
    if(ht->listPTR[i] == NULL){     //if null move on.
      i++;
      continue;
    }
    else{                           //not null, enter linked list.
      LL = ht->listPTR[i];
      while(LL !=NULL){             //if a node, apply function and move on.
	FN(LL->data,LL->count);
	LL = LL->next;
      }
    }
    i++;
  }
  return NULL;
}


float HT_loadfactor(HTable* table){
  return (float)((table->Entries)/(table->Size));
}

void HT_rehash(HTable* table){
  HTable* old = table;
  printf("new size will be: %i\n",(int)(table->Size)*2);
  HTable* newtable = HT_init((table->Size)*2);  //double the table size.
  Node* Current = NULL;
  //loop through the old table re-entering into the new table.
  int i = 0;
  while (i < (table->Size)){
    Current = old->listPTR[i];
    
    if(Current == NULL){
      i++;
    }
    else{
      do{
	printf("rehashing word: %s\n", Current->data);
	printf("words value is: %i\n", Current->count);
	HT_Insert(newtable, Current->data, Current->count);
	printf("moving nodes. going to check current.next\n");
      }while((Current = Current->next) != NULL);
      printf("moved a LL set\n");
      i++;
    }
  }
  free(Current);
  free(old->listPTR);
  *old = *newtable;            
  free(newtable);
}


void HT_Free(HTable* ht){
  Node* Ncurrent;
  Node* Ntemp;
  int i = 0;
  while(i < ht->Size){
    if((ht->listPTR[i]) == NULL){
      i++;
      continue;
    }
    Ncurrent = ht->listPTR[i];
    do{
      Ntemp = Ncurrent->next;
      free(Ncurrent);
      Ncurrent = Ntemp;
    }while((Ncurrent) != NULL);
    i++;
  }
  free(ht->listPTR);   
  free(ht);            
}
