#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EDlib.h"

pNodoRN* Inicializa_RN() {

    return NULL;      // Inicializa o ponteiro da �rvore

}

pNodoRN* _Rot_dir_RN(pNodoRN *A) {

    //printf("\nROTACAO A DIREITA\n");

    pNodoRN *p = A->esq;

    A->esq = p->dir;
    p->dir = A;         // Opera��es da rota��o � direita

    p->cor = 'N';       // Atualiza��o das cores
    p->esq->cor = 'R';
    p->dir->cor = 'R';

    return p;           // p vira a raiz da sub�rvore

}

pNodoRN* _Rot_dupla_dir_RN(pNodoRN *A) {

    //printf("\nROTACAO DUPLA A DIREITA\n");

    pNodoRN *p = A->esq;
    pNodoRN *q = p->dir;

    p->dir = q->esq;
    q->esq = p;         // Rota��o � esquerda
    A->esq = q->dir;
    q->dir = A;         // Rota��o � direita

    q->cor = 'N';       // Atualiza��o das cores
    q->esq->cor = 'R';
    q->dir->cor = 'R';

    return q;   // q vira a ra�z

}

pNodoRN* _Rot_esq_RN(pNodoRN *A) {

    //printf("\nROTACAO A ESQUERDA\n");

    pNodoRN *p = A->dir;
    A->dir = p->esq;
    p->esq = A;         // Opera��es da rota��o � esquerda

    p->cor = 'N';       // Atualiza��o das cores
    p->esq->cor = 'R';
    p->dir->cor = 'R';

    return p;           // p vira a raiz da sub�rvore

}

pNodoRN* _Rot_dupla_esq_RN(pNodoRN *A) {

    //printf("\nROTACAO DUPLA A ESQUERDA\n");

    pNodoRN *p = A->dir;
    pNodoRN *q = p->esq;

    p->esq = q->dir;
    q->dir = p;         // Rota��o � direita
    A->dir = q->esq;
    q->esq = A;         // Rota��o � esquerda

    q->cor = 'N';       // Atualiza��o das cores
    q->esq->cor = 'R';
    q->dir->cor = 'R';

    return q;   // q vira a ra�z

}

