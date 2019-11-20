#include <stdio.h>   // Para funções de input e output.
#include <stdlib.h>  // Para funções de gerenciamento de memória.
#include <string.h>  // Para operações de Strings, muito importante.
#include "AVL.h"

#define max(a,b) (((a) > (b)) ? (a) : (b))	// Achar maior valor rapidamente.
#define MAX_NOME 50   // Tamanho maximo do stream para nome
#define MAX_OCUP 100  // Tamanho maximo do stream para ocupação

FILE* fp;	// Ponteiro global para o arquivo que armazenará os registros.

// Aloca uma nova posicao de memoria para um no, e copia as informacoes dele para o novo.
USER* recriarNo(USER* No)
{
	USER* novoUser = (USER*)malloc(sizeof(USER));
	*novoUser = *No;
	novoUser->esquerda = NULL;
	novoUser->direita = NULL;
	novoUser->altura = 1;

	return novoUser;
}


// Cria um novo nó de acordo com as entradas.
USER* novoNo(char* nome, char* ocupacao, char* cpf, char* email, int dia, int mes, int ano)
{
	USER* novoUser = (USER*)malloc(sizeof(USER));
	novoUser->esquerda = NULL;
	novoUser->direita = NULL;
	novoUser->altura = 1;
	novoUser->niver.dia = dia;
	novoUser->niver.mes = mes;
	novoUser->niver.ano = ano;
	strcpy(novoUser->nome, nome);
	strcpy(novoUser->ocupacao, ocupacao);
	strcpy(novoUser->cpf, cpf);
	strcpy(novoUser->email, email);

	return novoUser;
}


// Insere um nó na arvore, comparação igual vão para esquerda, maneira clássica.
USER* inserirNo(USER* raiz, USER* novoUser)
{
	/******* (PASSO 1) INSERÇÃO BST *******/
	// Caso 1: Nova raiz da sub-árvore.
	if (raiz == NULL)
		return novoUser;

	// Caso 2: Chave MENOR que a da raiz.
	if (strcmp(novoUser->nome, raiz->nome) < 0)
        raiz->esquerda = inserirNo(raiz->esquerda, novoUser);

	// Caso 3: Chave MAIOR que a da raiz.
	else if (strcmp(novoUser->nome, raiz->nome) > 0)
        raiz->direita = inserirNo(raiz->direita, novoUser);

	// Caso 4: Chaves iguais, não permitido em BSTs.
	else
	{
		printf("<< ERRO: Nome em uso, tente outro >>");
		return raiz;
	}

	/****** (PASSO 2) ATUALIZAÇÃO DE ALTURA ******/
	raiz->altura = 1 + max(alturaNo(raiz->esquerda), alturaNo(raiz->direita));

	/* (3) CHECAR FATOR DE BALANCEAMENTO E REALIZAR ROTAÇÕES SE NECESSÁRIO */
	int fator = fatorNo(raiz);

	// Caso LL
	if (fator > 1 && strcmp(novoUser->nome, raiz->esquerda->nome) < 0)
		return rotDireita(raiz);
	// Caso RR
	if (fator < -1 && strcmp(novoUser->nome, raiz->direita->nome) > 0)
		return rotEsquerda(raiz);
	// Caso LR
	if (fator > 1 && strcmp(novoUser->nome, raiz->esquerda->nome) > 0)
	{
		raiz->esquerda = rotEsquerda(raiz->esquerda);
		return rotDireita(raiz);
	}
	// Caso RL
	if (fator < -1 && strcmp(novoUser->nome, raiz->direita->nome) < 0)
	{
		raiz->direita = rotDireita(raiz->direita);
		return rotEsquerda(raiz);
	}

	/*** Caso Padrão: Retorna raiz (nó) não alterada ***/
	return raiz;
}


// Função recursiva que busca Nós por sua chave e os retorna. Caso não ache, valor é Nulo.
USER* buscarNo(USER* raiz, char* nome)
{
	if (raiz == NULL || strcmp(raiz->nome, nome) == 0)
    	return raiz;

    //
    if (strcmp(nome, raiz->nome) > 0)
       return buscarNo(raiz->direita, nome);

    // Key is smaller than root's key
    return buscarNo(raiz->esquerda, nome);
}


