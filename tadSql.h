union unionDados{
	int i;
	float n;
		char c, t[20], d[10];
};
typedef union unionDados UnionDados;

struct tpDado {
	union unionDados valor;
	struct tpDado *prox;
};
typedef struct tpDado TpDado;

struct tpColuna {
	struct tpColuna *prox, *fk;
	char nome[20], tipo, pk;
	TpDado *pAtual, *pDados;
};
typedef struct tpColuna TpColuna;

struct tpTabela {
	struct TpTabela *ant, *prox;
	TpColuna *pCampos;
	char nome[20]; 
};
typedef struct tpTabela TpTabela;

struct tpBanco {
	char nome[20];
	TpTabela *pTabelas;
};
typedef struct tpBanco TpBancoDeDados;

int teste(char string1[100], char string2[30]) { // Função semelhante ao strstr 
    int i, j;

    for (i = 0; string1[i] != '\0'; i++) {
        j = 0;

        while (string1[i + j] == string2[j]) {
            j++;

            if (string2[j] == '\0') {
                return 1;
            }
        }
    }

    return 0;
}

void retornaPalavra(char string[], int index, char palavra[]) {
	int i = 0, len, indexWord = 1, iPalavra = 0;
	char newPalavra[30];
	len = strlen(string);
	
	while(i < len) {
		if(string[i] == ' ')
			indexWord++;
		
			
		if(indexWord == index) {
			if(string[i] != 40 && string[i] != 41 && string[i] >= 65 && string[i] <= 90 || string[i] >= 97 && string[i] <= 122 || isdigit(string[i]) || string[i] == 95 || string[i] == 45 || string[i] == 47) {
				newPalavra[iPalavra] = string[i];
				iPalavra++;
			}
		}
		i++;
	}
	newPalavra[iPalavra] = '\0';
	strcpy(palavra, newPalavra);
	if (indexWord < index)
		strcpy(palavra, "-404");
}


void defineFk(TpBancoDeDados *pBanco, char string[], char string2[]) {
	TpColuna *novoCampo;
	TpTabela *tabelaAdicionar = pBanco->pTabelas;
	TpTabela *tabelaFk = pBanco->pTabelas;
	
	char palavra[30];
	retornaPalavra(string, 3, palavra);
	while(strcmp(tabelaAdicionar->nome, palavra) != 0) // Na tabela que será adicionada a FK
		tabelaAdicionar = tabelaAdicionar->prox;
		
	TpColuna *aux = tabelaAdicionar->pCampos; // Campo FK
	retornaPalavra(string2, 3, palavra);
	while(strcmp(aux->nome, palavra) != 0)
		aux = aux->prox;

	retornaPalavra(string2, 5, palavra);
	while(strcmp(tabelaFk->nome, palavra) != 0) // Na tabela que está a FK
		tabelaFk = tabelaFk->prox;
	TpColuna *FK = tabelaFk->pCampos;
	retornaPalavra(string2, 6, palavra);
	while (strcmp(FK->nome, palavra) != 0) { // Campo PK
		FK = FK->prox; 
	}
	aux->fk = FK;
}

void definePk(TpTabela **pTabela, char string[]) {
	TpColuna *aux = (*pTabela)->pCampos;
	char pk[30];
	retornaPalavra(string, 5, pk);
	while(strcmp(aux->nome,pk) != 0)
		aux = aux->prox;
	aux->pk = 'S';
}

TpBancoDeDados *newDatabase(char name[]) {
	TpBancoDeDados *banco;
	banco = (TpBancoDeDados *)malloc(sizeof(TpBancoDeDados));
	
	strcpy(banco->nome, name);
	banco->pTabelas = NULL;
	
	return banco;
}

TpTabela *newTable(TpTabela **pTabelas, char name[]) {
	TpTabela *novaTabela;
	TpTabela *aux = *pTabelas;
	novaTabela = (TpTabela *)malloc(sizeof(TpTabela));
	
	strcpy(novaTabela->nome, name);
	novaTabela->pCampos = NULL;
	novaTabela->prox = novaTabela->ant = NULL;
	
	if (*pTabelas == NULL) {
		*pTabelas = novaTabela;
	} 
	else {
		while (aux->prox != NULL) 
			aux = aux->prox;
		aux->prox = novaTabela;
		novaTabela->ant = aux;
	}
	
	return novaTabela;
}

void mostraTudo(TpBancoDeDados *pBanco) {
	TpTabela *aux = pBanco->pTabelas;
	
	printf("%s\n\n", pBanco->nome);
	while(aux) {
		printf("%s\n", aux->nome);
		TpColuna *aux2 = aux->pCampos;
		while(aux2) {
			if(!aux2->fk)
				printf("%s - Tipo: %c - PK: '%c'\n", aux2->nome, aux2->tipo, aux2->pk);
			else
				printf("%s - FK aponta %s\n", aux2->nome, aux2->fk->nome);
			aux2 = aux2->prox;
		}
		aux = aux->prox;
		printf("\n");
	}
}

