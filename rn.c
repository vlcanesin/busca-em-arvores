#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EDlib.h"

pNodoRN* Inicializa_RN() {

    return NULL;      // Inicializa o ponteiro da Árvore

}

pNodoRN* _Rot_dir_RN(pNodoRN *A) {

    //printf("\nROTACAO A DIREITA\n");

    pNodoRN *p = A->esq;

    A->esq = p->dir;
    p->dir = A;         // Operações da rotação à direita

    p->cor = 'N';       // Atualização das cores
    p->esq->cor = 'R';
    p->dir->cor = 'R';

    return p;           // p vira a raiz da subárvore

}

pNodoRN* _Rot_dupla_dir_RN(pNodoRN *A) {

    //printf("\nROTACAO DUPLA A DIREITA\n");

    pNodoRN *p = A->esq;
    pNodoRN *q = p->dir;

    p->dir = q->esq;
    q->esq = p;         // Rotação à esquerda
    A->esq = q->dir;
    q->dir = A;         // Rotação à direita

    q->cor = 'N';       // Atualização das cores
    q->esq->cor = 'R';
    q->dir->cor = 'R';

    return q;   // q vira a raíz

}

pNodoRN* _Rot_esq_RN(pNodoRN *A) {

    //printf("\nROTACAO A ESQUERDA\n");

    pNodoRN *p = A->dir;
    A->dir = p->esq;
    p->esq = A;         // Operações da rotação à esquerda

    p->cor = 'N';       // Atualização das cores
    p->esq->cor = 'R';
    p->dir->cor = 'R';

    return p;           // p vira a raiz da subárvore

}

pNodoRN* _Rot_dupla_esq_RN(pNodoRN *A) {

    //printf("\nROTACAO DUPLA A ESQUERDA\n");

    pNodoRN *p = A->dir;
    pNodoRN *q = p->esq;

    p->esq = q->dir;
    q->dir = p;         // Rotação à direita
    A->dir = q->esq;
    q->esq = A;         // Rotação à esquerda

    q->cor = 'N';       // Atualização das cores
    q->esq->cor = 'R';
    q->dir->cor = 'R';

    return q;   // q vira a raíz

}

