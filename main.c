#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "EDlib.h"

int main(int argc, char *argv[]) {

    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados

    clock_t start, end; //para contar o tempo decorrido

    if (argc!=4) { //o numero de parametros esperado é 4: programa (argv[0]), texto A (argv[1]), texto B (argv[2]) e stopwords (argv[3])

        printf ("Número incorreto de parâmetros.\nPara chamar o programa digite: main <texto_A> <texto_B> <stopwords>\n");
        return 1;

    } else {

        start = clock(); // Inicia a contagem do tempo

        pNodoAVL *stopwords = Inicializa_AVL();  // AVL que guarda as stopwords
        pNodoRN *palavras = Inicializa_RN();     // RN que guarda tanto as palavras do texto A como do texto B

        int tam_textoA = 0, tam_textoB = 0, tam_inter = 0, x;

        Ler_TXT(&palavras, &stopwords,
                argv[3], 'S',
                'x', &x, &x);               // Lê stopwords
        //Cent_Esq_AVL(stopwords);

        Ler_TXT(&palavras, &stopwords,
                argv[1], 'P',
                'A', &tam_textoA, &tam_inter);   // Lê palavras do texto A
        //Cent_Esq_RN(palavras);
        Ler_TXT(&palavras, &stopwords,
                argv[2], 'P',
                'B', &tam_textoB, &tam_inter);   // Lê palavras do texto A
        //Cent_Esq_RN(palavras);

        end = clock(); // Encerra a contagem do tempo
        float miliseconds = (float)(end - start) / CLOCKS_PER_SEC * 1000; // Calcula o tempo decorrido

        //printf("\n'%s': %d palavras distintas\n", argv[1], tam_textoA);
        //printf("'%s': %d palavras distintas\n", argv[2], tam_textoB);
        //printf("Intersec.: %d palavras\n", tam_inter);
        printf("Jaccard = %.4f\n", (tam_textoA + tam_textoB > 0) ? (float)tam_inter/(tam_textoA + tam_textoB - tam_inter) : 1.00);
        printf("Tempo: %.2f ms\n", miliseconds);

        return 0;

    }

}
