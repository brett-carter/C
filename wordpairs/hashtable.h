#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct Node{
  struct Node *next;
  char* data;
  void* count;
}Node;

typedef struct hashtable{
  int Size;
  int Entries;
  struct Node **listPTR;  //array of pointers to LL's
}HTable;

unsigned long HT_hash(char* str);
HTable* HT_init(int buckets);
int HT_search(HTable* ht, char *key);
void HT_Insert(HTable* ht, char* str, void* val);
void* HT_Apply(HTable* ht, void (*FN)(char* a, void* b));
void HT_Free(HTable* ht);

#endif
