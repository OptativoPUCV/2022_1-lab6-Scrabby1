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
  int i;
  int j;
  int numero;
  int *d;
  for(i=0;i<9;i++)
  {
    d=(int*)calloc(10,sizeof(int));
    for(j=0;j<9;j++)
    {
      numero=n->sudo[i][j];
      if(numero==0)
      {
        continue;
      }
      if(d[numero]==1)
      {
        return 0;
      }
      else
      {
        d[numero]=1;
      }
    }
  }
  
  for(i=0;i<9;i++)
  {
    d=(int*)calloc(10,sizeof(int));
    for(j=0;j<9;j++)
    {
      numero=n->sudo[j][i];
      if(numero==0)
      {
        continue;
      }
      if(d[numero]==1)
      {
        return 0;
      }
      else
      {
        d[numero]=1;
      }
    }
  }
  int k;
  int p;
  for(k=0;k<9;k++)
  {
    d=(int*)calloc(10,sizeof(int));
    for(p=0;p<9;p++)
    {
      i=3*(k/3) + (p/3);
      j=3*(k%3) + (p%3);
      numero=n->sudo[i][j];
      if(numero==0)
      {
        continue;
      }
      if(d[numero]==1)
      {
        return 0;
      }
      else
      {
        d[numero]=1;
      }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  int i;
  int j;
  int numeroPosible = 1;
  for(i=0;i<9;i++)
    {
      for(j=0;j<9;j++)
        {
          if(n->sudo[i][j]==0)
          {
            while(numeroPosible<=9)
            {
              Node *adj_n=copy(n);
              adj_n->sudo[i][j]=numeroPosible;
              if(is_valid(adj_n)==1)
              {
                pushBack(list,adj_n);
              }
              numeroPosible++;
            }
            return list;
          }
        }
    }
  
    return list;
}


int is_final(Node* n){
  int i;
  int j;
  for(i=0;i<9;i++)
  {
    for(j=0;j<9;j++)
    {
      if(n->sudo[i][j]==0)
      {
        return 0;
      }
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* S=createStack();
  push(S,initial);
  while(get_size(S)!=0)
  {
    Node* buscar= top(S);
    pop(S);
    if(is_final(buscar)==1)
    {
      return buscar;
    }
    List *adj=get_adj_nodes(buscar);
    Node*aux=first(adj);
    while(aux)
    {
      push(S,aux);
      aux=next(adj);
    }
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