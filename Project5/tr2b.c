#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Bool checkDupes(char from[], int n, char check){
  int i;
  for(i = 0; i < n; i++){
    if(from[i] == check)
      return 1;
  }
  return 0;
}

int getind(char from[], int n, char check){
  int i;
  for(i = 0; i < n; i++){
    if(from[i] == check){
      return i;
    }
  }
  return -1;
    
}

int main(int argc, const char* argv[]){
  if(argc != 3){
    fprintf(stderr, "Incorrect number of arguments\n");
    exit(1);
  }
  const char* str1 = argv[1];
  const char* str2 = argv[2];
  if(strlen(str1) != strlen(str2)){
    fprintf(stderr, "Recieved arguments are different lengths\n");
    exit(1);
  }
  char *from = malloc(sizeof(char)*strlen(str1));
  int nfrom = 0;
  char *to = malloc(sizeof(char)*strlen(str2));
  int nto = 0;
  int i;
  for(i = 0; i < strlen(str1); i++){
    char ch = str1[i];
    if(checkDupes(from, nfrom, ch)){
	fprintf(stderr, "From argument contains duplicate characters\n");
	exit(1);
    }
    from[i] = ch;
    nfrom++;
    to[i] = str2[i];
    nto++;
  }

  
  char ch = getchar();
  while(ch != EOF){
    int ind = getind(from, nfrom, ch);
    if(ind == -1)
      putchar(ch);
    else{
      putchar(to[ind]);
    }
    ch = getchar();
  }
  
  

  
}
