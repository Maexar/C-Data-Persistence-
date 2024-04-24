#ifndef UPDATE_H
#define UPDATE_H

#include <string.h>
#include "../TAD_Persistencia.h"

void update(pDFile arq, void* chave, void* dados, FuncaoComparacao pfc, FuncaoAloca pfa){
   
   
   //Versao 3 (Funciona!)
    // Encontra a posição do registro correspondente à chave fornecida
    void* registroEncontrado = retrieve(arq, chave, pfc, pfa);

    if (registroEncontrado != NULL) {
        // Atualiza os dados do registro na memória
        memcpy(registroEncontrado, dados, arq->tamanhoRegistro);

        // Posiciona o ponteiro no início do registro no arquivo
        fseek(arq->arquivo, -arq->tamanhoRegistro, SEEK_CUR);

        // Escreve os novos dados do registro no arquivo
        fwrite(registroEncontrado, arq->tamanhoRegistro, 1, arq->arquivo);
        fflush(arq->arquivo); // Força a gravação imediata no arquivo

        // Limpa a memória alocada para o registro encontrado
        free(registroEncontrado);
    } else {
        printf("Registro nao encontrado para atualizacao.\n");
    }


 
}

#endif

