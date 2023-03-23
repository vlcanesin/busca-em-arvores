#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EDlib.h"

pNodoAVL* Inicializa_AVL() {

    return NULL;    // Inicializa o ponteiro da �rvore

}

// _Rot_dir(): fun��o que executa uma
// rota��o � direita.
pNodoAVL* _Rot_dir(pNodoAVL *A) {

    //printf("\nROTACAO A DIREITA\n");

    pNodoAVL *p = A->esq;
    A->esq = p->dir;
    p->dir = A;         // Opera��es da rota��o � direita

    A->FB = 0;          // A fica balanceados
    return p;           // p vira a raiz da sub�rvore

}

// _Rot_dupla_dir(): fun��o que executa uma
// rota��o dupla � direita.
pNodoAVL* _Rot_dupla_dir(pNodoAVL *A) {

    //printf("\nROTACAO DUPLA A DIREITA\n");

    pNodoAVL *p = A->esq;
    pNodoAVL *q = p->dir;

    p->dir = q->esq;
    q->esq = p;         // Rota��o � esquerda
    A->esq = q->dir;
    q->dir = A;         // Rota��o � direita

    if(q->FB == 1) A->FB = -1;
    else A->FB = 0;
    if(q->FB == -1) p->FB = 1;      // Ajustes dos FBs
    else p->FB = 0;

    return q;   // q vira a ra�z

}

// _Rot_dir(): fun��o que executa uma
// rota��o � direita.
pNodoAVL* _Rot_esq(pNodoAVL *A) {

    //printf("\nROTACAO A ESQUERDA\n");

    pNodoAVL *p = A->dir;
    A->dir = p->esq;
    p->esq = A;         // Opera��es da rota��o � esquerda

    A->FB = 0;          // A fica balanceado
    return p;           // p vira a raiz da sub�rvore

}

// _Rot_dupla_dir(): fun��o que executa uma
// rota��o dupla � direita.
pNodoAVL* _Rot_dupla_esq(pNodoAVL *A) {

    //printf("\nROTACAO DUPLA A ESQUERDA\n");

    pNodoAVL *p = A->dir;
    pNodoAVL *q = p->esq;

    p->esq = q->dir;
    q->dir = p;         // Rota��o � direita
    A->dir = q->esq;
    q->esq = A;         // Rota��o � esquerda

    if(q->FB == -1) A->FB = 1;
    else A->FB = 0;
    if(q->FB == 1) p->FB = -1;      // Ajustes dos FBs
    else p->FB = 0;

    return q;   // q vira a ra�z

}

// _B_esq(): fun��o de rebalanceamento
// para inser��es � esquerda.
pNodoAVL* _B_esq(pNodoAVL *A, int *ok) {

    pNodoAVL *esq = A->esq;
    if(esq->FB == 1) A = _Rot_dir(A);   // Se esq->FB for 1, basta fazer uma rota��o � direita
    else A = _Rot_dupla_dir(A);         // Caso contr�rio (se for -1), � preciso torn�-lo 1 para
                                        // depois fazer a rota��o � direita (fazendo uma rot. dupla)

    *ok = 0;    // Opera��o preserva a altura da �rvore (n�o � preciso verificar nodos acima)
    A->FB = 0;  // Ra�z � balanceada
    return A;   // Retorna nova ra�z

}

// _B_dir(): fun��o de rebalanceamento
// para inser��es � direita.
pNodoAVL* _B_dir(pNodoAVL *A, int *ok) {

    pNodoAVL *dir = A->dir;
    if(dir->FB == -1) A = _Rot_esq(A);  // Se dir->FB for -1, basta fazer uma rota��o � esquerda
    else A = _Rot_dupla_esq(A);         // Caso contr�rio (se for 1), � preciso torn�-lo -1 para
                                        // depois fazer a rota��o � esquerda (fazendo uma rot. dupla)

    *ok = 0;    // Opera��o preserva a altura da �rvore (n�o � preciso verificar nodos acima)
    A->FB = 0;  // Ra�z � balanceada
    return A;   // Retorna nova raiz

}

pNodoAVL* Insere_AVL(pNodoAVL *A, Dado info_nodo[], int *ok) {

    if(A == NULL) { // Se o filho de um nodo folha for atingido

        A = (pNodoAVL*) malloc(sizeof(pNodoAVL));          // Aloca nodo
        strcpy(A->info, info_nodo);                        // Insere nodo na �rvore
        A->dir = NULL;
        A->esq = NULL;
        A->FB = 0;

        *ok = 1;                       // e inicia processo de ajuste dos fatores de balanceamento

    } else {

        int dif = strcmp(info_nodo, A->info);
        if(dif < 0) {                                        // Se info_nodo for menor alfabeticamente,
            A->esq = Insere_AVL(A->esq, info_nodo, ok);      // insere na esquerda
            if(*ok) {
                switch(A->FB) {                          // Se h� balanceamento para fazer:
                    case -1: A->FB = 0; *ok = 0; break;  // �rvore � rebalanceada com altura preservada
                    case 0: A->FB = 1; break;            // �rvore � desbalanceada SEM preservar a altura
                    case 1: A = _B_esq(A, ok); break;    // �rvore precisa ser rebalanceada (PRESERVA a altura)
                }
            }
        } else if(dif > 0) {                                 // Se info_nodo for maior alfabeticamente,
            A->dir = Insere_AVL(A->dir, info_nodo, ok);      // insere na direita
            if(*ok) {
                switch(A->FB) {                          // Se h� balanceamento para fazer:
                    case 1: A->FB = 0; *ok = 0; break;   // �rvore � rebalanceada com altura preservada
                    case 0: A->FB = -1; break;           // �rvore � desbalanceada SEM preservar a altura
                    case -1: A = _B_dir(A, ok); break;   // �rvore precisa ser rebalanceada (PRESERVA a altura)
                }
            }
        }

    }

    return A;

}

int Consulta_AVL(pNodoAVL *A, Dado info_nodo[]) {

    if(A == NULL) return 0;     // Se (sub)�rvore � vazia, o elemento n�o est� l�

    int dif = strcmp(info_nodo, A->info);

    if(dif < 0) return Consulta_AVL(A->esq, info_nodo); // Se info_nodo � menor, procura � esquerda
    if(dif > 0) return Consulta_AVL(A->dir, info_nodo); // Se info_nodo � maior, procura � direita

    return 1;                   // Se encontrou o elemento, retorna 1

}

// Fun��es de DEBUG:

void Cent_Esq_AVL(pNodoAVL* raiz) {

    if (raiz != NULL) {
        Cent_Esq_AVL(raiz->esq);
        printf("%s ",raiz->info);
        Cent_Esq_AVL(raiz->dir);
    }

}

void Imprime_Niveis_AVL(pNodoAVL* raiz, int nivel) {

    if (raiz != NULL) {

        int i;
        for(i = 0; i < nivel; i++) printf("=");

        printf("%s (FB = %d)\n",raiz->info, raiz->FB);
        Imprime_Niveis_AVL(raiz->esq, nivel + 1);
        Imprime_Niveis_AVL(raiz->dir, nivel + 1);

    }

}
