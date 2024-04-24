#ifndef OPEN_H
#define OPEN_H

pDFile open(char arquivo[30], int tamanho){

    pDFile pdf = (pDFile) malloc(sizeof(struct dFile));

    pdf->arquivo         = fopen(arquivo, "a+b"); // mudar "r" para "w" quando precisar recriar o arquivo. Depois trocar para r dnv
    pdf->tamanhoRegistro = tamanho;

    return pdf;
}


#endif

