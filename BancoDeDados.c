#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "tadSql.h"

void createDatabase(TpBancoDeDados **pontBd) {
	FILE *ptrArq = fopen("comandoBanco2.txt", "r");
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
			fscanf(ptrArq, "%[^\n]\n", string);
			while(strcmp(string,");") != 0) {
				if(strstr(string, "PRIMARY KEY")) {
					definePk(&tabelaAtual, string);
				}
				else {
					newCampo(&tabelaAtual->pCampos, string);
				}
				fscanf(ptrArq, "%[^\n]\n", string); 
			}
		}
		if(strstr(string,"ALTER TABLE" )) {
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
	createDatabase(&pontBd);
	mostraTudo(pontBd);
	inserir(&pontBd->pTabelas);
	inserir(&pontBd->pTabelas);
	inserir(&pontBd->pTabelas);
	inserir(&pontBd->pTabelas);
	mostraDados(pontBd);
	return 0;
}

