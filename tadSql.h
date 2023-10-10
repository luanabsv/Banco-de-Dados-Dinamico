union unionDados{
	int i;
	float n;
	char c, t[20], d[11];
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
	struct tpTabela *ant, *prox;
	TpColuna *pCampos;
	char nome[20]; 
};
typedef struct tpTabela TpTabela;

struct tpBanco {
	char nome[20];
	TpTabela *pTabelas;
};
typedef struct tpBanco TpBancoDeDados;

struct tpString {
	char string[100];
	struct tpString *prox;
};
typedef struct tpString TpString;

int teste(char string[], char substring[]) {
	int i = 0, y, j;
	char c, subaux[strlen(substring)];
	while(string[i] != '\0') {
		for (y = 0, j = i; y < strlen(substring); y++, j++)
			subaux[y] = string[j];
		subaux[y] = '\0';
		if(strcmp(subaux, substring) == 0)
			return 1;
		i++;
	}
	return 0;
}

void retornaDado(char string[], int index, char palavra[]) {
	int i = 0, len, indexWord = 1, iPalavra = 0;
	char newPalavra[30];
	len = strlen(string);
	
	while(i < len) {
		if(string[i] == '(' || string[i] == ',')
			indexWord++;
		
			
		if(indexWord == index) {
			if(string[i] != 40 && string[i] != 41 && string[i] >= 65 && string[i] <= 90 || string[i] >= 97 && string[i] <= 122 || isdigit(string[i]) || string[i] == 95 || string[i] == 45 || string[i] == 47 || string[i] == ' ' || string[i] == ':' || string[i] == '-' || string[i] == '.' || string[i] == '@') {
				newPalavra[iPalavra] = string[i];
				iPalavra++;
			}
		}
		i++;
	}
	newPalavra[iPalavra] = '\0';
	if (index != 2) {
		for(i = 0; i < strlen(newPalavra); i++)
			newPalavra[i] = newPalavra[i + 1];
		newPalavra[iPalavra] = '\0';
	}
	strcpy(palavra, newPalavra);
	if (indexWord < index) {
		strcpy(palavra, "-404");
	}
}