pNodoRN* Insere_RN(pNodoRN *A, Dado info_nodo[], int *ok, int raiz, char origem, int *tam_texto, int *tam_inter) {

    if(A == NULL) {   // Um nodo folha foi atingido

        A = (pNodoRN*) malloc(sizeof(pNodoRN));          // Aloca nodo
        strcpy(A->info, info_nodo);                      // Insere nodo na árvore
        A->dir = NULL;
        A->esq = NULL;

        A->cor = 'R';                                    // O nodo é inserido como vermelho
        A->origem = origem;                                // A palavra veio do texto A

        *tam_texto = *tam_texto + 1;   // Um elemento novo foi inserido: incrementa o número de palavras
        *ok = 1;                       // e inicia processo de balanceamento

    }

    else {

        int dif = strcmp(info_nodo, A->info);

        if(dif < 0) {                                                                   // Se info_nodo for menor alfabeticamente,
            A->esq = Insere_RN(A->esq, info_nodo, ok, 0, origem, tam_texto, tam_inter);   // insere na esquerda
            // Obs1: o nó analisado deixa de ser a raíz ; Obs2: o filho esquerdo nunca é NULL, já que foi inserido.

            if(*ok) {                                               // Se há balanceamento para fazer:
                if(A->esq->cor == 'R') {                            // Só é preciso fazer algo se o filho é vermelho
                    if(A->esq->esq != NULL) {                       // Só é preciso fazer algo caso o nodo seja avô
                        if(A->esq->esq->cor == 'R') {
                            if(A->dir != NULL && A->dir->cor == 'R') {  // Só é preciso trocar as cores se o da direita é vermelho
                                // OBS: é certeza que o avô é preto; é impossível que haja uma sequência de 3 nós vermelhos
                                A->cor = 'R';                           // Raíz vira vermelha (NÃO É GARANTIDO QUE A ÁRVORE ESTÁ BALANCEADA),
                                A->esq->cor = 'N';                      // Pai vira preto e
                                A->dir->cor = 'N';                      // Tio vira preto
                            } else {
                                A = _Rot_dir_RN(A);                     // É preciso fazer uma rotação, que garantidamente balanceia a árvore (raíz é preta)
                            }
                        }   // Neto é preto, continua a busca pois pai e avô ou pai e filho podem ser vermelhos
                    } else if(A->esq->dir != NULL) {                // Outra verificação de avô
                        if(A->esq->dir->cor == 'R') {
                            if(A->dir != NULL && A->dir->cor == 'R') {  // Só é preciso trocar as cores se o da direita é vermelho
                                // OBS: é certeza que o avô é preto; é impossível que haja uma sequência de 3 nós vermelhos
                                A->cor = 'R';                           // Raíz vira vermelha (NÃO É GARANTIDO QUE A ÁRVORE ESTÁ BALANCEADA),
                                A->esq->cor = 'N';                      // Pai vira preto e
                                A->dir->cor = 'N';                      // Tio vira preto
                            } else {
                                A = _Rot_dupla_dir_RN(A);               // É preciso fazer uma rotação, que garantidamente balanceia a árvore (raíz é preta)
                            }
                        }   // Neto é preto, continua a busca pois pai e avô ou pai e filho podem ser vermelhos
                    }   // Nó ainda é pai, é preciso subir um nível
                } else *ok = 0;     // Não tem como um filho ser preto e a árvore estar desbalanceada
            }

        } else if(dif > 0) {                                                            // Se info_nodo for maior alfabeticamente,
            A->dir = Insere_RN(A->dir, info_nodo, ok, 0, origem, tam_texto, tam_inter);   // insere na direita
            // Obs1: o nó analisado deixa de ser a raíz ; Obs2: o filho direito nunca é NULL, já que foi inserido.

            if(*ok) {                                               // Se há balanceamento para fazer:
                if(A->dir->cor == 'R') {                            // Só é preciso fazer algo se o filho é vermelho
                    if(A->dir->dir != NULL) {                       // Só é preciso fazer algo caso o nodo seja avô
                        if(A->dir->dir->cor == 'R') {
                            if(A->esq != NULL && A->esq->cor == 'R') {  // Só é preciso trocar as cores se o da esquerda é vermelho
                                // OBS: é certeza que o avô é preto; é impossível que haja uma sequência de 3 nós vermelhos
                                A->cor = 'R';                           // Raíz vira vermelha (NÃO É GARANTIDO QUE A ÁRVORE ESTÁ BALANCEADA),
                                A->esq->cor = 'N';                      // Tio vira preto e
                                A->dir->cor = 'N';                      // Pai vira preto
                            } else {
                                A = _Rot_esq_RN(A);                     // É preciso fazer uma rotação, que garantidamente balanceia a árvore (raíz é preta)
                            }
                        }   // Neto é preto, continua a busca pois pai e avô ou pai e filho podem ser vermelhos
                    } else if(A->dir->esq != NULL) {                // Outra verificação de avô
                        if(A->dir->esq->cor == 'R') {
                            if(A->esq != NULL && A->esq->cor == 'R') {  // Só é preciso trocar as cores se o da esquerda é vermelho
                                // OBS: é certeza que o avô é preto; é impossível que haja uma sequência de 3 nós vermelhos
                                A->cor = 'R';                           // Raíz vira vermelha (NÃO É GARANTIDO QUE A ÁRVORE ESTÁ BALANCEADA),
                                A->esq->cor = 'N';                      // Tio vira preto e
                                A->dir->cor = 'N';                      // Pai vira preto
                            } else {
                                A = _Rot_dupla_esq_RN(A);               // É preciso fazer uma rotação, que garantidamente balanceia a árvore (raíz é preta)
                            }
                        }   // Neto é preto, continua a busca pois pai e avô ou pai e filho podem ser vermelhos
                    }   // Nó ainda é pai, é preciso subir um nível
                } else *ok = 0;     // Não tem como um filho ser preto e a árvore estar desbalanceada
            }
        } else {                                         // Se info_nodo for iqual, não segue a busca na árvore (e retorna em seguida)
            if(origem == 'B' && A->origem == 'A') {        // Se a palavra analisada for do texto B e a palavra da árvore não veio do texto B,
                *tam_inter = *tam_inter + 1;             // incrementa o tamanho da interseção,
                *tam_texto = *tam_texto + 1;             // incrementa o número de palavras do texto B e
                A->origem = 'B';                         // marca que a palavra da árvore também está presente no texto B.
            }
        }

    }

    if(raiz == 1) A->cor = 'N';   // A raíz sempre é preta

    return A;

}

// Funções de DEBUG:

int Consulta_RN(pNodoRN *A, Dado info_nodo[]) {

    if(A == NULL) return 0;     // Se (sub)árvore é vazia, o elemento não está lá

    int dif = strcmp(info_nodo, A->info);

    if(dif < 0) return Consulta_RN(A->esq, info_nodo); // Se info_nodo é menor, procura à esquerda
    if(dif > 0) return Consulta_RN(A->dir, info_nodo); // Se info_nodo é maior, procura à direita

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
