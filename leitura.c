#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "EDlib.h"

#define BUFFER_SIZE 256
// 2^8 chars/bytes

const char SEP[]= {"\n !\"#$%&'()*,-./0123456789:;<=>?@[]_{}~"};
// Caracteres separadores ordenados segundo a tabela ASCII

int _Busca_bin(int ini, int fim, int val) {

    if(ini > fim) return 0;

    int meio = (ini + fim)/2;
    if(val < SEP[meio]) return _Busca_bin(ini, meio-1, val);
    if(val > SEP[meio]) return _Busca_bin(meio+1, fim, val);

    return 1;

}

void _Ler_buffer(char buffer[], FILE** fileptr,
                 char modo, pNodoRN** RN, pNodoAVL** SW,
                 char origem, int *tam_texto, int *tam_inter) {

    char palavra[256];      // String que recebe os caracteres do buffer
    int i, c_count = 0;     // i - Ponteiro que itera sobre o buffer
                            // c_count - contador de caracteres da palavra

    for(i = 0; i < strlen(buffer); i++) {

        int sep_atingido = _Busca_bin(0, strlen(SEP)-1, buffer[i]);
        //int j, sep_atingido = 0;
        //for(j = 0; j < strlen(SEP); j++)    // OTIMIZAR
        //    if(buffer[i] == SEP[j])
        //        sep_atingido = 1;

        if(sep_atingido == 0) {    // Se é um caractere normal, salva na palavra

            if(c_count > 255) {
                printf("ERRO: tamanho limite de palavra excedido!\n");
                return;
            }

            palavra[c_count] = buffer[i];
            c_count++;

        } else {                   // Se é um caractere separador

            if(c_count != 0) {     // Se tiver algo na palavra

                palavra[c_count] = '\0';
                strcpy(palavra, strlwr(palavra));
                //printf("%s\n", palavra);

                if (modo == 'S') {          // Inserindo na árvore de stopwords

                    int ok = 0;
                    *SW = Insere_AVL(*SW, palavra, &ok);

                } else if(modo == 'P') {    // Inserindo na árvore de palavras

                    if(!Consulta_AVL(*SW, palavra)) {
                        int ok = 0, eh_raiz = 1;
                        *RN = Insere_RN(*RN, palavra, &ok, eh_raiz,
                                        origem, tam_texto, tam_inter);
                    }

                } else printf("Modo inválido!\n");

            }

            c_count = 0;           // Zera o tamanho da palavra

        }

    }

    if(c_count != 0) {  // Uma palavra foi lida pela metade (ou o fim do arquivo foi atingido)

        if(feof(*fileptr)) {  // Fim do arquivo atingido: falta salvar uma palavra

            palavra[c_count] = '\0';
            strcpy(palavra, strlwr(palavra));

            if (modo == 'S') {          // Inserindo na árvore de stopwords

                int ok = 0;
                *SW = Insere_AVL(*SW, palavra, &ok);

            } else if(modo == 'P') {    // Inserindo na árvore de palavras

                if(!Consulta_AVL(*SW, palavra)) {
                    int ok = 0, eh_raiz = 1;
                    *RN = Insere_RN(*RN, palavra, &ok, eh_raiz,
                                    origem, tam_texto, tam_inter);
                }

            } else printf("Modo inválido!\n");

        }

        else {                                      // Palavra lida pela metade:
            fseek(*fileptr, -c_count, SEEK_CUR);    // É preciso voltar o ponteiro do arquivo para
        }                                           // o ponto em que a palavra começa

    }

}

void Ler_TXT(pNodoRN** RN, pNodoAVL** SW,
             char path[], char modo,
             char origem, int *tam_texto, int *tam_inter) {

    FILE *entrada;
    char buffer[BUFFER_SIZE];

    entrada = fopen (path, "r"); // Abre o arquivo para leitura.

    if (entrada == NULL) {      // Se não conseguiu abrir o arquivo
        printf ("Erro ao abrir o arquivo %s", path);
        return;
    }

    else { // Arquivo de entrada OK

        // Percorre todo o arquivo colocando os bytes lidos em um buffer
        while (!feof(entrada)) {
            //fread(buffer, BUFFER_SIZE-1, 1, entrada);
            fgets(buffer, BUFFER_SIZE, entrada);
            //printf("%d\n", strlen(buffer));
            _Ler_buffer(buffer, &entrada,
                        modo, RN, SW,
                        origem, tam_texto, tam_inter);
        }

    }

    fclose (entrada); // fecha o arquivo

}
