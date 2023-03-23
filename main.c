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

        pNodoAVL *stopwords;  // AVL que guarda as stopwords
        stopwords = Inicializa_AVL();
        stopwords = Ler_Stopwords(stopwords, argv[3]);     // Lê stopwords
        //Cent_Esq_AVL(stopwords);

        int tam_textoA = 0, tam_textoB = 0, tam_inter = 0;
        pNodoRN *palavras;  // AVL que guarda tanto as palavras do texto A como do texto B
        palavras = Inicializa_RN();
        palavras = Ler_TXT(palavras, argv[1], stopwords, 'A', &tam_textoA, &tam_inter);   // Lê palavras do texto A
        //Cent_Esq(palavras);
        palavras = Ler_TXT(palavras, argv[2], stopwords, 'B', &tam_textoB, &tam_inter);   // Lê palavras do texto B
        //Cent_Esq(palavras);

        end = clock(); // Encerra a contagem do tempo
        float miliseconds = (float)(end - start) / CLOCKS_PER_SEC * 1000; // Calcula o tempo decorrido

        printf("\n'%s': %d palavras distintas\n", argv[1], tam_textoA);
        printf("'%s': %d palavras distintas\n", argv[2], tam_textoB);
        printf("Intersec.: %d palavras\n", tam_inter);
        printf("Jaccard = %.2f\n", (tam_textoA + tam_textoB > 0) ? (float)tam_inter/(tam_textoA + tam_textoB - tam_inter) : 1.00);
        printf("Tempo: %.2f ms\n", miliseconds);

        return 0;

    }

}
