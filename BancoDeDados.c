#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio2.h>
#include<windows.h>
#include "tadSql.h"

void createDatabase(TpBancoDeDados **pontBd) {
	FILE *ptrArq = fopen("scriptdboficina.txt", "r");
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
		
	if(teste(string, "CREATE TABLE")) {
			retornaPalavra(string, 3, palavra);
			tabelaAtual = newTable(&(*pontBd)->pTabelas, palavra);
			fscanf(ptrArq, "%[^\n]\n", string);
			while(strcmp(string,");") != 0) {
				if(teste(string, "PRIMARY KEY")) {
					definePk(&tabelaAtual, string);
				}
				else {
					newCampo(&tabelaAtual->pCampos, string);
				}
				fscanf(ptrArq, "%[^\n]\n", string); 
			}
		}
		if(teste(string,"ALTER TABLE" )) {
			fscanf(ptrArq, "%[^\n]\n", string2); 
			defineFk(*pontBd, string, string2);
		}
		fscanf(ptrArq, "%[^\n]\n", string);
	}
	fclose(ptrArq);
}

int main(void) {
	telacheia();
	Sleep(1000);
	TpBancoDeDados *pontBd;
	int y;
	char palavra[30], comandosql[600], string1[200], string2[200], string3[200];
	createDatabase(&pontBd);
	y = mostraDados(pontBd);
	gotoxy(3, y);
	printf("Comando SQL: ");
	gets(comandosql);
	while(strcmp(comandosql, "-1") != 0) {
		gotoxy(3, y + 1);
		if (teste(comandosql, "INSERT INTO"))
			inserir(&pontBd->pTabelas, comandosql);
		if (teste(comandosql, "SELECT"))
			mostraSelecionado(pontBd, comandosql);
		if(teste(comandosql, "DELETE"))
			deletar(&pontBd->pTabelas, comandosql);
		if(teste(comandosql, "UPDATE"))
			alterar(&pontBd->pTabelas, comandosql);
		y = mostraDados(pontBd);
		gotoxy(3, y);
		printf("Comando SQL: ");
		gets(comandosql);
	}
	return 0;
}