void retornaTipo(char string[], int index, char palavra[]) {
	int i = 0, len, indexWord = 1, iPalavra = 0;
	char newPalavra[30];
	len = strlen(string);
	
	while(i < len) {
		if(string[i] == ' ')
			indexWord++;
		
			
		if(indexWord == index) {
			if(string[i] >= 65 && string[i] <= 90 || string[i] >= 97 && string[i] <= 122 || isdigit(string[i]) || string[i] == 95 || string[i] == 45 || string[i] == 40 || string[i] == 41 ) {
				newPalavra[iPalavra] = string[i];
				iPalavra++;
			}
			if(string[i] == '/') {
				newPalavra[iPalavra] = string[i];
				iPalavra++;
			}
		}
		
		i++;
	}
	newPalavra[iPalavra] = '\0';
	strcpy(palavra, newPalavra);	
}

void newDado(TpDado **pDado, char tipo, UnionDados dado[20]) {
	TpDado *novoDado;
	TpDado *aux = *pDado;
	novoDado = (TpDado*)malloc(sizeof(TpDado));
	novoDado->prox = NULL;
	switch(tipo) {
		case 'T':
            strcpy(novoDado->valor.t, dado);
            break;
        case 'D':
            strcpy(novoDado->valor.d, dado);
            break;
        case 'C':
            novoDado->valor.c = dado;
            break;
        case 'I':
            novoDado->valor.i = atoi(dado);
            break;
        case 'N':
            novoDado->valor.n = atof(dado);
            break;
	}
	if(*pDado == NULL)
		*pDado = novoDado;
	else {
		while(aux->prox)
			aux = aux->prox;
		aux->prox = novoDado;
	}
}

