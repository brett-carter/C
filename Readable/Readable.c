/**
Brett Carter
brett.carter@wsu.edu
CS360 - systems programing
2/12/14
 **/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
//#include <cs360/misc.h>

void reading(const char* pathname);

int main(int argc, char* argv[]){
  const char* path;
  int length;
  if((argc == 2) && (path = strdup(argv[1]))){    //one argument
    printf("path: %s\n", path);
    
  }else{                            // zero arguments
    //path will equal the current working directory (cwd).
    printf("no pathway declared, using current directory...\n");
    path = getcwd(NULL, 64);
    printf("cwd: %s\n", path);
  }
  reading(path);
  return 0;
}

void reading(const char* pathname){
  DIR* directory;
  const char* pn;
  directory = opendir(pathname);
  
  if(directory == NULL){
    fprintf(stderr, "failed to open a directory\n");
    exit(1);
  }

  //recursively print out regular files within this and all subdirectories.
  struct dirent* currententry;
  struct stat sbuff;

  while(1){
    //d_type returns 8 for a reg file and 4 for a directory.
    currententry = readdir(directory);
    if(!currententry){ break;} // no more entries
    //if its either "." or ".." move on to the next entry. do not process these.
    if( (strcmp(currententry->d_name,".") == 0) || 
	(strcmp(currententry->d_name, "..") == 0)){
      continue;
    }
    //stat failure, exit.
    if(stat(currententry->d_name, &sbuff) == -1){ 
      fprintf(stderr, "error in stat()\n"); 
      exit(1);
    }
    
    //check file type.
    if(S_ISLINK(sbuff.st_mode)){
      printf("is a link\n");
      printf("entry: %s\n", currententry->d_name);
      continue;
    }
    else if(S_ISREG(sbuff.st_mode)){
      printf("is regular\n");
      printf("entry: %s\n", currententry->d_name);
    }
    else if(s_ISDIR(sbuff.st_mode)){
      printf("is a directory\n");
      printf("entry: %s\n", currententry->d_name);
    }
    
  }
  return;
}
