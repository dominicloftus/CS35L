#include <stdio.h>
#include <stdlib.h>


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





int main(void){
  char* word = malloc(0);
  char** all = malloc(0);
  int nword = 0;
  int nall = 0;
  while(!feof(stdin) && !ferror(stdin)){
    char let = getchar();
    if(ferror(stdin)){
      fprintf(stderr, "Read error");
      exit(1);
    }
    if(let == EOF){
      break;
    }

    word = realloc(word, (nword+1)*sizeof(char));
    if(word != NULL){
      word[nword] = let;
      nword++;
    }
    else{
      fprintf(stderr, "Memory Allocation Error");
      exit(1);
    }
    

    if(let == ' '){
      if(nword != 1){
	all = realloc(all, (nall+1)*sizeof(char*));
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

  for(int i = 0; i < nall; i++){
    for(int j = 0; all[i][j] != ' '; j++){
      putchar(all[i][j]);
    }
    putchar(' ');
  }
  free(all);
  free(word);
  
}













