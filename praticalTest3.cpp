#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 
#define DATA(node) ((node)->data) 
#define NEXT(node) ((node)->next) 
typedef enum _STATUS {ERROR,OK} STATUS; 
#define MAX_NOME 20 
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef struct _SMARTPHONE{ 
  char    marca[MAX_NOME]; 
  char    modelo[MAX_NOME]; 
  float   preco; 
  int     stock; 
} SMARTPHONE; 

typedef struct _LIST_NODE
{
	void * data;
	struct _LIST_NODE * next;
} LIST_NODE;

typedef LIST_NODE * LIST;
 
LIST_NODE * NewNode(void *); 
LIST_NODE * InsertIni(LIST *, void *); 
STATUS ReadFile(LIST *,char *);  
int main(int argc, char *argv[]) 
{ 
  LIST list; 
   SMARTPHONE phone; 
 
  if(!ReadFile(&list,"socios.txt")) 
    return 0;    
    //FreeList(&list); 
  return 1; 
}

STATUS ReadFile(LIST *list, char *name_file) 
{ 
  FILE *fp; 
  SMARTPHONE phone,*ptr; 
 
  if((fp = fopen(name_file,"r")) != NULL)  { 
    while(!feof(fp)) { //while(feof(fp) == 0)  { 
        fscanf(fp,"%[^;]; %[^;];%f;%d\n",phone.marca,phone.modelo,&phone.preco,&phone.stock); 
        if( ((ptr =(SMARTPHONE *)malloc(sizeof(SMARTPHONE)))!=NULL) && (InsertIni(list,ptr)!=NULL) )  { 
            strcpy(ptr ->marca,phone.marca); 
            strcpy(ptr ->modelo,phone.modelo); 
            ptr ->preco = phone.preco; 
            ptr->stock = phone.stock; 
        } 
        else 
            return ERROR; 
    } 
    fclose(fp); 
    return OK; 
  } 
  else 
    return ERROR; 
} 
 
LIST_NODE *NewNode(void *data) 
{ 
  LIST_NODE *new_node;  
  if((new_node = (LIST_NODE *)malloc(sizeof(LIST_NODE))) != NULL)  { 
    DATA(new_node) = data; 
    NEXT(new_node) = NULL; 
  } 
  return(new_node); 
} 
 
LIST_NODE *InsertIni(LIST *list, void *data) 
{ 
  LIST_NODE *new_node;  
  if((new_node = NewNode(data)) != NULL)  { 
    NEXT(new_node) = *list; 
    *list = new_node; 
  } 
  return(new_node); 
} 

void addPhone (LIST *list){
    SMARTPHONE *temp;
    char marca[MAX_NOME], modelo[MAX_NOME];
    float preco;
    int stock;
    printf("brand>>"); scanf("%s", marca);
    printf("model>>"); scanf("%s", modelo);
    printf("price>>"); scanf("%f", &preco);
    printf("stock>>"); scanf("%d", &stock);
    //((SMARTPHONE*)temp)->marca = marca;
    //((SMARTPHONE*)temp)->modelo = modelo;
    ((SMARTPHONE*)temp)->preco = preco;
    ((SMARTPHONE*)temp)->stock = stock;
    InsertIni(list, temp);
}

void allPrices (LIST *list){
  LIST_NODE *temp = *list;
  float sum = 0;
  while (temp != NULL){
    sum += (((SMARTPHONE*)DATA(temp))->preco);
    temp = NEXT(temp);
  }
  printf("all price: %.2f", sum);
}

STATUS removeNode (LIST *list, void *data){
  LIST_NODE *temp = *list, *prev;
  if (list == NULL){
    printf("list empty!");
    return ERROR;
  }
  if (DATA(*list) = data){
    *list = NEXT(*list);
    free(DATA(temp));
    free(temp);
  }
  temp = NEXT(temp);
  prev = temp;
  while (temp != NULL){
    if (DATA(temp) == data) break;
    temp = NEXT(temp);
    prev = NEXT(prev);
  }
  if (temp == NULL) return ERROR;
  NEXT(prev) = NEXT(temp);
  free(DATA(temp));
  free(temp);
}

void removeZeroStock (LIST *list){
  LIST_NODE *temp = *list;
  while (temp != NULL) if ((((SMARTPHONE*)DATA(temp))->preco) == 0) removeNode(list, DATA(temp));
}