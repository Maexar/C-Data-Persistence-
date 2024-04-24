#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "source/persistencia.h"

void adicionarVenda(pDFile arq);
void exibirTodosVenda(pDFile arq);

void imprimeVenda(void *info){
   
    Venda *v = (Venda *) info;
   printf("ID: %d, Cliente: %d - Data: %s Codigo: %d - Quantidade: %d - Valor: %f\n", v->id, v->cpf, v->date, v->cod, v->quantidade, v->valor);
}

int comparaVenda(void* info, void* chave){
   Venda *v = (Venda*)info;
    int* key = (int*)chave;
    
    return *key - v-> cod;
}

void* alocaVenda(){
   return malloc(sizeof(Venda));
}

int Filtro(void *info)
{
    Venda *vendas = (Venda *)info;
    
   if (vendas -> valor >= 1.00 )
      return 1;

   return 0;
}



int main() {
    // Abrir arquivo Venda
    pDFile arquivoVenda = open("Venda.dat", sizeof(Venda));
    

    if (arquivoVenda == NULL) {
        printf("Falha ao abrir um dos arquivos.\n");
        return 1;
    }

     int escolha;

     int FindID;

    
     
    do {
        // Exiba o menu
        printf("\n--- Menu ---\n");
        printf("1. Cadastro de Venda\n");
        printf("2. Exibir Venda\n");
        printf("3. Pesquisar Venda\n");
        printf("4. Atualizar Venda\n");
        printf("5. Deletar Venda\n");
        printf("6. Filtrar Vendas \n");
        printf("0. Sair\n"); 
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                adicionarVenda(arquivoVenda);
                exibirTodosVenda(arquivoVenda);
                break;
            case 2:
                exibirTodosVenda(arquivoVenda);
                break;
           case 3:
                printf("\nDigite ID do Venda para pesquisar: ");
                scanf("%d", &FindID);

              
            void *pEncontrado = retrieve(arquivoVenda, &FindID, comparaVenda , alocaVenda);

           if(pEncontrado != NULL){
                 printf("\nVenda Encontrado:\n");
                 imprimeVenda(pEncontrado);
           }
           else{
                printf("Venda Inexistente\n");
           }    
               
                break;

            case 4:
                printf("\nDigite Codigo do Venda para atualizar: ");
                 scanf("%d", &FindID);

                
                void *VendaExistente = retrieve(arquivoVenda, &FindID, comparaVenda, alocaVenda);

                if (VendaExistente != NULL) {
                    
                    Venda *novoDados = (Venda *)VendaExistente; 
                    
                   printf("\n Digite a nova data da Venda:");
                   scanf("%s", novoDados->date);
                    
                    printf("\n Digite a nova quantidade da Venda: ");
                    scanf("%d", &novoDados->quantidade);

                    printf("\n Digite o novo valor da Venda: ");
                    scanf("%f", &novoDados->valor);

                    
                    novoDados->id = FindID;
                    
                    
                    update(arquivoVenda, &FindID, novoDados, comparaVenda, alocaVenda);
                    printf("Venda atualizado com sucesso.\n\n");
                }
                
                else {
                    printf("Venda com ID %d nao encontrado para atualizacao.\n\n", FindID);
    
                }

                break;
            
            case 5:
                printf("Digite o Codigo do Venda que deseja deletar: \n");
                scanf("%d", &FindID);

                delete(arquivoVenda, &FindID, comparaVenda, alocaVenda);
                printf("Deletando Venda... \n");

                fclose(arquivoVenda->arquivo);
                int remover = remove("Venda.dat");
                
                // Esse IF Resolve o Bug de permissao negada, nao retirar. Se o bug retornar, tente tirar o if e
                // teste no programa. Se não resolver, mantenha o IF e recrie o arquivo Venda.dat
                //OBS: O bug de permissao negada faz com que, ao tentar deletar um registro, o programa se feche
                if (remover == 0)
                    printf("arq removido");
                else
                    perror("Erro: ");

                rename("arqNovo.dat", "Venda.dat");
                
                arquivoVenda = open("Venda.dat", sizeof(Venda));

                break;
            case 6:
                 printf("hhhhhhh1");
                arquivoVenda = open("Venda.dat","r+b");

                pDLista lista = query(arquivoVenda, Filtro);
                 printf("hhhhhhh2");
                
                 if (lista == NULL) {
                     printf("A função query retornou uma lista vazia ou NULL.\n");
                     break;
                    }

                 printf("Total de elementos na lista: %d\n", lista->quantidade);

                int i;
                 printf("hhhhhhh3");
                for(i=1; i<=lista->quantidade;i++){
                    printf("hhhhhhh4");

                    Venda *vv = (Venda *)buscarInfoPos(lista, i);
                    if (vv != NULL) {
                        imprimeVenda(vv);
                    } else {
                        printf("Erro ao buscar o elemento na posição %d da lista.\n", i);
                    }
                 
                    printf("Venda");
                }
                close(arquivoVenda);
                printf("hhhhhhh5");
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Escolha invalida. Tente novamente.\n");
        }
    } while (escolha != 0);

    // Feche os arquivos
    fclose(arquivoVenda->arquivo);
    
    free(arquivoVenda);
    
    return 0;
}

void adicionarVenda(pDFile arq) {
    
    Venda novoVenda;

    printf("Digite o id da Venda: ");
    scanf("%d", &novoVenda.id);

    printf("Digite o CPF do Cliente: ");
    scanf("%d", &novoVenda.cpf);
   
    

    printf("Digite a data da Venda: ");
    scanf("%s", novoVenda.date);

    printf("Digite o codigo do Produto: ");
    scanf("%d", &novoVenda.cod);

    

    printf("Digite a quantidade do Produto: ");
    scanf("%d", &novoVenda.quantidade);

    printf("Digite o valor da venda:");
    scanf("%f", &novoVenda.valor);

    createe(arq, &novoVenda);
    printf("Venda adicionada com sucesso.\n\n");
}

void exibirTodosVenda(pDFile arq) {
    // Define o ponteiro do arquivo no início do arquivo
    fseek(arq->arquivo, 0, SEEK_SET);

    Venda venda;
    printf("\n--- Todos as Vendas ---\n");
    while (fread(&venda, arq->tamanhoRegistro, 1, arq->arquivo) == 1) {
        printf("\n ID: %d, Cliente: %d, Data: %s, Codigo: %d, Quantidade:%d, Valor: %.2f\n", venda.id, venda.cpf, venda.date, venda.cod, venda.quantidade, venda.valor);
    }
} 