void newCampo(TpColuna **pCampos, char string[]) {
	TpColuna *novoCampo;
	TpColuna *aux;
	char palavra[30];
	
	novoCampo = (TpColuna*)malloc(sizeof(TpColuna));
	aux = *pCampos;
	
	retornaPalavra(string, 1, palavra);
	
	strcpy(novoCampo->nome, palavra);
	novoCampo->prox = NULL;
	novoCampo->fk = NULL;
	novoCampo->pk = 'N';
	novoCampo->pDados = NULL;
	novoCampo->pAtual = NULL;
	retornaTipo(string, 2, palavra);
	if (strcmp(palavra,"INTEGER") == 0) {
		novoCampo->tipo = 'I';
	} 
	else if (stricmp(palavra,"NUMERIC") == 0) {
		novoCampo->tipo = 'N';
	}
	else if (stricmp(palavra,"DATE") == 0) {
		novoCampo->tipo = 'D';
	}
	else if (stricmp(palavra,"CHARACTER(1)") == 0) {
		novoCampo->tipo = 'C';
	}
	else if (stricmp(palavra,"CHARACTER(20)") == 0) {
		novoCampo->tipo = 'T';
	}
	
	if (*pCampos == NULL) {
		*pCampos = novoCampo;
	}
	else {
		while (aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novoCampo;
	}
}

void inserir(TpTabela **pTabelas, char string[]) {
	getch();
	char string2[100], campo[20], dado[20], tabela[20];
	gets(string2);
	if(teste(string, "INSERT INTO")) {
		int i = 4;
		retornaPalavra(string, i, campo);
		while(strcmp(campo,"-404") != 0) {
			retornaPalavra(string, 3, tabela);
			TpTabela *aux = *pTabelas;
			while(strcmp(aux->nome, tabela) != 0) {
				aux = aux->prox;
			}
			TpColuna *auxCampos = aux->pCampos;
			while(strcmp(auxCampos->nome, campo) != 0) {
				auxCampos = auxCampos->prox;
			}
			retornaPalavra(string2, i - 2, dado);
			newDado(&auxCampos->pDados, auxCampos->tipo, dado);
			i++;
			retornaPalavra(string, i, campo);
		}
	}
}

int mostraDados(TpBancoDeDados *pBanco) {
	int x = 3, y = 2, qtdeTab = 0, qtdeDados = 0;
	TpTabela *auxTab = pBanco->pTabelas;
	system("cls");
	while(auxTab) {
		x = 3;
		y = (qtdeTab + qtdeDados) + 1;
		gotoxy(x, y);
		printf("Tabela: %s", auxTab->nome);
		TpColuna *auxCol = auxTab->pCampos;
		while(auxCol) {
			y = (qtdeTab + qtdeDados) + 2;
			gotoxy(x, y);
			if(auxCol->fk != NULL)
				printf("%s (FK)(%c)", auxCol->nome, auxCol->tipo);
			else if (auxCol->pk == 'S')
				printf("%s (PK)(%c)", auxCol->nome, auxCol->tipo);
				else
					printf("%s (%c)", auxCol->nome, auxCol->tipo);
			TpDado *auxDado = auxCol->pDados;
			while(auxDado) {
				y++;
				gotoxy(x, y);
				switch(auxCol->tipo) {
					case 'T':
			            printf("%s", auxDado->valor.t);
			            break;
			        case 'D':
			            printf("%s", auxDado->valor.d);
			            break;
			        case 'C':
			            printf("%c", auxDado->valor.c);
			            break;
			        case 'I':
			            printf("%d", auxDado->valor.i);
			            break;
			        case 'N':
			            printf("%.2f", auxDado->valor.n);
			            break;	
				}
				if(!auxCol->prox)
					qtdeDados++;
				auxDado = auxDado->prox;
			}
			
			x += strlen(auxCol->nome) + 12;
			auxCol = auxCol->prox;
		}
		qtdeDados += 2;
		qtdeTab++;
		auxTab = auxTab->prox;
		x = 3;
		y += 4;
	}
	return y;
}

void deletar(TpTabela **pTabela, char string1[]) {
	int i, j;
	float valorF;
	int valorI;
	char string2[100], palavra[30], condicao_campo[30], condicao_valor[10];
	TpColuna *auxCampos;
	TpDado *auxDados, *deletar, *anterior;
	gets(string2);
	
	TpTabela *aux = *pTabela;
	retornaPalavra(string1, 3, palavra);
	while(strcmp(aux->nome, palavra) != 0)
		aux = aux->prox;
	retornaPalavra(string2, 2, condicao_campo);
	retornaPalavra(string2, 4, condicao_valor);
	auxCampos = aux->pCampos;
	while(strcmp(auxCampos->nome, condicao_campo) != 0)
		auxCampos = auxCampos->prox;
	auxDados = auxCampos->pDados;
	i = 0;
	if(auxCampos->tipo == 'T')
		while(auxDados != NULL && strcmp(auxDados->valor.t, condicao_valor) != 0) {
			auxDados = auxDados->prox;
			i++;
		}
	else if(auxCampos->tipo == 'D')
		while(auxDados != NULL && strcmp(auxDados->valor.d, condicao_valor) != 0) {
			auxDados = auxDados->prox;
			i++;
		}
		else {
			if(auxCampos->tipo == 'C')
				while(auxDados != NULL && auxDados->valor.c != condicao_valor) {
					auxDados = auxDados->prox;
					i++;
				}
		else {
			if(auxCampos->tipo == 'N') {
				valorF = atof(condicao_valor);
				while(auxDados != NULL && auxDados->valor.n != valorF) {
					auxDados = auxDados->prox;
					i++;
				}
			}
			else {
				valorI = atoi(condicao_valor);
				while(auxDados->prox != NULL && auxDados->valor.i != valorI) {
					auxDados = auxDados->prox;
					i++;
				}
			}
		}
	}
	if(auxDados != NULL) {
		auxCampos = aux->pCampos;
		while(auxCampos != NULL) {
			auxDados = auxCampos->pDados;

			for(j = 0; j < i; j++) {
				anterior = auxDados;
				auxDados = auxDados->prox;	
			}
			printf("\n\n%d\n",i);
			getch();
			if (i == 0) {
				deletar = auxDados;
				
				auxCampos->pDados = auxDados->prox;
				free(deletar);
			}
			else {
				if(auxDados->prox == NULL) {
					deletar = auxDados;
					anterior->prox = NULL;
					free(deletar);
				}
				else {
					deletar = auxDados;
					anterior->prox = auxDados->prox;
					free(deletar);
				}
			}
			auxCampos = auxCampos->prox;
		}
	}
}

int mostraSelecionado(TpBancoDeDados *pBanco, char string[]) {
	int x = 3, y = 2, string2[100], qtdeTab = 0, qtdeDados = 0;
	gets(string2);
	TpTabela *auxTab = pBanco->pTabelas;
	system("cls");
	while(auxTab) {
		x = 3;
		y = (qtdeTab + qtdeDados) + 1;
		gotoxy(x, y);
		if(teste(string2, auxTab->nome))
			textcolor(GREEN);
		else
			textcolor(WHITE);
		printf("Tabela: %s", auxTab->nome);
		textcolor(WHITE);                  
		TpColuna *auxCol = auxTab->pCampos;
		while(auxCol) {
			y = (qtdeTab + qtdeDados) + 2;
			gotoxy(x, y);
			if(teste(string, auxCol->nome) && teste(string2, auxTab->nome) || teste(string, "*") && teste(string2, auxTab->nome))
				textcolor(GREEN);
			else
				textcolor(WHITE);
			if(auxCol->fk != NULL)
				printf("%s (FK)(%c)", auxCol->nome, auxCol->tipo);
			else if (auxCol->pk == 'S')
				printf("%s (PK)(%c)", auxCol->nome, auxCol->tipo);
				else
					printf("%s (%c)", auxCol->nome, auxCol->tipo);
			TpDado *auxDado = auxCol->pDados;
			while(auxDado) {
				y++;
				gotoxy(x, y);
				switch(auxCol->tipo) {
					case 'T':
			            printf("%s", auxDado->valor.t);
			            break;
			        case 'D':
			            printf("%s", auxDado->valor.d);
			            break;
			        case 'C':
			            printf("%c", auxDado->valor.c);
			            break;
			        case 'I':
			            printf("%d", auxDado->valor.i);
			            break;
			        case 'N':
			            printf("%.2f", auxDado->valor.n);
			            break;	
				}
				if(!auxCol->prox)
					qtdeDados++;
				auxDado = auxDado->prox;
			}
			
			x += strlen(auxCol->nome) + 12;
			auxCol = auxCol->prox;
		}
		qtdeDados += 2;
		qtdeTab++;
		auxTab = auxTab->prox;
		x = 3;
		y += 4;
	}
	getch();
	return y;
}

void alterar(TpTabela **pTabela, char string1[]) {
	float valorF;
	int valorI, j;
	TpTabela *aux;
	TpColuna *auxCampos;
	TpDado *auxDados;
	int i, qtde = 0;
	char string2[100], string3[100], palavra[30], condicao_coluna[30], condicao_valor[20], coluna[30], valor_coluna[20];
	gets(string2);
	gets(string3);
	retornaPalavra(string1, 2, palavra);
	aux = *pTabela;
	while(aux->prox != NULL && strcmp(aux->nome, palavra) != 0)
		aux = aux->prox;
	retornaPalavra(string3, 2, condicao_coluna);
	retornaPalavra(string3, 4, condicao_valor);
	
	auxCampos = aux->pCampos;
	while(auxCampos != NULL && strcmp(auxCampos->nome, condicao_coluna) != 0)
		auxCampos = auxCampos->prox;
	auxDados = auxCampos->pDados;
	if(auxCampos->tipo == 'T') {
		while(auxDados->prox != NULL && strcmp(auxDados->valor.t, condicao_valor) != 0) {
			auxDados = auxDados->prox;
			qtde++;
		}
	}
	if (auxCampos->tipo == 'D') {
		while(auxDados->prox != NULL && strcmp(auxDados->valor.d, condicao_valor) != 0) {
			auxDados = auxDados->prox;
			qtde++;
		}
	}
	getch();
	if (auxCampos->tipo == 'N') {
		valorF = atof(condicao_valor);
		while(auxDados->prox != NULL && auxDados->valor.n != valorF) {
			auxDados = auxDados->prox;
			qtde++;
		}
	}
	if (auxCampos->tipo == 'I') {
		valorI = atoi(condicao_valor);
		while(auxDados->prox != NULL && auxDados->valor.n != valorI) {
			auxDados = auxDados->prox;
			qtde++;
		}
	}
	if (auxCampos->tipo == 'C') {
		while(auxDados->prox != NULL && auxDados->valor.c != condicao_valor) {
			auxDados = auxDados->prox;
			qtde++;
		}
	}

	auxCampos = aux->pCampos;
	i = 2;
	retornaPalavra(string2, i, coluna);
	retornaPalavra(string2, i + 2, valor_coluna);
	while(auxCampos != NULL && stricmp(coluna, "-404") != 0) {
		if(strcmp(auxCampos->nome, coluna) == 0) {
			auxDados = auxCampos->pDados;
			for(j = 0; j < qtde; j++)
				auxDados = auxDados->prox;
			if(auxCampos->tipo == 'T') {
				strcpy(auxDados->valor.t, valor_coluna);
			}
			if (auxCampos->tipo == 'D') {
				strcpy(auxDados->valor.d, valor_coluna);
			}
			if (auxCampos->tipo == 'N') {
				valorF = atof(valor_coluna);
				auxDados->valor.n = valorF;
			}
			if (auxCampos->tipo == 'I') {
				valorI = atoi(valor_coluna);
				auxDados->valor.i = valorI;
			}
			if (auxCampos->tipo == 'C') {
				auxDados->valor.c = valor_coluna;
			}
			i += 3;
			retornaTipo(string2, i, coluna);
			retornaTipo(string2, i + 2, valor_coluna);
		}
		auxCampos = auxCampos->prox;
	}
}
