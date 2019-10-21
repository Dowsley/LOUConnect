#include <stdio.h>  //Para funções de input e output like.
#include <stdlib.h>  // Para funções de gerenciamento de memória.
#include <conio.h>  // Para funções que movem o no console.
#include <windows.h>  // Para funções relacionadas ao OS Windows. Neste caso, só usei para dar "cls" e limpar a tela do console.
#include <string.h>  // Para operações de Strings, muito importante.

// Struct que guarda uma data. Será usado para aniversário.
typedef struct Data{
	int dia;
	int mes;
	int ano;
}DATA;

// Struct que guarda informações de um usuário.
typedef struct USER{
	char nome[10];
	DATA* niver;

	struct USER* esquerda;
	struct USER* direita;
}USER;

// <conio.h> :: Variável e função que conseguem mover o cursor de escrita e leitura no console (CMD), com coordenadas X e Y.
COORD coord = {0,0};
void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

USER* novoNo(void);
void inserirNo(USER**, USER*);
void exibirPre(USER*);
void exibirIn(USER*);
void exibirPos(USER*);
USER* buscarNo(USER*, char*);
USER* deletarNo(USER*, char*);

int main()
{
	FILE *fp, *ft; /// file pointers
	USER* arvore = NULL;  // Criação da Árvore
	USER* temp;  // Auxiliar para armazenar um User.
	char nome[10], alter[10];   // Auxiliares de busca e alteração
	char another, choice;  // Auxiliares de escolha na GUI

    while(1)
    {
        system("cls");  // Limpa a janela do console.
        gotoxy(30,10);  // Põe o cursor na posição 30, 10 a partir do canto superior-esquerdo.
        printf("1. Adicionar Usuario"); 
        gotoxy(30,12);
        printf("2. Listar Usuarios");
        gotoxy(30,14);
		printf("3. Buscar um Usuario");
        gotoxy(30,16);
        printf("4. Modificar Info. de Usuario");
        gotoxy(30,18);
        printf("5. Deletar Usuario");
        gotoxy(30,20);
        printf("6. Sair");
        gotoxy(30,22);
        printf("Escolha: ");

        fflush(stdin);  // Dá flush no input buffer. Apaga qualquer caractér ou string que havia lá antes.
        choice  = getche();  // Recebe entrada do teclado, e como padrão printa na tela.
        switch(choice)
        {
	        case '1':  // Se o usuário pressionar '1': Registra um novo USER na árvore.
	            system("cls");
	            another = 's';
	            while(another == 's')  // Se o usuário quiser outro input.
	            {
					inserirNo(&arvore, novoNo());

	                printf("\nAdicionar outro Usuario? (s/n) ");
	                fflush(stdin);
	                another = getche();
	            }
	            break;
	        case '2':  // Exibe o nome de todos os USERS da árvore, em todos os 3 tipos de formato de procura.
	            system("cls");

				printf("\n\nPre-Ordem:");
				exibirPre(arvore);

				printf("\n\nPos-Ordem:");
				exibirPos(arvore);

				printf("\n\nIn-Ordem:");

			    exibirIn(arvore);

	            getch();
	            break;
			case '3':  // Busca um usuário pelo seu nome, e devolve todas as informações dele na tela.
				system("cls");
				another = 's';
				while(another == 's')
				{
					printf("\nInsira o nome do usuario que deseja buscar: ");
					scanf("%s", nome);
					
					temp = buscarNo(arvore, nome);
					if (temp != NULL)
					{
						printf("\nNome: %s", temp->nome);
						printf("\nData de Nascimento: %d/%d/%d", temp->niver->dia, temp->niver->mes, temp->niver->ano);
					}
					else
						printf("\nUsuario nao encontrado.");

					printf("\nBuscar outro Usuario? (s/n) ");
					fflush(stdin);
					another = getche();
				}
				break;
	        case '4':  // Modifica informações de um USER.
	            system("cls");
	            another = 's';
	            while(another == 's')
	            {
	               	printf("\nInsira o nome do usuario que deseja alterar: ");
	                scanf("%s",nome);

	                temp = buscarNo(arvore, nome);
	                if (temp != NULL)  // Encontrou
	                {
		                system("cls");
				        gotoxy(30,10);
				        printf("Usuario %s encontrado. O que deseja alterar?", nome); 
				        gotoxy(30,12);
				        printf("1. Nome");
				        gotoxy(30,14);
				        printf("2. Data de Aniversario");
				        gotoxy(30,16);
				        printf("Escolha: ");

				        fflush(stdin);
        				choice  = getche();
        				switch(choice)
        				{
        					case '1':
        						printf("\nDigite o novo nome: ");
	                			scanf("%s",alter);
	                			strcpy(temp->nome, alter);
	                			printf("\nNome alterado com sucesso!");
        						break;
        					case '2':
        						printf("\nDigite a nova data de nascimento no formato DD MM AAAA: ");
								scanf("%d", &temp->niver->dia);
								scanf("%d", &temp->niver->mes);
								scanf("%d", &temp->niver->ano);
								printf("\nData de nascimento alterado com sucesso!");
								break;
        				}
	                }
	                else printf("\nERRO: Usuario nao encontrado!");  // Não encontrou usuário sob este nome

	                printf("\nModificar outro registro? (s/n)");
	                fflush(stdin);
	                another = getche();
	            }
	            break;
	        case '5':  // Deleta um USER da árvore, e a reconstrói.
	            system("cls");
	            another = 's';
	            while(another == 's')
	            {
	               	printf("\nInsira o nome que deseja deletar: ");
	                scanf("%s",nome);

	                arvore = deletarNo(arvore, nome);

	                printf("\nDeletar outro registro? (s/n)");
	                fflush(stdin);
	                another = getche();
	            }
	            break;
	        case '6':  // Sai do programa. Aqui seria a serialização da árvore?
	            return 0;
        }
	}
}