void retornaPalavra(char string[], int index, char palavra[]) {
	int i = 0, len, indexWord = 1, iPalavra = 0;
	char newPalavra[30];
	len = strlen(string);
	
	while(string[i] != '\0') {
		if(string[i] == ' ')
			indexWord++;
		
			
		if(indexWord == index) {
			if(string[i] != 40 && string[i] != 41 && string[i] >= 65 && string[i] <= 90 || string[i] >= 97 && string[i] <= 122 || isdigit(string[i]) || string[i] == 95 || string[i] == 45 || string[i] == 47 || string[i] == '_') {
				newPalavra[iPalavra] = string[i];
				iPalavra++;
			}
		}
		i++;
	}
	newPalavra[iPalavra] = '\0';
	strcpy(palavra, newPalavra);
	if (indexWord < index) {
		strcpy(palavra, "-404");
	}
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
			if(string[i] >= 65 && string[i] <= 90 || string[i] >= 97 && string[i] <= 122 || isdigit(string[i]) || string[i] == 95 || string[i] == 45 || string[i] == 40 || string[i] == 41 || string[i] == '(' || string[i] == ')' || string[i] == ',') {
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

void newDado(TpDado **pDado, char tipo, char dado[30]) {
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
        	novoDado->valor.c = dado[0];
            break;
        case 'I':
            novoDado->valor.i = atoi(dado);
            break;
        case 'N':
            novoDado->valor.n = atof(dado);
            break;
	}
	if(*pDado == NULL) {
		*pDado = novoDado;
	}	
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
	novoCampo->pDados = novoCampo->pAtual = NULL;
	retornaTipo(string, 2, palavra);
	if (strcmp(palavra,"INTEGER") == 0) {
		novoCampo->tipo = 'I';
	} 
	else if (stricmp(palavra,"NUMERIC(6,2)") == 0) {
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

void quebrainsert(char comando[200], char insert[100], char values[100]) {
    int i = 0, j, y, indexpalavra = 0;
    char aux[6], c;
    strcpy(aux, " ");
    while (comando[i] != '\0' && strcmp(aux, "values") != 0) {
        for (j = i, y = 0; y < 6; y++, j++)
            aux[y] = comando[j];
        insert[i] = comando[i];
       	i++;
    }
    i -= 2;
    insert[i] = '\0';
    i++;
    while (comando[i] != '\0' && comando[i] != ';') {
        values[indexpalavra] = comando[i];
        indexpalavra++;
        i++;
    }
    values[indexpalavra] = '\0';
}

void quebradelete(char comando[200], char deletar[100], char where[100]) {
    int i = 0, j, y, indexpalavra = 0;
    char aux[5], c;
    strcpy(aux, " ");
    while (comando[i] != '\0' && strcmp(aux, "WHERE") != 0) {
        for (j = i, y = 0; y < 5; y++, j++)
            aux[y] = comando[j];
        deletar[i] = comando[i];
       	i++;
    }
    i -= 2;
    deletar[i] = '\0';
    i++;
    while (comando[i] != '\0' && comando[i] != ';') {
        where[indexpalavra] = comando[i];
        indexpalavra++;
        i++;
    }
    where[indexpalavra] = '\0';
}

void inserir(TpTabela **pTabelas, char comandosql[]) {
	char string2[200], campo[20], dado[20], tabela[20], string[200];
	quebrainsert(comandosql, string, string2);
	int i = 4;
	strcpy(campo," ");
	printf("\n\n");
	retornaPalavra(string, 3, tabela);
	retornaPalavra(string, i, campo);
	while(strcmp(campo,"-404") != 0) {
		TpTabela *aux = *pTabelas;
		while(strcmp(aux->nome, tabela) != 0) {
			aux = aux->prox;
		}
		TpColuna *auxCampos = aux->pCampos;
		while(strcmp(auxCampos->nome, campo) != 0) {
			auxCampos = auxCampos->prox;
		}
		retornaDado(string2, i - 2, dado);
		newDado(&auxCampos->pDados, auxCampos->tipo, dado);
		auxCampos->pAtual = auxCampos->pDados;
		i++;
		retornaPalavra(string, i, campo);
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
		printf("%s", auxTab->nome);
		TpColuna *auxCol = auxTab->pCampos;
		while(auxCol) {
			y = (qtdeTab + qtdeDados) + 3;
			gotoxy(x, y);
			retangulo(x - 1, y - 1, strlen(auxCol->nome) + 16, 1);
			gotoxy(x, y);
			if(auxCol->fk != NULL)
				printf(" %s (FK)(%c)", auxCol->nome, auxCol->tipo);
			else if (auxCol->pk == 'S')
				printf(" %s (PK)(%c)", auxCol->nome, auxCol->tipo);
				else
					printf(" %s (%c)", auxCol->nome, auxCol->tipo);
			TpDado *auxDado = auxCol->pDados;
			while(auxDado) {
				y += 2;
				gotoxy(x, y);
				retangulo(x - 1, y - 1, strlen(auxCol->nome) + 16, 1);
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
					qtdeDados += 2;
				auxDado = auxDado->prox;
			}
			
			x += strlen(auxCol->nome) + 12;
			auxCol = auxCol->prox;
		}
		qtdeDados += 4;
		qtdeTab++;
		auxTab = auxTab->prox;
	}
	
	y+=3;
	return y;
}

void deletar(TpTabela **pTabela, char comandosql[]) {
	int i, j;
	float valorF;
	int valorI;
	char deletarS[100], whereS[100], palavra[30], condicao_campo[30], condicao_valor[10];
	TpColuna *auxCampos;
	TpDado *auxDados, *deletar, *anterior;
	quebradelete(comandosql, deletarS, whereS);
	TpTabela *aux = *pTabela;
	retornaPalavra(deletarS, 3, palavra);
	while(strcmp(aux->nome, palavra) != 0)
		aux = aux->prox;
	retornaPalavra(whereS, 2, condicao_campo);
	retornaPalavra(whereS, 4, condicao_valor);
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
				while(auxDados != NULL && auxDados->valor.i != valorI) {
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

void quebraselect(char comando[200], char select[100], char from[100], char where[100]) {
    int i = 0, j, y, x, indexpalavra = 0;
    char aux[6], c;
    strcpy(aux, " ");
    while (comando[i] != '\0' && strcmp(aux, "FROM") != 0) {
        for (j = i, y = 0; y < 4; y++, j++)
            aux[y] = comando[j];
        aux[y] = '\0';
        select[i] = comando[i];
       	i++;
    }
    i -= 1;
    select[i] = '\0';
    x = 0;
    while (comando[i] != '\0' && strcmp(aux, "WHERE") != 0) {
        for (j = i, y = 0; y < 5; y++, j++)
            aux[y] = comando[j];
        aux[y] = '\0';
        from[x] = comando[i];
       	i++;
       	x++;
    }
    from[x] = '\0';
    x = 0;
    i -= 1;
    while (comando[i] != '\0') {
        for (j = i, y = 0; y < 5; y++, j++)
            aux[y] = comando[j];
        aux[y] = '\0';
        where[x] = comando[i];
       	i++;
       	x++;
    }
    i -= 1;
    where[x] = '\0';
}

int isInside(char string[], TpString *listaString) {
	while(listaString->prox && strcmp(string, listaString->string) != 0) {
		listaString = listaString->prox;
	}
	if (strcmp(string, listaString->string) == 0)
		return 1;
	return 0;
}

int mostraSelecionado(TpBancoDeDados *pBanco, char comandosql[]) {
	int x = 3, y = 2, select[200], from[200], where[200], qtdeTab = 0, qtdeDados = 0, minI, maxI, valorC;
	float minF, maxF;
	quebraselect(comandosql, select, from, where);
	TpString *listaSelect = NULL, *listaFrom = NULL;
	TpTabela *auxTab = pBanco->pTabelas;
	TpColuna *auxBet = auxTab->pCampos;
	TpDado *auxBetC = auxBet->pDados;
	system("cls");
	char aux[100], campoBet[20];
	int i = 2;
	TpString *novaCaixa, *auxLista;
	retornaPalavra(select, i, aux);
	while(strcmp(aux, "-404") != 0) {
		novaCaixa = (TpString*)malloc(sizeof(TpString));
		novaCaixa->prox = NULL;
		strcpy(novaCaixa->string, aux);
		if (listaSelect == NULL)
			listaSelect = novaCaixa;
		else {
			auxLista = listaSelect;
			while (auxLista->prox != NULL)
				auxLista = auxLista->prox;
			auxLista->prox = novaCaixa;
		}
		i++;
		retornaPalavra(select, i, aux);
	}
	i = 2;
	retornaPalavra(from, i, aux);
	while(strcmp(aux, "-404") != 0) {
		novaCaixa = (TpString*)malloc(sizeof(TpString));
		novaCaixa->prox = NULL;
		strcpy(novaCaixa->string, aux);
		if (listaFrom == NULL)
			listaFrom = novaCaixa;
		else {
			auxLista = listaFrom;
			while (auxLista->prox != NULL)
				auxLista = auxLista->prox;
			auxLista->prox = novaCaixa;
		}
		i++;
		retornaPalavra(from, i, aux);
	}
	if (strcmp(where, ";") == 0)
		while(auxTab) {
			x = 3;
			y = (qtdeTab + qtdeDados) + 1;
			gotoxy(x, y);
			if(isInside(auxTab->nome, listaFrom))
				textcolor(CYAN);
			else
				textcolor(WHITE);
			printf("%s", auxTab->nome);
			textcolor(WHITE);                  
			TpColuna *auxCol = auxTab->pCampos;
			while(auxCol) {
				y = (qtdeTab + qtdeDados) + 3;
				gotoxy(x, y);
				if(isInside(auxCol->nome, listaSelect) && isInside(auxTab->nome, listaFrom) || teste(select, "*") && isInside(auxTab->nome, listaFrom))
					textcolor(CYAN);
				else
					textcolor(WHITE);
				retangulo(x - 1, y - 1, strlen(auxCol->nome) + 16, 1);
					gotoxy(x, y);
				if(auxCol->fk != NULL)
					printf("%s (FK)(%c)", auxCol->nome, auxCol->tipo);
				else if (auxCol->pk == 'S')
					printf("%s (PK)(%c)", auxCol->nome, auxCol->tipo);
					else
						printf("%s (%c)", auxCol->nome, auxCol->tipo);
				TpDado *auxDado = auxCol->pDados;
				while(auxDado) {
					y+=2;
					gotoxy(x, y);
					retangulo(x - 1, y - 1, strlen(auxCol->nome) + 16, 1);
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
						qtdeDados+=2;
					auxDado = auxDado->prox;
				}
				
				x += strlen(auxCol->nome) + 12;
				auxCol = auxCol->prox;
			}
			qtdeDados += 4;
			qtdeTab++;
			auxTab = auxTab->prox;
		}
	else {
		if (teste(where, "BETWEEN")){
			auxTab = pBanco->pTabelas;
			retornaPalavra(from, 2, aux);
			while(strcmp(auxTab->nome, aux) != 0)
				auxTab = auxTab->prox;
			auxBet = auxTab->pCampos;
			retornaPalavra(where, 2, campoBet);
			while(strcmp(auxBet->nome, campoBet) != 0)
				auxBet = auxBet->prox;
			if(auxBet->tipo == 'I') {
				retornaPalavra(where, 4, aux);
				minI = atoi(aux);
				retornaPalavra(where, 6, aux);
				maxI = atoi(aux);
				auxTab = pBanco->pTabelas;
				while(auxTab) {
					x = 3;
					y = (qtdeTab + qtdeDados) + 1;
					gotoxy(x, y);
					if(isInside(auxTab->nome, listaFrom))
						textcolor(CYAN);
					else
						textcolor(WHITE);
					printf("%s", auxTab->nome);
					textcolor(WHITE);                  
					TpColuna *auxCol = auxTab->pCampos;
					while(auxCol) {
						auxBetC = auxBet->pDados;
						y = (qtdeTab + qtdeDados) + 3;
						gotoxy(x, y);
						if(isInside(auxCol->nome, listaSelect) && isInside(auxTab->nome, listaFrom) || teste(select, "*") && isInside(auxTab->nome, listaFrom))
							textcolor(CYAN);
						else
							textcolor(WHITE);
						retangulo(x - 1, y - 1, strlen(auxCol->nome) + 16, 1);
							gotoxy(x, y);
						if(auxCol->fk != NULL)
							printf("%s (FK)(%c)", auxCol->nome, auxCol->tipo);
						else if (auxCol->pk == 'S')
							printf("%s (PK)(%c)", auxCol->nome, auxCol->tipo);
							else
								printf("%s (%c)", auxCol->nome, auxCol->tipo);
						TpDado *auxDado = auxCol->pDados;
						while(auxDado) {
							if(isInside(auxCol->nome, listaSelect) && isInside(auxTab->nome, listaFrom) && auxBetC->valor.i >= minI && auxBetC->valor.i <= maxI || isInside(auxTab->nome, listaFrom) && strcmp(select, "SELECT * ") == 0 && auxBetC->valor.i >= minI && auxBetC->valor.i <= maxI)
								textcolor(CYAN);
							else
								textcolor(WHITE);
							y+=2;
							gotoxy(x, y);
							retangulo(x - 1, y - 1, strlen(auxCol->nome) + 16, 1);
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
							textcolor(WHITE);
							if(!auxCol->prox)
								qtdeDados+=2;
							auxDado = auxDado->prox;
							if(auxBetC != NULL)
								auxBetC = auxBetC->prox;
						}
						x += strlen(auxCol->nome) + 12;
						auxCol = auxCol->prox;
					}
					qtdeDados += 4;
					qtdeTab++;
					auxTab = auxTab->prox;
				}
			}
			else {
				retornaPalavra(where, 4, aux);
				minF = atof(aux);
				retornaPalavra(where, 6, aux);
				maxF = atof(aux);
				auxTab = pBanco->pTabelas;
				while(auxTab) {
					x = 3;
					y = (qtdeTab + qtdeDados) + 1;
					gotoxy(x, y);
					if(isInside(auxTab->nome, listaFrom))
						textcolor(CYAN);
					else
						textcolor(WHITE);
					printf("%s", auxTab->nome);
					textcolor(WHITE);                  
					TpColuna *auxCol = auxTab->pCampos;
					while(auxCol) {
						auxBetC = auxBet->pDados;
						y = (qtdeTab + qtdeDados) + 3;
						gotoxy(x, y);
						if(isInside(auxCol->nome, listaSelect) && isInside(auxTab->nome, listaFrom) || teste(select, "*") && isInside(auxTab->nome, listaFrom))
							textcolor(CYAN);
						else
							textcolor(WHITE);
						retangulo(x - 1, y - 1, strlen(auxCol->nome) + 16, 1);
						gotoxy(x, y);
						if(auxCol->fk != NULL)
							printf("%s (FK)(%c)", auxCol->nome, auxCol->tipo);
						else if (auxCol->pk == 'S')
							printf("%s (PK)(%c)", auxCol->nome, auxCol->tipo);
							else
								printf("%s (%c)", auxCol->nome, auxCol->tipo);
						TpDado *auxDado = auxCol->pDados;
						while(auxDado) {
							if(isInside(auxCol->nome, listaSelect) && isInside(auxTab->nome, listaFrom) && auxBetC->valor.n >= minF && auxBetC->valor.n <= maxF || isInside(auxTab->nome, listaFrom) && strcmp(select, "SELECT * ") == 0 && auxBetC->valor.n >= minF && auxBetC->valor.n <= maxF)
								textcolor(CYAN);
							else
								textcolor(WHITE);
							y+=2;
							gotoxy(x, y);
							retangulo(x - 1, y - 1, strlen(auxCol->nome) + 16, 1);
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
							textcolor(WHITE);
							if(!auxCol->prox)
								qtdeDados+=2;
							auxDado = auxDado->prox;
							if(auxBetC != NULL) 
								auxBetC = auxBetC->prox;
						}
						x += strlen(auxCol->nome) + 12;
						auxCol = auxCol->prox;
					}
					qtdeDados += 4;
					qtdeTab++;
					auxTab = auxTab->prox;
				}
			}
		}
		else {
			auxTab = pBanco->pTabelas;
			retornaPalavra(from, 2, aux);
			while(strcmp(auxTab->nome, aux) != 0)
				auxTab = auxTab->prox;
			auxBet = auxTab->pCampos;
			retornaPalavra(where, 2, campoBet);
			while(strcmp(auxBet->nome, campoBet) != 0)
				auxBet = auxBet->prox;
			auxTab = pBanco->pTabelas;
			if (auxBet->tipo == 'I') {
				retornaPalavra(where, 4, aux);
				valorC = atoi(aux);
				while(auxTab) {
					x = 3;
					y = (qtdeTab + qtdeDados) + 1;
					gotoxy(x, y);
					if(isInside(auxTab->nome, listaFrom))
						textcolor(CYAN);
					else
						textcolor(WHITE);
					printf("%s", auxTab->nome);
					textcolor(WHITE);                  
					TpColuna *auxCol = auxTab->pCampos;
					while(auxCol) {
						auxBetC = auxBet->pDados;
						y = (qtdeTab + qtdeDados) + 3;
						gotoxy(x, y);
						if(isInside(auxCol->nome, listaSelect) && isInside(auxTab->nome, listaFrom) || teste(select, "*") && isInside(auxTab->nome, listaFrom))
							textcolor(CYAN);
						else
							textcolor(WHITE);
						retangulo(x - 1, y - 1, strlen(auxCol->nome) + 16, 1);
							gotoxy(x, y);
						if(auxCol->fk != NULL)
							printf("%s (FK)(%c)", auxCol->nome, auxCol->tipo);
						else if (auxCol->pk == 'S')
							printf("%s (PK)(%c)", auxCol->nome, auxCol->tipo);
							else
								printf("%s (%c)", auxCol->nome, auxCol->tipo);
						TpDado *auxDado = auxCol->pDados;
						while(auxDado) {
							if(isInside(auxCol->nome, listaSelect) && isInside(auxTab->nome, listaFrom) && auxBetC->valor.i == valorC || isInside(auxTab->nome, listaFrom) && strcmp(select, "SELECT * ") == 0 && auxBetC->valor.i == valorC)
								textcolor(CYAN);
							else
								textcolor(WHITE);
							y+=2;
							gotoxy(x, y);
							retangulo(x - 1, y - 1, strlen(auxCol->nome) + 16, 1);
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
							textcolor(WHITE);
							if(!auxCol->prox)
								qtdeDados+=2;
							auxDado = auxDado->prox;
							if(auxBetC != NULL)
								auxBetC = auxBetC->prox;
						}
						x += strlen(auxCol->nome) + 12;
						auxCol = auxCol->prox;
					}
					qtdeDados += 4;
					qtdeTab++;
					auxTab = auxTab->prox;
				}
			}
			else {
				while(auxTab) {
					retornaPalavra(where, 4, aux);
					x = 3;
					y = (qtdeTab + qtdeDados) + 1;
					gotoxy(x, y);
					if(isInside(auxTab->nome, listaFrom))
						textcolor(CYAN);
					else
						textcolor(WHITE);
					printf("%s", auxTab->nome);
					textcolor(WHITE);                  
					TpColuna *auxCol = auxTab->pCampos;
					while(auxCol) {
						auxBetC = auxBet->pDados;
						y = (qtdeTab + qtdeDados) + 3;
						gotoxy(x, y);
						if(isInside(auxCol->nome, listaSelect) && isInside(auxTab->nome, listaFrom) || teste(select, "*") && isInside(auxTab->nome, listaFrom))
							textcolor(CYAN);
						else
							textcolor(WHITE);
						retangulo(x - 1, y - 1, strlen(auxCol->nome) + 16, 1);
							gotoxy(x, y);
						if(auxCol->fk != NULL)
							printf("%s (FK)(%c)", auxCol->nome, auxCol->tipo);
						else if (auxCol->pk == 'S')
							printf("%s (PK)(%c)", auxCol->nome, auxCol->tipo);
							else
								printf("%s (%c)", auxCol->nome, auxCol->tipo);
						TpDado *auxDado = auxCol->pDados;
						while(auxDado) {
							if(isInside(auxCol->nome, listaSelect) && isInside(auxTab->nome, listaFrom) && strcmp(auxBetC->valor.t,aux) == 0 || isInside(auxTab->nome, listaFrom) && strcmp(select, "SELECT * ") == 0 && strcmp(auxBetC->valor.t,aux) == 0)
								textcolor(CYAN);
							else
								textcolor(WHITE);
							y+=2;
							gotoxy(x, y);
							retangulo(x - 1, y - 1, strlen(auxCol->nome) + 16, 1);
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
							textcolor(WHITE);
							if(!auxCol->prox)
								qtdeDados+=2;
							auxDado = auxDado->prox;
							if(auxBetC != NULL)
								auxBetC = auxBetC->prox;
						}
						x += strlen(auxCol->nome) + 12;
						auxCol = auxCol->prox;
					}
					qtdeDados += 4;
					qtdeTab++;
					auxTab = auxTab->prox;
				}
			}
		}
	}
	x = 3;
	y+=3;
	textcolor(CYAN);
	gotoxy(x, y);
	printf("===============================");
	gotoxy(x, y + 1);
	printf("{ Pressione Enter para voltar }");
	gotoxy(x, y + 2);
	printf("===============================");
	getch();
	textcolor(WHITE);
	return y;
}

void quebraupdate(char comando[300], char update[100], char set[100], char where[100]) {
    int i = 0, j, y, indexpalavra = 0;
    char aux[8], c;
    strcpy(aux, " ");
    while (comando[i] != '\0' && strcmp(aux, "SET") != 0) {
        for (j = i, y = 0; y < 3; y++, j++)
            aux[y] = comando[j];
        aux[y] = '\0';
        update[i] = comando[i];
       	i++;
    }
    i -= 2;
    update[i] = '\0';
    i++;
    while (comando[i] != '\0' && strcmp(aux, "WHERE") != 0) {
        for (j = i, y = 0; y < 5; y++, j++)
            aux[y] = comando[j];
        aux[y] = '\0';
        set[indexpalavra] = comando[i];
        indexpalavra++;
       	i++;
    }
    indexpalavra -= 2;
    set[indexpalavra] = '\0';
    i--;
    indexpalavra = 0;
    while (comando[i] != '\0' && comando[i] != ';') {
        where[indexpalavra] = comando[i];
        indexpalavra++;
        i++;
    }
    where[indexpalavra] = '\0';
}

void alterar(TpTabela **pTabela, char comandosql[]) {
	float valorF;
	int valorI, j;
	TpTabela *aux;
	TpColuna *auxCampos;
	TpDado *auxDados;
	int i, qtde = 0;
	char update[100], set[100], where[100], palavra[30], condicao_coluna[30], condicao_valor[20], coluna[30], valor_coluna[20];
	quebraupdate(comandosql, update, set, where);
	retornaPalavra(update, 2, palavra);
	aux = *pTabela;
	while(aux->prox != NULL && strcmp(aux->nome, palavra) != 0)
		aux = aux->prox;
	retornaPalavra(where, 2, condicao_coluna);
	retornaPalavra(where, 4, condicao_valor);
	
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
	if (auxCampos->tipo == 'N') {
		valorF = atof(condicao_valor);
		while(auxDados->prox != NULL && auxDados->valor.n != valorF) {
			auxDados = auxDados->prox;
			qtde++;
		}
	}
	if (auxCampos->tipo == 'I') {
		valorI = atoi(condicao_valor);
		while(auxDados->prox != NULL && auxDados->valor.i != valorI) {
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
	retornaPalavra(set, i, coluna);
	retornaPalavra(set, i + 2, valor_coluna);
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
				auxDados->valor.c = valor_coluna[0];
			}
			i += 3;
			retornaPalavra(set, i, coluna);
			retornaPalavra(set, i + 2, valor_coluna);
		}
		auxCampos = auxCampos->prox;
	}
}

void telacheia() {
	keybd_event ( VK_MENU, 0x38, 0, 0 );
	keybd_event ( VK_SPACE, 0x39, 0, 0 );
	keybd_event(0x58,0,0,0);
	keybd_event ( VK_MENU, 0x38, KEYEVENTF_KEYUP, 0 );
	keybd_event ( VK_SPACE, 0x39, KEYEVENTF_KEYUP, 0 );
	keybd_event(0x58,0,KEYEVENTF_KEYUP,0);
}

// Desenhos

#define X_MAX 150
#define LINHAH 196
#define LINHAV 179
#define BORDASE 218
#define BORDASD 191
#define BORDAIE 192
#define BORDAID 217

void retangulo(int x, int y, int BASERETANGULO, int ALTURARETANGULO) {
	int i, j;
	gotoxy(x, y);
	printf("%c", BORDASE);
	for(i = 0; i < BASERETANGULO; i++) {
		printf("%c", LINHAH);
	}
	printf("%c\n", BORDASD);
	
	for(i = 0; i < ALTURARETANGULO; i++) {
		gotoxy(x, ++y);
		printf("%c", LINHAV);
		for(j = 0; j < BASERETANGULO; j++)
			printf(" ");
		printf("%c\n", LINHAV);
	}
	
	gotoxy(x, ++y);
	printf("%c", BORDAIE);
	for(i = 0; i < BASERETANGULO; i++) {
		printf("%c", LINHAH);
	}
	printf("%c", BORDAID);
}
