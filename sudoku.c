#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){

  for(int i = 0; i < 9; i++){
    for(int j  =0; j < 9; j++){
      if(n->sudo[i][j] == 0) continue;
      for(int x = 0; x < 9; x++){
        if(x!=i){
          if(n->sudo[i][j] == n->sudo[x][j]) return 0;
        }
        if(x!=j){
          if(n->sudo[i][j] == n->sudo[i][x]) return 0;
        }
      }

      int l, d, l2, d2;
      l = (i/3) * 3;
      d = l +3;
      l2 = (j/3) *3;
      d2 = l2 + 3;
      
      for(int x = l; x < d; x++){
        for(int y = l2; y < d2; y++){
          if(x != i || y !=j ){
            if(n->sudo[x][y] == n->sudo[i][j]) return 0;
          }
        }
      }
    }
  }
  
  return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  
  for(int i  = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if( n->sudo[i][j] == 0){

        for(int k = 1 ; k <= 9; k++){
          Node* new = copy(n);
          new->sudo[i][j] = k;
          if(is_valid(new)) pushBack(list, new);
        }
        return list;
      }
    }
  }
      
  return list;
}


int is_final(Node* n){

  for(int i =0; i < 9; i++){
    for(int j =0; j < 9; j++){
      if(n->sudo[i][j] == 0) return 0;
    }
  }
  
  
  return 1;
}

Node* DFS(Node* initial, int* cont){


  if(is_final(initial)) return initial;
  
  if(initial == NULL) return NULL;

  List* mio =  get_adj_nodes(initial);

  Node* it  = first(mio);

  while(it!=NULL){
    (*cont) ++;
    Node* nodito = DFS(it, cont);
    
    if(nodito!=NULL) return nodito;
    
    it = next(mio);
  }
  
  return NULL;

}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/