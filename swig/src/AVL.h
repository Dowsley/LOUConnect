// Struct que guarda uma data. Será usado para aniversário.
typedef struct Data{
	int dia;
	int mes;
	int ano;
}DATA;

// Struct que guarda informações de um usuário.
typedef struct USER{
	char nome[50], cpf[15], email[30], ocupacao[100];
	DATA niver;
	struct USER* esquerda;
	struct USER* direita;
	int altura;
}USER;

USER* recriarNo(USER* No);
USER* novoNo(char* nome, char* ocupacao, char* cpf, char* email, int dia, int mes, int ano);
USER* inserirNo(USER* raiz, USER* novoUser);
USER* buscarNo(USER* raiz, char* nome);
USER* deletarNo(USER* raiz, char* nome);

int alturaNo(USER* No);
int fatorNo(USER* No);
USER* rotDireita(USER* y);
USER* rotEsquerda(USER* x);

void escreveNo(USER* No);
void serializar(USER* No);
USER* desserializar(USER* arvore);

void exibirPre(USER* arvore);
void exibirIn(USER* arvore);
void exibirPos(USER* arvore);
