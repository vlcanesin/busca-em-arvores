#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "EDlib.h"

pNodoAVL* Ler_Stopwords(pNodoAVL *SW, char path[]) {

    FILE *entrada;
    char palavra[256];

    char *tok; // Utilizados para limpar a palavra
    char separador[]= {" 0123456789-.,&*%\?!;/'@\"$#=~><()][}{:\n\t_"};

    entrada = fopen (path, "r"); // Abre o arquivo para leitura.

    if (entrada == NULL) {      // Se não conseguiu abrir o arquivo
        printf ("Erro ao abrir o arquivo %s", path);
        return NULL;
    }

    else { // Arquivo de entrada OK

        // Percorre todo o arquivo lendo palavra por palavra
        while (fscanf(entrada,"%s ",palavra) && !feof(entrada)) {

            tok = strtok(palavra, separador);     // Limpa caracteres indesejados
            sprintf(palavra, "%s", tok);          // no final da palavra (como ' ', '\n')

            int ok = 0;
            SW = Insere_AVL(SW, strlwr(palavra), &ok);  // Insere palavra em SW

        }

    }

    fclose (entrada); //fecha o arquivos
    return SW;

}

pNodoRN* Ler_TXT(pNodoRN *RN_atual, char path[], pNodoAVL* SW, char origem, int *tam_texto, int *tam_inter) {

    FILE *entrada;
    char palavra[256];

    char *tok; // Utilizados para iterar sobre as palavras de uma linha
    char separador[]= {" 0123456789-.,&*%\?!;/'@\"$#=~><()][}{:\n\t_"};

    entrada = fopen (path, "r"); // Abre o arquivo para leitura.

    if (entrada == NULL) {      // Se não conseguiu abrir o arquivo
        printf ("Erro ao abrir o arquivo %s", path);
        return NULL;
    }

    else { // Arquivo de entrada OK

        // Percorre todo o arquivo lendo palavra por palavra
        // (caso a palavra tenha contenha caracteres separadores, ela é separada em outras palavras)
        while (fscanf(entrada,"%s ",palavra) && !feof(entrada)) {

            tok = strtok(palavra, separador);           // Retira a primeira palavra

            while(tok) {

                sprintf(palavra, "%s", tok);          // Guarda a palavra
                strcpy(palavra, strlwr(palavra));

                if(!Consulta_AVL(SW, palavra)) {      // Se palavra não for stopword
                    //printf("\nPalavra lida: %s\n", palavra);
                    int ok = 0, eh_raiz = 1;
                    RN_atual = Insere_RN(RN_atual, palavra, &ok, eh_raiz, origem, tam_texto, tam_inter);  // Insere na árvore
                    //Imprime_Niveis_RN(RN_atual, 1);
                }

                tok = strtok(NULL, separador);        // Pega a próxima palavra

            }

        }

    }

    fclose (entrada); //fecha o arquivos
    return RN_atual;

}
