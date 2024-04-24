#ifndef QUERY_H
#define QUERY_H

#include "../persistencia.h" 

 
pDLista query(pDFile arq, FuncaoPredicado pred) {

 if (arq->arquivo == NULL){
      printf("arquivo nao encontrado!!!");
      return NULL;
   }

   pDLista lista = criarLista();

   rewind(arq->arquivo);
   int result;

   do{
      void *dados = malloc(arq->tamanhoRegistro);
      result = fread(dados, arq->tamanhoRegistro, 1, arq->arquivo);
      if (result == 0)
        continue;
      printf("%f", ((Venda *) dados) ->valor);
      if (pred(dados) == 1)
       incluirInfo(lista, dados);
        
    
   } while(result!=0);
     
   return lista;
}




#endif



//é um filtro. ex: pesquisar vendas com valor acima de R$20

// Transforma o arquivo em lista

/*
 fseek(arq->arquivo, 0, SEEK_SET); 

    Produto produto;
    while (fread(&produto, arq->tamanhoRegistro, 1, arq->arquivo) == 1) {
        // Realiza a comparação de acordo com o tipo fornecido
        if (tipo == 0) { // Busca por igualdade
            if (pred(&produto, chave, valorLimite, tipo)) {
                incluirInfo(resultado, &produto); 
            }
        } else if (tipo == 1) { // Busca por maior ou igual
            if (pred(&produto, chave, valorLimite, tipo)) {
                incluirInfo(resultado, &produto); 
            }
        } else if (tipo == 2) { // Busca por menor ou igual
            if (pred(&produto, chave, valorLimite, tipo)) {
                incluirInfo(resultado, &produto); 
            }
        }
    }

    return resultado;
*/