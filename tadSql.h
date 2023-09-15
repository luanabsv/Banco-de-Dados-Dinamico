union unionDados{
	int i;
	float n;
	char c, t[20], d[10];
};

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
void defineFk(TpBancoDeDados *pBanco, char string[], char string2[]) {
	TpColuna *novoCampo;
	TpTabela *tabelaAdicionar = pBanco->pTabelas;
	TpTabela *tabelaFk = pBanco->pTabelas;
	char palavra[30];
	retornaPalavra(string, 3, palavra);
	while(strcmp(tabelaAdicionar->nome, palavra) != 0) // Na tabela que será adicionada a FK
		tabelaAdicionar = tabelaAdicionar->prox;
	retornaPalavra(string2, 5, palavra);
	while(strcmp(tabelaFk->nome, palavra) != 0) // Na tabela que está a FK
		tabelaFk = tabelaFk->prox;
	
	TpColuna *FK = tabelaFk->pCampos; // Campos da tabela que tem a FK
	retornaPalavra(string2, 3, palavra);
	printf("%s", palavra);
	while (strcmp(FK->nome, palavra) != 0) {
		FK = FK->prox; 
	}
	novoCampo = (TpColuna*)malloc(sizeof(TpColuna));
	retornaPalavra(string, 6, palavra);
	strcpy(novoCampo->nome, palavra); // Nome da FK na tabela nova
	novoCampo->prox = NULL;
	novoCampo->fk = FK; // FK apontada
	novoCampo->pk = 'N';
}

void definePk(TpBancoDeDados *pBanco, char string[]) {
	TpColuna *coluna;
	char pk[30];
	coluna = pBanco->pTabelas->pCampos;
	retornaPalavra(string, 5, pk);
	
	while(coluna->prox != NULL) {
		if(strstr(pk, coluna->nome))
		{
			
			coluna->pk = 'S';
		}
		else
			coluna->pk = 'N';
			printf("%c, %s", coluna->pk, coluna->nome);
		coluna = coluna->prox;
	}
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

void mostraTudo(TpTabela *tabelas) {
	TpTabela *aux = tabelas;
	while(aux) {
		printf("\n%s\n", aux->nome);
		TpColuna *aux2 = aux->pCampos;
		while(aux2) {
			printf("%s\n", aux2->nome);
			aux2 = aux2->prox;
		}
		aux = aux->prox;	
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
	printf("criado campo %s\n", palavra);
	retornaPalavra(string, 2, palavra);
	if (strcmp(palavra,"INTEGER") == 0) {
		novoCampo->tipo = 'I';
	} 
	else if (strcmp(palavra,"NUMERIC") == 0) {
		novoCampo->tipo = 'N';
	}
	else if (strcmp(palavra,"DATE") == 0) {
		novoCampo->tipo = 'D';
	}
	else if (strcmp(palavra,"CHARACTER(1)") == 0) {
		novoCampo->tipo = 'C';
	}
	else if (strcmp(palavra,"CHARACTER(20)") == 0) {
		novoCampo->tipo ='T';
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



