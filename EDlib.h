#ifndef EDLIB_H
#define EDLIB_H

// ======= DEFINI��ES ======= //

typedef char Dado;    // Palavras

typedef struct nodoAVL {    // AVL
    Dado info[256];
    int FB;
    struct nodoAVL *esq, *dir;
} pNodoAVL;

typedef struct nodoRN {    // �rvore Rubro Negra (RN)
    Dado info[256];
    char cor, origem;           // origem indica se o nodo veio do texto B
    struct nodoRN *esq, *dir;
} pNodoRN;

// ========== AVL =========== //

pNodoAVL* Inicializa_AVL();
// Retorna NULL

pNodoAVL* Insere_AVL(pNodoAVL *A, Dado info_nodo[], int *ok);
// Insere elemento na �rvore respeitando as regras de balanceamento da AVL.
// Retorna a nova �rvore.

int Consulta_AVL(pNodoAVL *A, Dado info_nodo[]);
// Verifica se o nodo est� na �rvore. Retorna
// 1 se sim, 0 caso contr�rio.

    // Fun��es de DEBUG:

    void Cent_Esq_AVL(pNodoAVL* raiz);
    // Caminhamento central � esquerda.

    void Imprime_Niveis_AVL(pNodoAVL* raiz, int nivel);
    // Imprime a �rvore em n�veis (cam. pr�-fixado � esquerda)


// ========== RN =========== //

pNodoRN* Inicializa_RN();
// Retorna NULL

pNodoRN* Insere_RN(pNodoRN *A, Dado info_nodo[], int *ok, int raiz, char origem, int *tam_texto, int *tam_inter);
// Insere elemento na �rvore respeitando as regras de balanceamento da �rvore RB.
// Se origem � "A", n�o conta interse��es. Se origem � "B", conta interse��es;
// Adiciona ao n�mero de palavras em tam_texto e ao tamanho da interse��o dos dois textos em tam_inter;
// Retorna a nova �rvore.

    // Fun��es de DEBUG:

    int Consulta_RN(pNodoRN *A, Dado info_nodo[]);
    // Verifica se o nodo est� na �rvore. Retorna
    // 1 se sim, 0 caso contr�rio.

    void Cent_Esq_RN(pNodoRN* raiz);
    // Caminhamento central � esquerda.

    void Imprime_Niveis_RN(pNodoRN* raiz, int nivel);
    // Imprime a �rvore em n�veis (cam. pr�-fixado � esquerda)


// ======== LEITURA ========= //

void Ler_TXT(
    pNodoRN** RN, pNodoAVL** SW,
    char path[], char modo,
    char origem, int *tam_texto, int *tam_inter
);
// L� as palavras do arquivo <path>.txt;
// Se modo � "S", salva palavras na �rvore de stopwords; se modo � "P", salva na �rvore de palavras;
// Se origem � "A", n�o conta interse��es. Se origem � "B", conta interse��es;
// Salva o n�mero de palavras em tam_texto e o tamanho da interse��o dos dois textos em tam_inter;
// Retorna a �rvore gerada a partir das passagens por refer�ncia.

#endif
