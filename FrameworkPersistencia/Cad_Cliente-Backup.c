
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "source/persistencia.h"



void adicionarCliente(pDFile arq);
void exibirTodosCliente(pDFile arq);


void imprimeCliente(void *info){
   
    Cliente *c = (Cliente *) info;
   printf("CPF: %d - Nome: %s \n", c->cpf, c->nome);
}

int comparaCliente(void* info, void* chave){
   Cliente *c = (Cliente*)info;
    int* key = (int*)chave;
    
    return *key - c-> cpf;
}

void* alocaCliente(){
   return malloc(sizeof(Cliente));
}

int main() {
    // Abrir arquivo cliente
    pDFile arquivoCliente = open("cliente.dat", sizeof(Cliente));
    
    

    if (arquivoCliente == NULL) {
        printf("Falha ao abrir um dos arquivos.\n");
        return 1;
    }


     int escolha;
     int FindCpf;

    

    

    do {
        // Exiba o menu
        printf("\n--- Menu ---\n");
        printf("1. Cadastro de Cliente\n");
        printf("2. Exibir Cliente\n");
        printf("3. Pesquisar Cliente\n");
        printf("4. Atualizar Cliente\n");
        printf("5. Deletar Cliente\n");
        printf("0. Sair\n"); 
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                adicionarCliente(arquivoCliente);
                exibirTodosCliente(arquivoCliente);
                break;
            case 2:
                exibirTodosCliente(arquivoCliente);
                break;
           case 3:
                printf("\nDigite CPF para pesquisar: ");
                scanf("%d", &FindCpf);

              
            void *pEncontrado = retrieve(arquivoCliente, &FindCpf, comparaCliente , alocaCliente);

           if(pEncontrado != NULL){
                 printf("\nCliente Encontrado:\n");
                 imprimeCliente(pEncontrado);
           }else
                printf("Cliente Inexistente\n");
                
            break;

            case 4:
                printf("\nDigite CPF para atualizar: ");
                scanf("%d", &FindCpf);

                // Verificar se o cliente com o CPF existe antes de atualizar
                void *clienteExistente = retrieve(arquivoCliente, &FindCpf, comparaCliente, alocaCliente);

                if (clienteExistente != NULL) {
                    
                    Cliente novoDados; // obter novos dados do cliente para atualização
                    
                    printf("Digite o novo nome do Cliente: ");
                    scanf("%s", novoDados.nome);

                    // Preencher os demais novos dados do cliente
                    novoDados.cpf = FindCpf;

                    // Chama a função update para atualizar os dados do cliente
                    update(arquivoCliente, &FindCpf, &novoDados, comparaCliente, alocaCliente);
                    printf("Cliente atualizado com sucesso.\n\n");
                }
                
                else {
                    printf("Cliente com CPF %d nao encontrado para atualizacao.\n\n", FindCpf);
                
                }

            break;

            case 5:
            

        
                
                printf("Digite o CFP do cliente que deseja deletar: \n");
                scanf("%d", &FindCpf);

                delete(arquivoCliente, &FindCpf, comparaCliente, alocaCliente);
                printf("Deletando Cliente... \n");

                fclose(arquivoCliente->arquivo);
                int remover = remove("cliente.dat");

               
                
                rename("arqNovo.dat", "cliente.dat");
                
                arquivoCliente = open("cliente.dat", sizeof(Cliente));

                break;

            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Escolha invalida. Tente novamente.\n");
        }
    } while (escolha != 0);

    // Feche os arquivos
    fclose(arquivoCliente->arquivo);
    
    free(arquivoCliente);
    
    return 0;
}



void adicionarCliente(pDFile arq) {
    Cliente novoCliente;
    int FindCpf;

    printf("Digite o cpf do Cliente: ");
    scanf("%d", &FindCpf);

    // Verificar se o cliente com o CPF informado já está cadastrado
    void *clienteExistente = retrieve(arq, &FindCpf, comparaCliente, alocaCliente);

    if (clienteExistente != NULL) {
        printf("Cliente com CPF %d ja cadastrado.\n\n", FindCpf);
        return; // Encerra a função se o cliente já existe
    }

    printf("Digite o nome do Cliente: ");
    scanf("%s", novoCliente.nome);

    // Preencha os demais dados do novo cliente
    novoCliente.cpf = FindCpf;

    createe(arq, &novoCliente);
    printf("Cliente adicionado com sucesso.\n\n");
}

void exibirTodosCliente(pDFile arq) {
    
    fseek(arq->arquivo, 0, SEEK_SET);

    // Leia e exiba todos os Clientes
    Cliente cliente;
    printf("\n--- Todos os Clientes ---\n");
    while (fread(&cliente, arq->tamanhoRegistro, 1, arq->arquivo) == 1) {
        printf("Nome: %s, cpf: %d\n", cliente.nome, cliente.cpf);
    }
}


