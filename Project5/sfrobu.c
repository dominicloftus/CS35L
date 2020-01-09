#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>

int frobcmp(void const *aa, void const *bb){
  char const *a = *(char const **) aa;
  char const *b = *(char const **) bb;
  while(1){
    if(*a == ' ' && *b == ' ')
      return 0;
    else if(*a == ' ' || (*a ^ 42) < (*b ^ 42))
      return -1;
    else if(*b == ' ' || (*a ^ 42) > (*b ^ 42))
      return 1;
    a++;
    b++;
  }

}





int main(int argc, const char* argv[]){
  if(argc > 2){
    fprintf(stderr, "Too many arguments");
    exit(1);
  }
  _Bool upper = 0;
  if(argc == 2 && argv[1] == "-f"){
    upper = 1;
  }

  struct stat filecheck;
  if(fstat(STDIN_FILENO, &filecheck) < 0){
    fprintf(stderr, "IO error");
    exit(1);
  }
  int nfile;
  if(S_ISREG(filecheck.st_mode)){
    nfile = filecheck.st_size;
  }
  else{
    nfile = 0;
  }
  
  
  char* word = malloc(0);
  char** all = malloc(sizeof(char) * nfile);
  int allsize = 0;
  int nword = 0;
  int nall = 0;
  char let[1];
  while(read(STDIN_FILENO, let, 1) > 0){
    
    if(allsize == nfile){
      nfile++;
      all = realloc(all, sizeof(char) * nfile + 1);
      if(all == NULL){
	fprintf(stderr, "Allocation error");
	exit(1);
      }
    }

    word = realloc(word, (nword+1)*sizeof(char));
    if(word != NULL){
      if(upper)
	word[nword] = toupper(*let);
      else
	word[nword] = *let;
      nword++;
      allsize++;
    }
    else{
      fprintf(stderr, "Memory Allocation Error");
      exit(1);
    }
    

    if(*let == ' '){
      if(nword != 1){
	if(all != NULL){
	  all[nall] = word;
	  nall++;
	  word = malloc(0);
	  nword = 0;
	}
	else{
	  fprintf(stderr, "Memory Allocation Error");
	  exit(1);
        }
      }
      else{
	word = malloc(0);
	nword = 0;
      }
    }
  }
  if(nword != 0){
    word = realloc(word, (nword+1)*sizeof(char));
    if(word != NULL){
      word[nword] = ' ';
      nword++;
    }
    else{
      fprintf(stderr, "Memory Allocation Error");
      exit(1);
    }

    all = realloc(all, (nall+1)*sizeof(char*));
    if(all != NULL){
      all[nall] = word;
      nall++;
    }
  }

  qsort(all, nall, sizeof(char*), frobcmp);

  char space = ' ';
  for(int i = 0; i < nall; i++){
    for(int j = 0; all[i][j] != ' '; j++){
      if(write(STDOUT_FILENO, &(all[i][j]), 1) < 1){
	fprintf(stderr, "Write Error");
	exit(1);
      }
    }
    if(write(STDOUT_FILENO, &space, 1) < 1){
      fprintf(stderr, "Write Error");
      exit(1);
    }
  }
  free(all);
  free(word);
  
}













