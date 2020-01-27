#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TOKEN_LEN 64
#define TOKEN_CHAR_SET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define N_TOKEN 100000


void set_rand_str(int len, char* dst, char* char_set){
  int i, r_max;
  r_max = strlen(char_set);
  for(i = 0 ; i < len ; i++){
    int r = rand() % r_max;
    dst[i] = char_set[r];
  }
  dst[len] = '\0';
}
#define RAND_CHAR_SET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define set_rand_str_const(len, dst) set_rand_str((len),(dst) , RAND_CHAR_SET)
#define GET_MACRO(_1,_2,_3,NAME,...) NAME
#define set_rand_str(...) GET_MACRO(__VA_ARGS__, set_rand_str, set_rand_str_const)(__VA_ARGS__)

int compare(const void *a, const void *b)
{
  return strcmp(*(char**)a, *(char**)b);
}

int check_conflict(char **token, int n){
  int i;
  qsort(token, n, sizeof(char*), compare);
  for (i = 1 ; i < n ; i++){
    if (strcmp(token[i-1], token[i]) == 0){
      return 1;
    }
  }
  return 0;
}

void gen_token(){
  char **token, *ztoken, **token_base;
  int i;
  token = malloc(sizeof(char*) * N_TOKEN);
  ztoken = token[0] = malloc(sizeof(char) * N_TOKEN * (TOKEN_LEN + 1));

  for(i = 1 ; i < N_TOKEN ; i++){
    token[i] = token[i - 1] + (TOKEN_LEN + 1);
  }
  for(i = 0 ; i < N_TOKEN ; i++){
    set_rand_str(TOKEN_LEN, token[i], TOKEN_CHAR_SET);
  }
  if (check_conflict(token, N_TOKEN)){
    fprintf(stdout, "トークン衝突\n");
    return;
  }
  for(i = 0 ; i < N_TOKEN ; i++){
    fprintf(stdout, "%s\n", ztoken + (TOKEN_LEN + 1) * i);
  }
  free(ztoken);
  free(token);
}


int main(){
  gen_token();
  return 0;
}
