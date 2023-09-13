#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "tadSql.h"

void createDatabase(TpBancoDeDados **pontBd) {
	FILE *ptrArq = fopen("comandoBanco.txt", "r");
	char string[100], palavra[30];
	
	if(ptrArq == NULL)	{
		printf("Erro ao abrir o arquivo!");
	}
	
	fscanf(ptrArq, "%[^\n]\n", string);
	while(!feof(ptrArq)) {
		if(strstr(string, "CREATE DATABASE")) {
			retornaPalavra(string, 3, palavra);
			*pontBd = newDatabase(palavra);
		}
		
		if(strstr(string, "CREATE TABLE")) {
			retornaPalavra(string, 3, palavra);
			newTable(&(*pontBd)->pTabelas, palavra);
			//puts((*pontBd)->pTabelas->pCampos);
				
			fscanf(ptrArq, "%[^\n]\n", string);
			while(strcmp(string,");") != 0) {
				newCampo(&(*pontBd)->pTabelas->pCampos, string);		
				fscanf(ptrArq, "%[^\n]\n", string); 				
			}
		}
		if(strstr(string,"ALTER TABLE" ))
			printf("****Vincular banco*****\n\n");
		fscanf(ptrArq, "%[^\n]\n", string);
	}
	fclose(ptrArq);
}

int main(void) {
	TpBancoDeDados *pontBd;
	char palavra[30];
	//FILE *ptrArq = fopen("comandoBanco.txt", "r");
	createDatabase(&pontBd);
	//retornaPalavra("CREATE DATABASE db_locadora", , palavra);
    //puts(palavra);
 
    if(pontBd->pTabelas->pCampos == NULL)
    	printf("erro!");
    printf("%s\n", pontBd->pTabelas->pCampos->nome);
	printf("%s\n", pontBd->pTabelas->pCampos->prox->nome);
	printf("%s\n", pontBd->pTabelas->pCampos->prox->prox->nome);
	printf("%s\n", pontBd->pTabelas->pCampos->prox->prox->prox->nome);
	return 0;
}