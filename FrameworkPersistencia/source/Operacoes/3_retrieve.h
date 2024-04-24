


#ifndef RETRIEVE_H
#define RETRIEVE_H

#include "../persistencia.h"

void* retrieve(pDFile arq, void* chave, FuncaoComparacao pfc, FuncaoAloca pfa) {
      
    pDLista listaGeral;
    listaGeral = queryAll(arq, pfa);

        pNoh pGeralPos = listaGeral->primeiro;

        int i = 1;

        while(i <= listaGeral->quantidade){
            if (pfc(pGeralPos->info, chave) == 0)
                return pGeralPos->info;
            pGeralPos = pGeralPos->prox;
            i++;
    }
      return NULL;
}



#endif  
//pesquisa