#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
typedef struct _LIST_NODE
{
	void * data;
	struct _LIST_NODE * next;
} LIST_NODE;

typedef LIST_NODE * LIST;
typedef struct _ALUNO
{
	char nome[30];
	int idade;
}ALUNO;

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
        printf("ALUNO: %s, IDADE: %d\n", ((ALUNO *)DATA(list))->nome,((ALUNO *)DATA(list))->idade);
        list=NEXT(list);
    }
}