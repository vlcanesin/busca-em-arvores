#ifndef EDLIB_H
#define EDLIB_H

// ======= DEFINIÇÕES ======= //

typedef char Dado;    // Palavras

typedef struct nodoAVL {    // AVL
    Dado info[256];
    int FB;
    struct nodoAVL *esq, *dir;
} pNodoAVL;

typedef struct nodoRN {    // Árvore Rubro Negra (RN)
    Dado info[256];
    char cor, origem;           // origem indica se o nodo veio do texto B
    struct nodoRN *esq, *dir;
} pNodoRN;

// ========== AVL =========== //

pNodoAVL* Inicializa_AVL();
// Retorna NULL

pNodoAVL* Insere_AVL(pNodoAVL *A, Dado info_nodo[], int *ok);
// Insere elemento na árvore respeitando as regras de balanceamento da AVL.
// Retorna a nova árvore.

int Consulta_AVL(pNodoAVL *A, Dado info_nodo[]);
// Verifica se o nodo está na árvore. Retorna
// 1 se sim, 0 caso contrário.

    // Funções de DEBUG:

    void Cent_Esq_AVL(pNodoAVL* raiz);
    // Caminhamento central à esquerda.

    void Imprime_Niveis_AVL(pNodoAVL* raiz, int nivel);
    // Imprime a árvore em níveis (cam. pré-fixado à esquerda)


// ========== RN =========== //

pNodoRN* Inicializa_RN();
// Retorna NULL

pNodoRN* Insere_RN(pNodoRN *A, Dado info_nodo[], int *ok, int raiz, char origem, int *tam_texto, int *tam_inter);
// Insere elemento na árvore respeitando as regras de balanceamento da árvore RB.
// Se origem é "A", não conta interseções. Se origem é "B", conta interseções;
// Adiciona ao número de palavras em tam_texto e ao tamanho da interseção dos dois textos em tam_inter;
// Retorna a nova árvore.

    // Funções de DEBUG:

    int Consulta_RN(pNodoRN *A, Dado info_nodo[]);
    // Verifica se o nodo está na árvore. Retorna
    // 1 se sim, 0 caso contrário.

    void Cent_Esq_RN(pNodoRN* raiz);
    // Caminhamento central à esquerda.

    void Imprime_Niveis_RN(pNodoRN* raiz, int nivel);
    // Imprime a árvore em níveis (cam. pré-fixado à esquerda)


// ======== LEITURA ========= //

void Ler_TXT(
    pNodoRN** RN, pNodoAVL** SW,
    char path[], char modo,
    char origem, int *tam_texto, int *tam_inter
);
// Lê as palavras do arquivo <path>.txt;
// Se modo é "S", salva palavras na árvore de stopwords; se modo é "P", salva na árvore de palavras;
// Se origem é "A", não conta interseções. Se origem é "B", conta interseções;
// Salva o número de palavras em tam_texto e o tamanho da interseção dos dois textos em tam_inter;
// Retorna a árvore gerada a partir das passagens por referência.

#endif
