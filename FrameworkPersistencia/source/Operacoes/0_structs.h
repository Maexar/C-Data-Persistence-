#ifndef STRUCT_FILE_H
#define STRUCT_FILE_H

/* --------------------------
   Tipos de dados
   -------------------------- */
struct dFile{
  FILE* arquivo;         // nome do arquivo em disco
  int   tamanhoRegistro; // qtde bytes do tipo de dado (struct)
};

typedef struct{
    char nome[50];
    int cpf;
    
}Cliente;

typedef struct{
    int id;
    char date[8];
    int  cod;
    int cpf;
    int quantidade;
    float valor;
    
}Venda;

typedef struct {
    char nome[50];
    int codigo;
    int quantidade;
    float preco;
   
}Produto;

#endif