USER* novoNo(void)
{
	USER* novoUser = (USER*)malloc(sizeof(USER));
	novoUser->esquerda = NULL;
	novoUser->direita = NULL;

	char nome[10];
	printf("\nInsira o nome que deseja adicionar: ");
	scanf("%s", nome);
	strcpy(novoUser->nome, nome);

	DATA* niver = (DATA*)malloc(sizeof(DATA));
	printf("\nDigite sua data de nascimento no formato DD MM AAAA: ");
	scanf("%d", &niver->dia);
	scanf("%d", &niver->mes);
	scanf("%d", &niver->ano);
	novoUser->niver = niver;

	return novoUser;
}

void inserirNo(USER** arvore, USER* novoUser)  // Cria novo nó, as informações novas são inseridas dentro da própria função.
{
	if (*arvore == NULL)
        *arvore = novoUser;
    else
    {
        if (strcmp(novoUser->nome, (*arvore)->nome) <= 0)
            inserirNo(&(*arvore)->esquerda, novoUser);
        else
        	inserirNo(&(*arvore)->direita, novoUser);
    }
}

void exibirPre(USER* arvore)  // Função que printa as chaves em Pré-ordem.
{
	if (arvore != NULL)
	{
		printf("\n%s", arvore->nome);
		exibirPre(arvore->esquerda);
		exibirPre(arvore->direita);
	}
}

void exibirIn(USER* arvore)  // Função que printa as chaves em In-ordem.
{
	if (arvore != NULL)
	{
		exibirIn(arvore->esquerda);
		printf("\n%s", arvore->nome);
		exibirIn(arvore->direita);
	}
}

void exibirPos(USER* arvore)  // Função que printa as chaves em Pós-ordem.
{
	if (arvore != NULL)
	{
		exibirPos(arvore->esquerda);
		exibirPos(arvore->direita);
		printf("\n%s", arvore->nome);
	}
}

USER* buscarNo(USER* raiz, char* nome)  // Função que busca Nós por sua chave e os retorna.
{
	if (raiz == NULL || strcmp(raiz->nome, nome) == 0)
    	return raiz; 
     
    // Key is greater than root's key 
    if (strcmp(nome, raiz->nome) > 0) 
       return buscarNo(raiz->direita, nome); 
  
    // Key is smaller than root's key 
    return buscarNo(raiz->esquerda, nome); 
}

USER* deletarNo(USER* raiz, char* nome)  // Função que busca nós pela sua chave, e os apaga da memória.
{
	if (raiz == NULL) return raiz;

	if (strcmp(nome, raiz->nome) < 0)
		raiz->esquerda = deletarNo(raiz->esquerda, nome);
	
	else if (strcmp(nome, raiz->nome) > 0)
		raiz->direita = deletarNo(raiz->direita, nome);

	// Se for igual.
	else 
	{
		// Nó com um filho ou nenhum filho.
		if (raiz->esquerda == NULL)
		{
			USER* temp = raiz->direita;
			free(raiz);
			return temp;
		}
		else if (raiz->direita == NULL)
		{
			USER* temp = raiz->esquerda;
			free(raiz);
			return temp;
		}

		// Nó com 2 filhos: Pegar o sucessor InOrdem. 
		// (o menor na subárvore da direita)
		USER* atual = raiz->direita; 
  
	    /* loop down to find the leftmost leaf */
	    while (atual && atual->esquerda != NULL)
	        atual = atual->esquerda; 
		USER* temp = atual;

		// Copia o valor do sucessor inordem para o Nó.
		strcpy(raiz->nome, temp->nome);

		// Deleta o sucessor inordem
		raiz->direita = deletarNo(raiz->direita, temp->nome);
	}
	return raiz;
}