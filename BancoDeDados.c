#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "tadSql.h"

void createDatabase(TpBancoDeDados **pontBd) {
	FILE *ptrArq = fopen("comandoBanco.txt", "r");
	TpTabela *tabelaAtual = NULL;
	char string[100], string2[100], palavra[30];
	
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
			tabelaAtual = newTable(&(*pontBd)->pTabelas, palavra);
			printf("criou %s\n", palavra);
			//puts((*pontBd)->pTabelas->pCampos);
			fscanf(ptrArq, "%[^\n]\n", string);
			while(strcmp(string,");") != 0) {
				if(strstr(string, "PRIMARY KEY")) {
					printf("");
				// definePk(*pontBd, string);
				}
				else {
					newCampo(&tabelaAtual->pCampos, string);
				}
				fscanf(ptrArq, "%[^\n]\n", string); 
			}
		}
		if(strstr(string,"ALTER TABLE" )) {
			printf("Define FK\n");
			fscanf(ptrArq, "%[^\n]\n", string2); 
			defineFk(*pontBd, string, string2);
		}
		fscanf(ptrArq, "%[^\n]\n", string);
	}
	fclose(ptrArq);
}

int main(void) {
	TpBancoDeDados *pontBd;
	char palavra[30];
	//FILE *ptrArq = fopen("comandoBanco.txt", "r");
	createDatabase(&pontBd);
	mostraTudo(pontBd->pTabelas);
	//retornaPalavra("CREATE DATABASE db_locadora", , palavra);
    //puts(palavra);
    	
//    printf("%c, %s\n", pontBd->pTabelas->pCampos->pk, pontBd->pTabelas->pCampos->nome);
//	printf("%c\n", pontBd->pTabelas->pCampos->prox->pk);
//	printf("%c\n", pontBd->pTabelas->pCampos->prox->prox->pk);
//	printf("%c\n", pontBd->pTabelas->pCampos->prox->prox->prox->pk);
	
	return 0;
}

