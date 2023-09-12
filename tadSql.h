union unionDados{
	int i;
	float n;
	char c, t[20], d[10];
};

struct tpDado {
	union valor;
	tpDado *prox;
}

struct tpColuna {
	tpColuna *prox, *fk;
	char campo[20], tipo, pk;
	tpDado *pAtual, *pDados;
};
typedef struct tpColuna Coluna;

struct tpTabela {
	struct tpTabela *ant, *prox;
	struct tpColuna *pCampo;
	char tabela[20]; 
};
typedef struct tpTabela Tabela;

struct tpBanco {
	char banco[20];
	tpTabela *pTabela;
};
typedef struct tpBanco Banco;


