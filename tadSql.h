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
		
	TpColuna *aux = tabelaAdicionar->pCampos;
	
	retornaPalavra(string2, 5, palavra);
	while(strcmp(tabelaFk->nome, palavra) != 0) // Na tabela que está a FK
		tabelaFk = tabelaFk->prox;
	
	TpColuna *FK = tabelaFk->pCampos; // Campos da tabela que tem a FK
	retornaPalavra(string2, 3, palavra);
	while (strcmp(FK->nome, palavra) != 0) {
		FK = FK->prox; 
	}
	
	novoCampo = (TpColuna*)malloc(sizeof(TpColuna));
	retornaPalavra(string, 6, palavra);
	strcpy(novoCampo->nome, palavra); // Nome da FK na tabela nova
	novoCampo->prox = NULL;
	novoCampo->fk = FK; // FK apontada
	novoCampo->pk = 'N';
	novoCampo->tipo = FK->tipo;
	novoCampo->pDados = NULL;
	
	while (aux->prox != NULL)
		aux = aux->prox;
	aux->prox = novoCampo;
}

void definePk(TpTabela **pTabela, char string[]) {
	TpColuna *aux = &(*pTabela)->pCampos;
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
	if(strstr(string, "INSERT INTO")) {
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
			printf("%s", auxCol->nome);
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
