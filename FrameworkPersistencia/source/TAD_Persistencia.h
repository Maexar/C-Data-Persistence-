/* --------------------------
   Tipos de dados
   -------------------------- */
#include "C:\Users\marlo\Desktop\Projetos\Fund. Estr. Dados\Trab. Persist. de Dados\FrameworkPersistencia\source\Cap3\TAD_ListaLinear.h "
typedef struct dFile DFile;
typedef DFile*       pDFile;

typedef int   (*FuncaoComparacao)(void *, void *);
typedef void* (*FuncaoAloca)     ();
typedef void  (*FuncaoImpressao) (void *);
typedef int   (*FuncaoPredicado) (void *);

/* --------------------------
   Operacoes CRUD
   -------------------------- */
pDFile  open      (char[30], int);
void    createe   (pDFile, void*);                          // dados
void*   retrieve  (pDFile, void*, FuncaoComparacao, FuncaoAloca);        // chave
void    update    (pDFile, void*, void*, FuncaoComparacao, FuncaoAloca); // chave e os dados
void    delete    (pDFile, void*, FuncaoComparacao, FuncaoAloca);        // chave
void    close     (pDFile);

pDLista queryAll  (pDFile, FuncaoAloca);
pDLista queryBy   (pDFile, FuncaoPredicado); // query
void   persistAll (pDFile, pDLista);




