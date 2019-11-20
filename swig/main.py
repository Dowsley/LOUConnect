from AVL import *

# Recarregamento/Inicializacao da arvore.
arvore = None
arvore = desserializar(arvore)

# GUI
while (True):
    print("1. Inserir Usuario")
    print("2. Listar Usuarios")
    print("3. Buscar Usuario")
    print("4. Modificar Info de Usuario")
    print("5. Deletar Usuario")
    print("6. Sair")
    escolha = input("Escolha: ")

    # Adicionar User
    if (escolha == '1'):
        nome = input("Digite o nome: ")

        # Anti-repeticao
        found = buscarNo(arvore, nome)
        if (found != None):
            print("Um usuario sob este nome ja existe, tente novamente!")
        else:
            ocup =input("Digite a ocupacao: ")
            cpf = input("Digite o cpf: ")
            email =  input("Digite o email: ")
            niver = input("Digite a data de aniversario no formato DD MM AAAA: ").split(" ")

            # Insercao
            arvore = inserirNo(arvore, novoNo(nome, ocup, cpf, email, int(niver[0]), int(niver[1]), int(niver[2])))

    # Listar Users
    elif (escolha == '2'):
        exibirIn(arvore)

    # Buscar User
    elif (escolha == '3'):
        nome = input("Digite o nome do usuario a ser buscado: ")
        found = buscarNo(arvore, nome)
        if (found == None):
            print("Nenhum usuario com este nome encontrado.")
        else:
            print("Nome:", found.nome)
            print("Ocupacao:", found.ocupacao)
            print("CPF:", found.cpf)
            print("Email:", found.email)
            print("{}/{}/{}".format(found.niver.dia, found.niver.mes, found.niver.ano))

    # Modificar user
    elif (escolha == '4'):
        nome = input("Digite o nome do usuario a ser modificado: ")
        found = buscarNo(arvore, nome)
        if (found == None):
            print("Nenhum usuario com este nome encontrado.")
        else:
            print("O que deseja modificar?")
            print("1. Nome")
            print("2. Ocupacao")
            print("3. CPF")
            print("4. Email")
            print("5. Niver")
            escolha = input("Escolha: ")

            if (escolha == '1'):    # Nome
                nome = input("Digite o novo nome: ")
                found = buscarNo(arvore, nome)
                if (found != None):
                    print("Um usuario sob este nome ja existe, tente novamente!")
                else:
                    found.nome = nome
            elif (escolha == '2'):  #  Ocup
                found.ocupacao = input("Digite o novo :")
            elif (escolha == '3'):  # CPF
                found.cpf = input("Digite o novo :")
            elif (escolha == '4'):  # Email
                found.email = input("Digite o novo :")
            elif (escolha == '5'):  # Niver
                niver = input("Digite a data de aniversario no formato DD MM AAAA: ").split(" ")
                found.niver.dia = int(niver[0])
                found.niver.mes = int(niver[1])
                found.niver.ano = int(niver[2])

    # Deletar user
    elif (escolha == '5'):
        nome = input("Digite o nome do usuario a ser deletado: ")
        found = buscarNo(arvore, nome)
        if (found == None):
            print("Nenhum usuario com este nome encontrado.")
        else:
            deletarNo(arvore, nome)

    # Encerramento do programa e serializacao da arvore
    elif (escolha == '6'):
        print("Armazenando registros...")
        serializar(arvore)
        print("Registros armazenados com sucesso. Adeus!")
        break
