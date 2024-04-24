#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "source/persistencia.h"

void adicionarProduto(pDFile arq);
void exibirTodosProduto(pDFile arq);

void imprimeProduto(void *info){
   
    Produto *p = (Produto *) info;
   printf("Codigo: %d - Nome: %s - Quantidade: %d - Preco: %f\n", p->codigo, p->nome, p->quantidade, p->preco);
}

int comparaProduto(void* info, void* chave){
   Produto *p = (Produto*)info;
    int* key = (int*)chave;
    
    return *key - p-> codigo;
}

void* alocaProduto(){
   return malloc(sizeof(Produto));
}

int main() {
    // Abrir arquivo Produto
    pDFile arquivoProduto = open("Produto.dat", sizeof(Produto));
    

    if (arquivoProduto == NULL) {
        printf("Falha ao abrir um dos arquivos.\n");
        return 1;
    }

     int escolha;

     int FindCod;

      int tipoConsulta;

    do {
        // Exiba o menu
        printf("\n--- Menu ---\n");
        printf("1. Cadastro de Produto\n");
        printf("2. Exibir Produto\n");
        printf("3. Pesquisar Produto\n");
        printf("4. Atualizar Produto\n");
        printf("5. Deletar Produto\n");
        printf("0. Sair\n"); 
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                adicionarProduto(arquivoProduto);
                exibirTodosProduto(arquivoProduto);
                break;
            case 2:
                exibirTodosProduto(arquivoProduto);
                break;
           case 3:
                printf("\nDigite Codigo do Produto para pesquisar: ");
                scanf("%d", &FindCod);

              
            void *pEncontrado = retrieve(arquivoProduto, &FindCod, comparaProduto , alocaProduto);

           if(pEncontrado != NULL){
                 printf("\nProduto Encontrado:\n");
                 imprimeProduto(pEncontrado);
           }
           else{
                printf("Produto Inexistente\n");
           }    
               
                break;

            case 4:
                 printf("\nDigite Codigo do Produto para atualizar: ");
                 scanf("%d", &FindCod);

                
                void *produtoExistente = retrieve(arquivoProduto, &FindCod, comparaProduto, alocaProduto);

                if (produtoExistente != NULL) {
                    
                    Produto *novoDados = (Produto *)produtoExistente; 
                    
                   int op;

                    printf("\n Deseja alterar o nome? Sim: 1, Nao: 0 :");
                    scanf("%d", &op);

                    if(op == 1){
                        printf("Digite o novo nome do Produto: ");
                        scanf("%s", novoDados->nome);
                    }
                    
                    printf("\n Digite a nova quantidade do Produto: ");
                    scanf("%d", &novoDados->quantidade);

                    printf("\n Digite o novo valor do Produto: ");
                    scanf("%f", &novoDados->preco);

                    
                    novoDados->codigo = FindCod;
                    
                    
                    update(arquivoProduto, &FindCod, novoDados, comparaProduto, alocaProduto);
                    printf("Produto atualizado com sucesso.\n\n");
                }
                
                else {
                    printf("Produto com Codigo %d nao encontrado para atualizacao.\n\n", FindCod);
                
                }

                break;
            
            case 5:
                printf("Digite o Codigo do Produto que deseja deletar: \n");
                scanf("%d", &FindCod);

                delete(arquivoProduto, &FindCod, comparaProduto, alocaProduto);
                printf("Deletando Produto... \n");

                fclose(arquivoProduto->arquivo);
                int remover = remove("Produto.dat");
                
                // Esse IF Resolve o Bug de permissao negada, nao retirar. Se o bug retornar, tente tirar o if e
                // testar no programa. Se não resolver, mantenha o IF e recrie o arquivo Produto.dat
                //OBS: O bug de permissao negada faz com que, ao tentar deletar um registro, o programa se feche
                if (remover == 0)
                    printf("arq removido");
                else
                    perror("Erro: ");

                rename("arqNovo.dat", "Produto.dat");
                
                arquivoProduto = open("Produto.dat", sizeof(Produto));

                break;
            
               
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Escolha invalida. Tente novamente.\n");
        }
    } while (escolha != 0);

    // Feche os arquivos
    fclose(arquivoProduto->arquivo);
    
    free(arquivoProduto);
    
    return 0;
}

void adicionarProduto(pDFile arq) {
    Produto novoProduto;

    printf("Digite o nome do Produto: ");
    scanf("%s", novoProduto.nome);

    printf("Digite o codigo do Produto: ");
    scanf("%d", &novoProduto.codigo);

    printf("Digite a quantidade do Produto: ");
    scanf("%d", &novoProduto.quantidade);

    printf("Digite o preco do Produto: ");
    scanf("%f", &novoProduto.preco);

    



    createe(arq, &novoProduto);
    printf("Produto adicionado com sucesso.\n\n");
}

void exibirTodosProduto(pDFile arq) {
    // Defina o ponteiro do arquivo no início do arquivo
    fseek(arq->arquivo, 0, SEEK_SET);

    // Leia e exiba todos os Produtos
    Produto produto;
    printf("\n--- Todos os Produtos ---\n");
    while (fread(&produto, arq->tamanhoRegistro, 1, arq->arquivo) == 1) {
        printf("\nNome: %s, Codigo: %d, Quantidade: %d, Preco: %.2f\n", produto.nome, produto.codigo,produto.quantidade, produto.preco);
    }
} 