// Função recursiva que busca por um nó pelo seu valor e o apaga da memória, após isso é feita uma reconstrução adequada da árvore.
USER* deletarNo(USER* raiz, char* nome)
{
	/** (PASSO 1) REMOÇÃO PADRÃO DE BST **/

	// Não encontrou.
	if (raiz == NULL)
		return raiz;
	// Chave MENOR que a da raiz.
	if (strcmp(nome, raiz->nome) < 0)
		raiz->esquerda = deletarNo(raiz->esquerda, nome);
	// Chave MENOR que a da raiz.
	else if (strcmp(nome, raiz->nome) > 0)
		raiz->direita = deletarNo(raiz->direita, nome);

	// Se for igual --> Encontrou o Nó certo.
	else
	{
		// Nó com apenas um ou nenhum filho.
		if ( (raiz->esquerda == NULL) || (raiz->direita == NULL) )
		{
			USER* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

			// Caso de nenhum filho
			if (temp == NULL)
			{
				temp = raiz;
				raiz = NULL;
			}
			// Caso de 1 filho
			else *raiz = *temp;
			free(temp);
		}
		// Nó com 2 filhos
		else
		{
			// Acha o sucessor InOrdem
			USER* atual = raiz->direita;
			while (atual->esquerda != NULL)
				atual = atual->esquerda;
			// Passa a chave do sucessor para a raiz
			strcpy(raiz->nome, atual->nome);
			// Deleta o sucessor
			raiz->direita = deletarNo(raiz->direita, atual->nome);
		}
	}

	// Se a árvore tinha apenas um nó:
	if (raiz == NULL)
		return raiz;

	/*** (PASSO 2) ATUALIZAÇÃO DA ALTURA ***/
	raiz->altura = 1 + max(alturaNo(raiz->esquerda), alturaNo(raiz->direita));

	/* (PASSO 3) CHECAR FATOR DE BALANCEAMENTO E REALIZAR ROTAÇÕES SE NECESSÁRIO */
	int fator = fatorNo(raiz);

	// Caso LL
	if (fator > 1 && fatorNo(raiz->esquerda) >= 0)
		return rotDireita(raiz);
	// Caso RR
	if (fator < -1 && fatorNo(raiz->direita) <= 0)
		return rotEsquerda(raiz);
	// Caso LR
	if (fator > 1 && fatorNo(raiz->esquerda) < 0)
	{
		raiz->esquerda = rotEsquerda(raiz->esquerda);
		return rotDireita(raiz);
	}
	// Caso RL
	if (fator < -1 && fatorNo(raiz->direita) > 0)
	{
		raiz->direita = rotDireita(raiz->direita);
		return rotEsquerda(raiz);
	}

	/*** Caso Padrão: Retorna raiz (nó) não alterada ***/
	return raiz;
}


// Retorna a altura de um Nó. Nó não existente tem altura 0.
int alturaNo(USER* No)
{
	if (No == NULL)
		return 0;
	else
		return No->altura;
}


// Retorna o fator de balanceamento do nó.
int fatorNo(USER* No)
{
	if (No == NULL)
		return 0;
	else
		return alturaNo(No->esquerda) - alturaNo(No->direita);
}


// Função que printa as chaves em Pré-ordem.
void exibirPre(USER* arvore)
{
	if (arvore != NULL)
	{
		printf("\n%s", arvore->nome);
		exibirPre(arvore->esquerda);
		exibirPre(arvore->direita);
	}
}


// Função que printa as chaves em In-ordem.
void exibirIn(USER* arvore)
{
	if (arvore != NULL)
	{
		exibirIn(arvore->esquerda);
		printf("\n| %s", arvore->nome);
		exibirIn(arvore->direita);
	}
}


// Função que printa as chaves em Pós-ordem.
void exibirPos(USER* arvore)
{
	if (arvore != NULL)
	{
		exibirPos(arvore->esquerda);
		exibirPos(arvore->direita);
		printf("\n%s", arvore->nome);
	}
}

// Varre a arvore e executa a serializacao .
void escreveNo(USER* No)
{
	if (No != NULL)
	{
		fwrite(No, sizeof(USER), 1, fp);
		escreveNo(No->esquerda);
		escreveNo(No->direita);
	}
}

// Executa a serialização da árvore (Escrita dela num arquivo, para garantir a persistência dos dados)
void serializar(USER* No)
{
	fp = fopen("USER.DAT", "wb+");
	escreveNo(No);
	fclose(fp);
}

// Abre o arquivo de registros e recarrega a arvore. Cria o arquivo caso nao exista.
USER* desserializar(USER* arvore)
{
	fp = fopen("USER.DAT", "rb+");

	// Nao existe --> Cria arquivo vazio
	if (fp == NULL)
	{
		fclose(fp);
		fp = fopen("USER.DAT", "wb+");
	}
	// Des-serialização a partir do arquivo.
	else
	{
		USER No;
		while(fread(&No, sizeof(No), 1, fp)==1)
			arvore = inserirNo(arvore, recriarNo(&No));
	}
	rewind(fp);
	fclose(fp);

	return arvore;
}


// Realiza rotação da sub-árvore y pra direita, retorna a nova raiz que fica no lugar de y.
USER* rotDireita(USER* y)
{
	USER* x = y->esquerda;
	USER* sub = x->direita;

	// Realiza rotação.
	x->direita = y;
	y->esquerda = sub;

	// Atualiza altura.
	y->altura = max(alturaNo(y->esquerda), alturaNo(y->direita)) + 1;
	x->altura = max(alturaNo(x->esquerda), alturaNo(x->direita)) + 1;

	// Retorna a nova raiz
	return x;
}


// Realiza rotação da sub-árvore x pra esquerda, retorna a nova raiz que fica no lugar de x.
USER* rotEsquerda(USER* x)
{
	USER* y = x->direita;
	USER* sub = y->esquerda;

	// Realiza rotação.
	y->esquerda = x;
	x->direita = sub;

	// Atualiza altura.
	x->altura = max(alturaNo(x->esquerda), alturaNo(x->direita)) + 1;
	y->altura = max(alturaNo(y->esquerda), alturaNo(y->direita)) + 1;

	// Retorna a nova raiz
	return y;
}
