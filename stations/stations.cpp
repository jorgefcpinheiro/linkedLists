#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
typedef enum _BOOLEAN {FALSE,TRUE} BOOLEAN;
#define MAX 20
typedef struct _LIST_NODE
{
	void * data;
	struct _LIST_NODE * next;
} LIST_NODE;

typedef LIST_NODE * LIST;
typedef struct _ESTACAO{
    char desig[MAX];
    float custo;
    BOOLEAN ativa,no;
}ESTACAO;

typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _LIST_LOCATION { LIST_START, LIST_END } LIST_LOCATION;
typedef enum _STATUS { OK, ERROR } STATUS;
#define DATA(node) ((node)->data)
#define NEXT(node) ((node)->next)
#define EMPTY NULL
#define NO_LINK NULL
void initList(LIST *list){
    *list = NULL;
}
BOOLEAN emptyList(LIST list){
    if (list == NULL) return TRUE;
    return FALSE;
}
LIST_NODE * NewNode(void * data){
    LIST_NODE *new_node;
    if((new_node = (LIST_NODE *)malloc(sizeof(LIST_NODE))) != NULL){
        DATA(new_node) = data;
        NEXT(new_node) = NULL;
    }
    return (new_node);
}
STATUS InsertIni(LIST *list, void *data){
    LIST_NODE* new_node;
    if((new_node = NewNode(data)) != NULL){
        NEXT(new_node)=*list;
        *list=new_node;
        return OK;
    }
    return ERROR;
}
STATUS InsertEnd(LIST *list, void *data){
    LIST_NODE *new_node, *temp;
    if((new_node=NewNode(data)) != NULL)
    {
        if(*list == NULL) *list = new_node;
        else{
            temp = *list;
            while(NEXT(temp) != NULL) temp = NEXT(temp);
            NEXT(temp) = new_node;
        }
        return OK;
    }
    return ERROR;
};
int ListSize(LIST list){
    int count = 0;
    while (list != NULL){
        count++;
        list=NEXT(list);
    }
    return count;
}
void ShowValues(LIST list){
    if (emptyList(list) == TRUE) {
        printf("a lista esta vazia!");
        return;
    }
    while(list != NULL){
        printf("ESTACAO: %s, CUSTO: %f\n", ((ESTACAO *)DATA(list))->desig,((ESTACAO *)DATA(list))->custo);
        list=NEXT(list);
    }
}

void changeActive (LIST *list){
    LIST_NODE *temp = *list;
    char name[MAX];
    printf("station name >>"); scanf("%s", name);
    while (temp != NULL){
        if (((ESTACAO*)DATA(temp))->desig == name) break;
        temp = NEXT(temp);
    }
    if (temp == NULL){
        printf("station not on the list");
        return;
    }
    if (((ESTACAO *)DATA(temp))->ativa == TRUE) ((ESTACAO *)DATA(temp))->ativa = FALSE;
    else ((ESTACAO *)DATA(temp))->ativa = TRUE;
}