pNodoRN* Insere_RN(pNodoRN *A, Dado info_nodo[], int *ok, int raiz, char origem, int *tam_texto, int *tam_inter) {

    if(A == NULL) {   // Um nodo folha foi atingido

        A = (pNodoRN*) malloc(sizeof(pNodoRN));          // Aloca nodo
        strcpy(A->info, info_nodo);                      // Insere nodo na �rvore
        A->dir = NULL;
        A->esq = NULL;

        A->cor = 'R';                                    // O nodo � inserido como vermelho
        A->origem = origem;                                // A palavra veio do texto A

        *tam_texto = *tam_texto + 1;   // Um elemento novo foi inserido: incrementa o n�mero de palavras
        *ok = 1;                       // e inicia processo de balanceamento

    }

    else {

        int dif = strcmp(info_nodo, A->info);

        if(dif < 0) {                                                                   // Se info_nodo for menor alfabeticamente,
            A->esq = Insere_RN(A->esq, info_nodo, ok, 0, origem, tam_texto, tam_inter);   // insere na esquerda
            // Obs1: o n� analisado deixa de ser a ra�z ; Obs2: o filho esquerdo nunca � NULL, j� que foi inserido.

            if(*ok) {                                               // Se h� balanceamento para fazer:
                if(A->esq->cor == 'R') {                            // S� � preciso fazer algo se o filho � vermelho
                    if(A->esq->esq != NULL) {                       // S� � preciso fazer algo caso o nodo seja av�
                        if(A->esq->esq->cor == 'R') {
                            if(A->dir != NULL && A->dir->cor == 'R') {  // S� � preciso trocar as cores se o da direita � vermelho
                                // OBS: � certeza que o av� � preto; � imposs�vel que haja uma sequ�ncia de 3 n�s vermelhos
                                A->cor = 'R';                           // Ra�z vira vermelha (N�O � GARANTIDO QUE A �RVORE EST� BALANCEADA),
                                A->esq->cor = 'N';                      // Pai vira preto e
                                A->dir->cor = 'N';                      // Tio vira preto
                            } else {
                                A = _Rot_dir_RN(A);                     // � preciso fazer uma rota��o, que garantidamente balanceia a �rvore (ra�z � preta)
                            }
                        }   // Neto � preto, continua a busca pois pai e av� ou pai e filho podem ser vermelhos
                    } else if(A->esq->dir != NULL) {                // Outra verifica��o de av�
                        if(A->esq->dir->cor == 'R') {
                            if(A->dir != NULL && A->dir->cor == 'R') {  // S� � preciso trocar as cores se o da direita � vermelho
                                // OBS: � certeza que o av� � preto; � imposs�vel que haja uma sequ�ncia de 3 n�s vermelhos
                                A->cor = 'R';                           // Ra�z vira vermelha (N�O � GARANTIDO QUE A �RVORE EST� BALANCEADA),
                                A->esq->cor = 'N';                      // Pai vira preto e
                                A->dir->cor = 'N';                      // Tio vira preto
                            } else {
                                A = _Rot_dupla_dir_RN(A);               // � preciso fazer uma rota��o, que garantidamente balanceia a �rvore (ra�z � preta)
                            }
                        }   // Neto � preto, continua a busca pois pai e av� ou pai e filho podem ser vermelhos
                    }   // N� ainda � pai, � preciso subir um n�vel
                } else *ok = 0;     // N�o tem como um filho ser preto e a �rvore estar desbalanceada
            }

        } else if(dif > 0) {                                                            // Se info_nodo for maior alfabeticamente,
            A->dir = Insere_RN(A->dir, info_nodo, ok, 0, origem, tam_texto, tam_inter);   // insere na direita
            // Obs1: o n� analisado deixa de ser a ra�z ; Obs2: o filho direito nunca � NULL, j� que foi inserido.

            if(*ok) {                                               // Se h� balanceamento para fazer:
                if(A->dir->cor == 'R') {                            // S� � preciso fazer algo se o filho � vermelho
                    if(A->dir->dir != NULL) {                       // S� � preciso fazer algo caso o nodo seja av�
                        if(A->dir->dir->cor == 'R') {
                            if(A->esq != NULL && A->esq->cor == 'R') {  // S� � preciso trocar as cores se o da esquerda � vermelho
                                // OBS: � certeza que o av� � preto; � imposs�vel que haja uma sequ�ncia de 3 n�s vermelhos
                                A->cor = 'R';                           // Ra�z vira vermelha (N�O � GARANTIDO QUE A �RVORE EST� BALANCEADA),
                                A->esq->cor = 'N';                      // Tio vira preto e
                                A->dir->cor = 'N';                      // Pai vira preto
                            } else {
                                A = _Rot_esq_RN(A);                     // � preciso fazer uma rota��o, que garantidamente balanceia a �rvore (ra�z � preta)
                            }
                        }   // Neto � preto, continua a busca pois pai e av� ou pai e filho podem ser vermelhos
                    } else if(A->dir->esq != NULL) {                // Outra verifica��o de av�
                        if(A->dir->esq->cor == 'R') {
                            if(A->esq != NULL && A->esq->cor == 'R') {  // S� � preciso trocar as cores se o da esquerda � vermelho
                                // OBS: � certeza que o av� � preto; � imposs�vel que haja uma sequ�ncia de 3 n�s vermelhos
                                A->cor = 'R';                           // Ra�z vira vermelha (N�O � GARANTIDO QUE A �RVORE EST� BALANCEADA),
                                A->esq->cor = 'N';                      // Tio vira preto e
                                A->dir->cor = 'N';                      // Pai vira preto
                            } else {
                                A = _Rot_dupla_esq_RN(A);               // � preciso fazer uma rota��o, que garantidamente balanceia a �rvore (ra�z � preta)
                            }
                        }   // Neto � preto, continua a busca pois pai e av� ou pai e filho podem ser vermelhos
                    }   // N� ainda � pai, � preciso subir um n�vel
                } else *ok = 0;     // N�o tem como um filho ser preto e a �rvore estar desbalanceada
            }
        } else {                                         // Se info_nodo for iqual, n�o segue a busca na �rvore (e retorna em seguida)
            if(origem == 'B' && A->origem == 'A') {        // Se a palavra analisada for do texto B e a palavra da �rvore n�o veio do texto B,
                *tam_inter = *tam_inter + 1;             // incrementa o tamanho da interse��o,
                *tam_texto = *tam_texto + 1;             // incrementa o n�mero de palavras do texto B e
                A->origem = 'B';                         // marca que a palavra da �rvore tamb�m est� presente no texto B.
            }
        }

    }

    if(raiz == 1) A->cor = 'N';   // A ra�z sempre � preta

    return A;

}

// Fun��es de DEBUG:

int Consulta_RN(pNodoRN *A, Dado info_nodo[]) {

    if(A == NULL) return 0;     // Se (sub)�rvore � vazia, o elemento n�o est� l�

    int dif = strcmp(info_nodo, A->info);

    if(dif < 0) return Consulta_RN(A->esq, info_nodo); // Se info_nodo � menor, procura � esquerda
    if(dif > 0) return Consulta_RN(A->dir, info_nodo); // Se info_nodo � maior, procura � direita

    return 1;                   // Se encontrou o elemento, retorna 1

}

void Cent_Esq_RN(pNodoRN* raiz) {

    if (raiz != NULL) {
        Cent_Esq_RN(raiz->esq);
        printf("%s ",raiz->info);
        Cent_Esq_RN(raiz->dir);
    }

}

void Imprime_Niveis_RN(pNodoRN* raiz, int nivel) {

    if (raiz != NULL) {

        int i;
        for(i = 0; i < nivel; i++) printf("=");

        printf("%s (cor = %c)\n",raiz->info, raiz->cor);
        Imprime_Niveis_RN(raiz->esq, nivel + 1);
        Imprime_Niveis_RN(raiz->dir, nivel + 1);

    }

}
