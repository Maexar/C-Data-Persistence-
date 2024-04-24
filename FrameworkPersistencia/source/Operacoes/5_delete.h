#ifndef DELETE_H
#define DELETE_H

#include "../TAD_Persistencia.h"
#include "../persistencia.h"

void delete(pDFile arq, void* chave, FuncaoComparacao pfc, FuncaoAloca pfa) {
   
   //Versao 3 (Funcional)

   pDFile arqNovo = fopen("arqNovo.dat", "w+b");

   void* buffer = malloc(arq->tamanhoRegistro);
   rewind(arq->arquivo);


   while(fread(buffer,arq->tamanhoRegistro, 1, arq->arquivo)== 1){
        if(pfc(buffer,chave)!= 0){
            fwrite(buffer, arq->tamanhoRegistro, 1, arqNovo);
        }

   }

   fclose(arqNovo);
   fclose(arq);
   return; 
   
}

#endif

