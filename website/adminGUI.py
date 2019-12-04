from AVL import *
from os import *

# Recarregamento/Inicializacao da arvore.
system("clear")
print("<< Carregando registros...>>")
arvore = None
arvore = desserializar(arvore)
print("<< Registros carregados com sucesso! >>\n")
input("Aperte enter para iniciar o programa.")

# GUI
while (True):
    system("clear")
    print("1. Inserir Usuario")
    print("2. Listar Usuarios")
    print("3. Buscar Usuario")
    print("4. Modificar Info de Usuario")
    print("5. Deletar Usuario")
    print("6. Sair")
    escolha = input("Escolha: ")

    # Adicionar User
    if (escolha == '1'):
        system("clear")
        nome = input("Digite o nome: ")

        # Anti-repeticao
        found = buscarNo(arvore, nome)
        if (found != None):
            print("<<ERRO: Um usuario sob este nome ja existe, tente novamente! >>")
        else:
            ocup =input("Digite a ocupacao: ")
            cpf = input("Digite o cpf: ")
            email =  input("Digite o email: ")
            niver = input("Digite a data de aniversario no formato DD MM AAAA: ").split(" ")
            desc = input("Insira a descrição: ")

            # Insercao
            arvore = inserirNo(arvore, novoNo(nome, ocup, cpf, email, desc, int(niver[0]), int(niver[1]), int(niver[2])))
            print("\nUsuário inserido com sucesso!")
        input("\nAperte enter para voltar ao menu.")

    # Listar Users
    elif (escolha == '2'):
        system("clear")
        print("-- Usuarios Registrados --")
        exibirIn(arvore)
        input("\n\nAperte enter para voltar.")

    # Buscar User
    elif (escolha == '3'):
        system("clear")
        nome = input("Digite o nome do usuario a ser buscado: ")
        found = buscarNo(arvore, nome)
        if (found == None):
            print("\n<< Nenhum usuario com este nome encontrado. >>")
        else:
            print("\nNome:", found.nome)
            print("Ocupacao:", found.ocupacao)
            print("CPF:", found.cpf)
            print("Email:", found.email)
            print("Descrição:",found.desc)
            print("Data de Aniversário: {}/{}/{}".format(found.niver.dia, found.niver.mes, found.niver.ano))
        input("\nAperte enter para voltar ao menu.")

    # Modificar user
    elif (escolha == '4'):
        system("clear")
        nome = input("Digite o nome do usuario a ser modificado: ")
        found = buscarNo(arvore, nome)
        if (found == None):
            print("\n<<ERRO: Nenhum usuario com este nome encontrado. >>")
        else:
            print("\nO que deseja modificar?")
            print("1. Nome")
            print("2. Ocupacao")
            print("3. CPF")
            print("4. Email")
            print("5. Niver")
            print("6. Descrição")
            escolha = input("Escolha: ")

            if (escolha == '1'):    # Nome
                nome = input("\nDigite o novo nome: ")
                found = buscarNo(arvore, nome)
                if (found != None):
                    print("<< ERRO: Um usuario sob este nome ja existe, tente novamente! >>")
                else:
                    found.nome = nome
            elif (escolha == '2'):  #  Ocup
                found.ocupacao = input("Digite o novo: ")
            elif (escolha == '3'):  # CPF
                found.cpf = input("Digite o novo: ")
            elif (escolha == '4'):  # Email
                found.email = input("Digite o novo: ")
            elif (escolha == '5'):  # Niver
                niver = input("Digite a data de aniversario no formato DD MM AAAA: ").split(" ")
                found.niver.dia = int(niver[0])
                found.niver.mes = int(niver[1])
                found.niver.ano = int(niver[2])
            elif (escolha == '6'):
                found.desc = input("Digite o novo: ")
            input("\n<< Aperte enter para voltar ao menu. >>")

    # Deletar user
    elif (escolha == '5'):
        system("clear")
        nome = input("Digite o nome do usuario a ser deletado: ")
        found = buscarNo(arvore, nome)
        if (found == None):
            print("\n<< ERRO:Nenhum usuario com este nome encontrado. >>")
        else:
            arvore = deletarNo(arvore, nome)
            print("Usuário deletado com sucesso!")
        input("\nAperte enter para voltar ao menu.")

    # Encerramento do programa e serializacao da arvore
    elif (escolha == '6'):
        system("clear")
        print("Armazenando registros...")
        serializar(arvore)
        print("Registros armazenados com sucesso. Adeus!")
        input("\n<< Aperte enter para sair do programa. >>")
        break
