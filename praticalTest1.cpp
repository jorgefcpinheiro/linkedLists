#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define DATA(node) ((node)->data)
#define NEXT(node) ((node)->next)
typedef enum _STATUS {ERROR,OK} STATUS;
typedef enum _BOOLEAN {FALSE,TRUE} BOOLEAN;
#define MAX_NOME 20

typedef struct _LIST_NODE
{
	void * data;
	struct _LIST_NODE * next;
} LIST_NODE;

typedef LIST_NODE * LIST;

typedef struct _PLAYER{
    char nome[MAX_NOME];
    char clube[MAX_NOME];
    int posicao;
    BOOLEAN titular;
} PLAYER;

typedef LIST_NODE * LIST;
LIST_NODE *NewNode(void *data){
    LIST_NODE *new_node;
    if((new_node = (LIST_NODE *)malloc(sizeof(LIST_NODE))) != NULL) {
        DATA(new_node) = data;
        NEXT(new_node) = NULL;
    }
    return(new_node);
}

STATUS InsertIni(LIST* list, void* data)
{
	LIST_NODE* new_node;
	if ((new_node = NewNode(data)) != NULL)
	{
		NEXT(new_node) = *list;
		*list = new_node;
		return OK;
	}
	return ERROR;
}

STATUS ReadFile(LIST *list, char *name_file)
{
    FILE *fp;
    PLAYER player,*ptr;
    int aux;
    if((fp = fopen(name_file,"r")) != NULL) {
        while(!feof(fp)) { //while(feof(fp) == 0)
            fscanf(fp,"%[^;]; %[^;];%f;%d\n",player.nome, player.clube,& player.posicao,&aux);
            if( ((ptr =(PLAYER *)malloc(sizeof(PLAYER)))!=NULL) && (InsertIni(list,ptr)!=NULL) ) {
                strcpy(ptr ->nome,player.nome);
                strcpy(ptr ->clube,player.clube);
                ptr ->posicao = player.posicao;
                if(aux) ptr->titular = TRUE;
                else ptr->titular = FALSE;
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

void FreeList(LIST* list){
    LIST_NODE *node;
    while(list != NULL){
        node=NEXT(*list);
        free(DATA(*list));
        free(*list);
        *list = node;
    }
}

STATUS addPlayer(LIST* list){
	PLAYER* pt=NULL;
	int titular = 0;

	if (((pt = (PLAYER*)malloc(sizeof(PLAYER))) != NULL) && (InsertIni(list,pt)==OK))
	{
		printf("Nome >> ");
		scanf("%s", pt->nome);
		printf("Club >> ");
		scanf("%s", pt->clube);
		printf("Posicao >> ");
		scanf("%d", &(pt->posicao));
		printf("Titular >> ");
		scanf("%d", &titular);
		if (titular == 1)
			pt->titular = TRUE;
		else
			pt->titular = FALSE;
	}
}

void showEleven (LIST *list){
    while (list != NULL){
        if (((PLAYER*)DATA(*list))->titular == TRUE){
            printf("%s | %s | %s",((PLAYER*)DATA(*list))->clube, ((PLAYER*)DATA(*list))->posicao, ((PLAYER*)DATA(*list))->nome);
            *list = NEXT(*list);
        }
    }
}

void subPlayer(LIST* list){
    char plOut[MAX_NOME];
    char plIn[MAX_NOME];
    LIST_NODE *temp = *list;
    printf("name player in >>"); scanf("%s", plIn);
    printf("name player out >>"); scanf("%s", plOut);
    while(temp != NULL){
        if(((PLAYER*)DATA(*list))->nome == plIn) {
            if (((PLAYER*)DATA(*list))->titular = FALSE) ((PLAYER*)DATA(*list))->titular = TRUE; 
            else printf("the player is already in");
        if(((PLAYER*)DATA(*list))->nome == plOut) 
            if(((PLAYER*)DATA(*list))->titular = TRUE) ((PLAYER*)DATA(*list))->titular = FALSE;
            else printf("the player is already out");
        temp=NEXT(temp); 
        }
    }
}

int main(int argc, char *argv[])
{
    LIST list;
    PLAYER player;
    if(!ReadFile(&list,"selecao.txt"))
    return 0;
    FreeList(&list);
    return 1;
}

